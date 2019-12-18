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
struct mpt_softc {int cfg_role; int role; TYPE_1__* ioc_page2; scalar_t__ do_cfg_role; } ;
struct TYPE_2__ {scalar_t__ MaxPhysDisks; } ;

/* Variables and functions */
 int ENODEV ; 
 int MPT_ROLE_INITIATOR ; 
 int MPT_ROLE_TARGET ; 

__attribute__((used)) static int
mpt_cam_probe(struct mpt_softc *mpt)
{
	int role;

	/*
	 * Only attach to nodes that support the initiator or target role
	 * (or want to) or have RAID physical devices that need CAM pass-thru
	 * support.
	 */
	if (mpt->do_cfg_role) {
		role = mpt->cfg_role;
	} else {
		role = mpt->role;
	}
	if ((role & (MPT_ROLE_TARGET|MPT_ROLE_INITIATOR)) != 0 ||
	    (mpt->ioc_page2 != NULL && mpt->ioc_page2->MaxPhysDisks != 0)) {
		return (0);
	}
	return (ENODEV);
}