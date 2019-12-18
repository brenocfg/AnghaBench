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
struct usb_ether {int /*<<< orphan*/  ue_tq; int /*<<< orphan*/  ue_unit; int /*<<< orphan*/  ue_rxq; int /*<<< orphan*/  ue_sysctl_ctx; int /*<<< orphan*/ * ue_miibus; int /*<<< orphan*/  ue_dev; int /*<<< orphan*/  ue_watchdog; struct ifnet* ue_ifp; } ;
struct ifnet {int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  UE_LOCK (struct usb_ether*) ; 
 int /*<<< orphan*/  UE_UNLOCK (struct usb_ether*) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  free_unr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  mbufq_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysctl_ctx_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ueunit ; 
 int /*<<< orphan*/  usb_callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_proc_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_proc_free (int /*<<< orphan*/ *) ; 

void
uether_ifdetach(struct usb_ether *ue)
{
	struct ifnet *ifp;

	/* wait for any post attach or other command to complete */
	usb_proc_drain(&ue->ue_tq);

	/* read "ifnet" pointer after taskqueue drain */
	ifp = ue->ue_ifp;

	if (ifp != NULL) {

		/* we are not running any more */
		UE_LOCK(ue);
		ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
		UE_UNLOCK(ue);

		/* drain any callouts */
		usb_callout_drain(&ue->ue_watchdog);

		/* detach miibus */
		if (ue->ue_miibus != NULL) {
			mtx_lock(&Giant);	/* device_xxx() depends on this */
			device_delete_child(ue->ue_dev, ue->ue_miibus);
			mtx_unlock(&Giant);
		}

		/* detach ethernet */
		ether_ifdetach(ifp);

		/* free interface instance */
		if_free(ifp);

		/* free sysctl */
		sysctl_ctx_free(&ue->ue_sysctl_ctx);

		/* drain mbuf queue */
		mbufq_drain(&ue->ue_rxq);

		/* free unit */
		free_unr(ueunit, ue->ue_unit);
	}

	/* free taskqueue, if any */
	usb_proc_free(&ue->ue_tq);
}