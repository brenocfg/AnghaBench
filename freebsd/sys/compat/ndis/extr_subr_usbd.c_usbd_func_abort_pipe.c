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
struct TYPE_2__ {int /*<<< orphan*/  upr_handle; } ;
union usbd_urb {TYPE_1__ uu_pipe; } ;
struct ndisusb_ep {int /*<<< orphan*/ * ne_xfer; } ;
struct ndis_softc {int dummy; } ;
typedef  int /*<<< orphan*/  irp ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRP_NDIS_DEV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NDISUSB_LOCK (struct ndis_softc*) ; 
 int /*<<< orphan*/  NDISUSB_UNLOCK (struct ndis_softc*) ; 
 int /*<<< orphan*/  USBD_STATUS_INVALID_PIPE_HANDLE ; 
 int /*<<< orphan*/  USBD_STATUS_SUCCESS ; 
 struct ndis_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 struct ndisusb_ep* usbd_get_ndisep (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 union usbd_urb* usbd_geturb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t
usbd_func_abort_pipe(irp *ip)
{
	device_t dev = IRP_NDIS_DEV(ip);
	struct ndis_softc *sc = device_get_softc(dev);
	struct ndisusb_ep *ne;
	union usbd_urb *urb;

	urb = usbd_geturb(ip);
	ne = usbd_get_ndisep(ip, urb->uu_pipe.upr_handle);
	if (ne == NULL) {
		device_printf(IRP_NDIS_DEV(ip), "get NULL endpoint info.\n");
		return (USBD_STATUS_INVALID_PIPE_HANDLE);
	}

	NDISUSB_LOCK(sc);
	usbd_transfer_stop(ne->ne_xfer[0]);
	usbd_transfer_start(ne->ne_xfer[0]);
	NDISUSB_UNLOCK(sc);

	return (USBD_STATUS_SUCCESS);
}