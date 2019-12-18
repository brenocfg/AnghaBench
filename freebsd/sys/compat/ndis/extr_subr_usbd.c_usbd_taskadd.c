#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ndisusb_task {unsigned int nt_type; int /*<<< orphan*/  nt_tasklist; int /*<<< orphan*/ * nt_ctx; } ;
struct ndis_softc {int /*<<< orphan*/  ndisusb_taskitem; int /*<<< orphan*/  ndisusb_tasklock; int /*<<< orphan*/  ndisusb_tasklist; } ;
typedef  int /*<<< orphan*/  irp ;
typedef  int /*<<< orphan*/  io_workitem_func ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRP_NDIS_DEV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InsertTailList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IoQueueWorkItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ndis_softc*) ; 
 int /*<<< orphan*/  KeAcquireSpinLockAtDpcLevel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeReleaseSpinLockFromDpcLevel (int /*<<< orphan*/ *) ; 
 int M_NOWAIT ; 
 int /*<<< orphan*/  M_USBDEV ; 
 int M_ZERO ; 
 int /*<<< orphan*/  USBD_STATUS_NO_MEMORY ; 
 int /*<<< orphan*/  USBD_STATUS_SUCCESS ; 
 int /*<<< orphan*/  WORKQUEUE_CRITICAL ; 
 struct ndis_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct ndisusb_task* malloc (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ usbd_task_wrap ; 

__attribute__((used)) static int32_t
usbd_taskadd(irp *ip, unsigned type)
{
	device_t dev = IRP_NDIS_DEV(ip);
	struct ndis_softc *sc = device_get_softc(dev);
	struct ndisusb_task *nt;

	nt = malloc(sizeof(struct ndisusb_task), M_USBDEV, M_NOWAIT | M_ZERO);
	if (nt == NULL)
		return (USBD_STATUS_NO_MEMORY);
	nt->nt_type = type;
	nt->nt_ctx = ip;

	KeAcquireSpinLockAtDpcLevel(&sc->ndisusb_tasklock);
	InsertTailList((&sc->ndisusb_tasklist), (&nt->nt_tasklist));
	KeReleaseSpinLockFromDpcLevel(&sc->ndisusb_tasklock);

	IoQueueWorkItem(sc->ndisusb_taskitem,
	    (io_workitem_func)usbd_task_wrap, WORKQUEUE_CRITICAL, sc);

	return (USBD_STATUS_SUCCESS);
}