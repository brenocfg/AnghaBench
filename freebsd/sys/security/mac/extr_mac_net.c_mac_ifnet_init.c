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
struct ifnet {int /*<<< orphan*/ * if_label; } ;

/* Variables and functions */
 int MPC_OBJECT_IFNET ; 
 int /*<<< orphan*/ * mac_ifnet_label_alloc () ; 
 int mac_labeled ; 

void
mac_ifnet_init(struct ifnet *ifp)
{

	if (mac_labeled & MPC_OBJECT_IFNET)
		ifp->if_label = mac_ifnet_label_alloc();
	else
		ifp->if_label = NULL;
}