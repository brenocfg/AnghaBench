#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ndisusb_ep {int /*<<< orphan*/ * ne_xfer; } ;
struct ndis_softc {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  irp_cancelirql; void* irp_cancel; } ;
typedef  TYPE_1__ irp ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  device_object ;

/* Variables and functions */
 struct ndisusb_ep* IRP_NDISUSB_EP (TYPE_1__*) ; 
 int /*<<< orphan*/  IRP_NDIS_DEV (TYPE_1__*) ; 
 int /*<<< orphan*/  IoReleaseCancelSpinLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDISUSB_LOCK (struct ndis_softc*) ; 
 int /*<<< orphan*/  NDISUSB_UNLOCK (struct ndis_softc*) ; 
 void* TRUE ; 
 struct ndis_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
usbd_irpcancel(device_object *dobj, irp *ip)
{
	device_t dev = IRP_NDIS_DEV(ip);
	struct ndis_softc *sc = device_get_softc(dev);
	struct ndisusb_ep *ne = IRP_NDISUSB_EP(ip);

	if (ne == NULL) {
		ip->irp_cancel = TRUE;
		IoReleaseCancelSpinLock(ip->irp_cancelirql);
		return;
	}

	/*
	 * Make sure that the current USB transfer proxy is
	 * cancelled and then restarted.
	 */
	NDISUSB_LOCK(sc);
	usbd_transfer_stop(ne->ne_xfer[0]);
	usbd_transfer_start(ne->ne_xfer[0]);
	NDISUSB_UNLOCK(sc);

	ip->irp_cancel = TRUE;
	IoReleaseCancelSpinLock(ip->irp_cancelirql);
}