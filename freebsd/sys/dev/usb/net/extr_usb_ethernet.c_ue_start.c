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
struct usb_ether {TYPE_1__* ue_methods; } ;
struct ifnet {int if_drv_flags; struct usb_ether* if_softc; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ue_start ) (struct usb_ether*) ;} ;

/* Variables and functions */
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  UE_LOCK (struct usb_ether*) ; 
 int /*<<< orphan*/  UE_UNLOCK (struct usb_ether*) ; 
 int /*<<< orphan*/  stub1 (struct usb_ether*) ; 

__attribute__((used)) static void
ue_start(struct ifnet *ifp)
{
	struct usb_ether *ue = ifp->if_softc;

	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) == 0)
		return;

	UE_LOCK(ue);
	ue->ue_methods->ue_start(ue);
	UE_UNLOCK(ue);
}