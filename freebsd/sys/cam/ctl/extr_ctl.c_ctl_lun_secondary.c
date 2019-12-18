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
struct ctl_lun {int /*<<< orphan*/  lun_lock; int /*<<< orphan*/  flags; } ;
struct ctl_be_lun {scalar_t__ ctl_lun; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_LUN_PRIMARY_SC ; 
 int /*<<< orphan*/  CTL_UA_ASYM_ACC_CHANGE ; 
 int /*<<< orphan*/  ctl_est_ua_all (struct ctl_lun*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_isc_announce_lun (struct ctl_lun*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int
ctl_lun_secondary(struct ctl_be_lun *be_lun)
{
	struct ctl_lun *lun = (struct ctl_lun *)be_lun->ctl_lun;

	mtx_lock(&lun->lun_lock);
	lun->flags &= ~CTL_LUN_PRIMARY_SC;
	ctl_est_ua_all(lun, -1, CTL_UA_ASYM_ACC_CHANGE);
	mtx_unlock(&lun->lun_lock);
	ctl_isc_announce_lun(lun);
	return (0);
}