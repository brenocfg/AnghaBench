#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usb_error_t ;
struct TYPE_10__ {int cdb_len; int /*<<< orphan*/  cdb; int /*<<< orphan*/  tag_type; void* tag_num; } ;
struct TYPE_8__ {int /*<<< orphan*/  targ_lun; int /*<<< orphan*/  targ_port; int /*<<< orphan*/  initid; } ;
struct TYPE_9__ {TYPE_2__ nexus; int /*<<< orphan*/  io_type; TYPE_1__* ctl_private; } ;
union ctl_io {TYPE_4__ scsiio; TYPE_3__ io_hdr; } ;
typedef  void* uint32_t ;
struct usb_xfer {int dummy; } ;
struct cfumass_softc {int sc_current_stalled; int /*<<< orphan*/  sc_queued; TYPE_5__* sc_cbw; int /*<<< orphan*/  sc_ctl_initid; void* sc_current_transfer_length; void* sc_current_residue; int /*<<< orphan*/  sc_current_flags; void* sc_current_tag; int /*<<< orphan*/  sc_current_status; int /*<<< orphan*/ * sc_ctl_io; } ;
struct TYPE_12__ {int /*<<< orphan*/  targ_port; int /*<<< orphan*/  ctl_pool_ref; } ;
struct TYPE_11__ {int bCDBLength; int /*<<< orphan*/  CBWCB; int /*<<< orphan*/  dCBWTag; int /*<<< orphan*/  bCBWLUN; int /*<<< orphan*/  bCBWFlags; int /*<<< orphan*/  dCBWDataTransferLength; int /*<<< orphan*/  dCBWSignature; } ;
struct TYPE_7__ {struct cfumass_softc* ptr; } ;

/* Variables and functions */
 void* CBWSIGNATURE ; 
 int /*<<< orphan*/  CFUMASS_DEBUG (struct cfumass_softc*,char*,...) ; 
 int /*<<< orphan*/  CFUMASS_LOCK (struct cfumass_softc*) ; 
 int /*<<< orphan*/  CFUMASS_UNLOCK (struct cfumass_softc*) ; 
 int /*<<< orphan*/  CFUMASS_WARN (struct cfumass_softc*,char*,int,...) ; 
 int /*<<< orphan*/  CTL_IO_SCSI ; 
 size_t CTL_PRIV_FRONTEND ; 
 int CTL_RETVAL_COMPLETE ; 
 int /*<<< orphan*/  CTL_TAG_UNTAGGED ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 void* UGETDW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 TYPE_6__ cfumass_port ; 
 int /*<<< orphan*/  cfumass_port_online ; 
 int /*<<< orphan*/  cfumass_quirk (struct cfumass_softc*,int /*<<< orphan*/ ,int) ; 
 union ctl_io* ctl_alloc_io (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_decode_lun (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_free_io (union ctl_io*) ; 
 int ctl_queue (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_zero_io (union ctl_io*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  refcount_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_errstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct cfumass_softc* usbd_xfer_softc (struct usb_xfer*) ; 

__attribute__((used)) static void
cfumass_t_command_callback(struct usb_xfer *xfer, usb_error_t usb_error)
{
	struct cfumass_softc *sc;
	uint32_t signature;
	union ctl_io *io;
	int error = 0;

	sc = usbd_xfer_softc(xfer);

	KASSERT(sc->sc_ctl_io == NULL,
	    ("sc_ctl_io is %p, should be NULL", sc->sc_ctl_io));

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		CFUMASS_DEBUG(sc, "USB_ST_TRANSFERRED");

		signature = UGETDW(sc->sc_cbw->dCBWSignature);
		if (signature != CBWSIGNATURE) {
			CFUMASS_WARN(sc, "wrong dCBWSignature 0x%08x, "
			    "should be 0x%08x", signature, CBWSIGNATURE);
			break;
		}

		if (sc->sc_cbw->bCDBLength <= 0 ||
		    sc->sc_cbw->bCDBLength > sizeof(sc->sc_cbw->CBWCB)) {
			CFUMASS_WARN(sc, "invalid bCDBLength %d, should be <= %zd",
			    sc->sc_cbw->bCDBLength, sizeof(sc->sc_cbw->CBWCB));
			break;
		}

		sc->sc_current_stalled = false;
		sc->sc_current_status = 0;
		sc->sc_current_tag = UGETDW(sc->sc_cbw->dCBWTag);
		sc->sc_current_transfer_length =
		    UGETDW(sc->sc_cbw->dCBWDataTransferLength);
		sc->sc_current_flags = sc->sc_cbw->bCBWFlags;

		/*
		 * Make sure to report proper residue if the datamove wasn't
		 * required, or wasn't called due to SCSI error.
		 */
		sc->sc_current_residue = sc->sc_current_transfer_length;

		if (cfumass_quirk(sc,
		    sc->sc_cbw->CBWCB, sc->sc_cbw->bCDBLength) != 0)
			break;

		if (!cfumass_port_online) {
			CFUMASS_DEBUG(sc, "cfumass port is offline; stalling");
			usbd_xfer_set_stall(xfer);
			break;
		}

		/*
		 * Those CTL functions cannot be called with mutex held.
		 */
		CFUMASS_UNLOCK(sc);
		io = ctl_alloc_io(cfumass_port.ctl_pool_ref);
		ctl_zero_io(io);
		io->io_hdr.ctl_private[CTL_PRIV_FRONTEND].ptr = sc;
		io->io_hdr.io_type = CTL_IO_SCSI;
		io->io_hdr.nexus.initid = sc->sc_ctl_initid;
		io->io_hdr.nexus.targ_port = cfumass_port.targ_port;
		io->io_hdr.nexus.targ_lun = ctl_decode_lun(sc->sc_cbw->bCBWLUN);
		io->scsiio.tag_num = UGETDW(sc->sc_cbw->dCBWTag);
		io->scsiio.tag_type = CTL_TAG_UNTAGGED;
		io->scsiio.cdb_len = sc->sc_cbw->bCDBLength;
		memcpy(io->scsiio.cdb, sc->sc_cbw->CBWCB, sc->sc_cbw->bCDBLength);
		refcount_acquire(&sc->sc_queued);
		error = ctl_queue(io);
		if (error != CTL_RETVAL_COMPLETE) {
			CFUMASS_WARN(sc,
			    "ctl_queue() failed; error %d; stalling", error);
			ctl_free_io(io);
			refcount_release(&sc->sc_queued);
			CFUMASS_LOCK(sc);
			usbd_xfer_set_stall(xfer);
			break;
		}

		CFUMASS_LOCK(sc);
		break;

	case USB_ST_SETUP:
tr_setup:
		CFUMASS_DEBUG(sc, "USB_ST_SETUP");

		usbd_xfer_set_frame_len(xfer, 0, sizeof(*sc->sc_cbw));
		usbd_transfer_submit(xfer);
		break;

	default:
		if (usb_error == USB_ERR_CANCELLED) {
			CFUMASS_DEBUG(sc, "USB_ERR_CANCELLED");
			break;
		}

		CFUMASS_DEBUG(sc, "USB_ST_ERROR: %s", usbd_errstr(usb_error));

		goto tr_setup;
	}
}