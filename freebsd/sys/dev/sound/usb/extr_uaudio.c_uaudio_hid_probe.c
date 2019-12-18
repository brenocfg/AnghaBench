#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct usb_attach_arg {int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  xfer; int /*<<< orphan*/  iface_index; int /*<<< orphan*/  mute_id; int /*<<< orphan*/  mute_loc; int /*<<< orphan*/  volume_down_id; int /*<<< orphan*/  volume_down_loc; int /*<<< orphan*/  volume_up_id; int /*<<< orphan*/  volume_up_loc; } ;
struct uaudio_softc {int /*<<< orphan*/ * sc_mixer_lock; TYPE_1__ sc_hid; int /*<<< orphan*/  sc_mixer_iface_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int /*<<< orphan*/  HID_USAGE2 (int /*<<< orphan*/ ,int) ; 
 int HIO_VARIABLE ; 
 int /*<<< orphan*/  HUP_CONSUMER ; 
 int /*<<< orphan*/  M_TEMP ; 
 int UAUDIO_HID_HAS_ID ; 
 int UAUDIO_HID_HAS_MUTE ; 
 int UAUDIO_HID_HAS_VOLUME_DOWN ; 
 int UAUDIO_HID_HAS_VOLUME_UP ; 
 int /*<<< orphan*/  UAUDIO_HID_N_TRANSFER ; 
 int UAUDIO_HID_VALID ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_input ; 
 scalar_t__ hid_locate (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hid_report_size (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  uaudio_hid_config ; 
 int /*<<< orphan*/  usbd_errstr (int) ; 
 int usbd_req_get_hid_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_set_parent_iface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usbd_transfer_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uaudio_softc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
uaudio_hid_probe(struct uaudio_softc *sc,
    struct usb_attach_arg *uaa)
{
	void *d_ptr;
	uint32_t flags;
	uint16_t d_len;
	uint8_t id;
	int error;

	if (!(sc->sc_hid.flags & UAUDIO_HID_VALID))
		return (-1);

	if (sc->sc_mixer_lock == NULL)
		return (-1);

	/* Get HID descriptor */
	error = usbd_req_get_hid_desc(uaa->device, NULL, &d_ptr,
	    &d_len, M_TEMP, sc->sc_hid.iface_index);

	if (error) {
		DPRINTF("error reading report description\n");
		return (-1);
	}

	/* check if there is an ID byte */
	hid_report_size(d_ptr, d_len, hid_input, &id);

	if (id != 0)
		sc->sc_hid.flags |= UAUDIO_HID_HAS_ID;

	if (hid_locate(d_ptr, d_len,
	    HID_USAGE2(HUP_CONSUMER, 0xE9 /* Volume Increment */),
	    hid_input, 0, &sc->sc_hid.volume_up_loc, &flags,
	    &sc->sc_hid.volume_up_id)) {
		if (flags & HIO_VARIABLE)
			sc->sc_hid.flags |= UAUDIO_HID_HAS_VOLUME_UP;
		DPRINTFN(1, "Found Volume Up key\n");
	}

	if (hid_locate(d_ptr, d_len,
	    HID_USAGE2(HUP_CONSUMER, 0xEA /* Volume Decrement */),
	    hid_input, 0, &sc->sc_hid.volume_down_loc, &flags,
	    &sc->sc_hid.volume_down_id)) {
		if (flags & HIO_VARIABLE)
			sc->sc_hid.flags |= UAUDIO_HID_HAS_VOLUME_DOWN;
		DPRINTFN(1, "Found Volume Down key\n");
	}

	if (hid_locate(d_ptr, d_len,
	    HID_USAGE2(HUP_CONSUMER, 0xE2 /* Mute */),
	    hid_input, 0, &sc->sc_hid.mute_loc, &flags,
	    &sc->sc_hid.mute_id)) {
		if (flags & HIO_VARIABLE)
			sc->sc_hid.flags |= UAUDIO_HID_HAS_MUTE;
		DPRINTFN(1, "Found Mute key\n");
	}

	free(d_ptr, M_TEMP);

	if (!(sc->sc_hid.flags & (UAUDIO_HID_HAS_VOLUME_UP |
	    UAUDIO_HID_HAS_VOLUME_DOWN |
	    UAUDIO_HID_HAS_MUTE))) {
		DPRINTFN(1, "Did not find any volume related keys\n");
		return (-1);
	}

	/* prevent the uhid driver from attaching */
	usbd_set_parent_iface(uaa->device, sc->sc_hid.iface_index,
	    sc->sc_mixer_iface_index);

	/* allocate USB transfers */
	error = usbd_transfer_setup(uaa->device, &sc->sc_hid.iface_index,
	    sc->sc_hid.xfer, uaudio_hid_config, UAUDIO_HID_N_TRANSFER,
	    sc, sc->sc_mixer_lock);
	if (error) {
		DPRINTF("error=%s\n", usbd_errstr(error));
		return (-1);
	}
	return (0);
}