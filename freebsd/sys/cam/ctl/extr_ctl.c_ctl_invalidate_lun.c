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
struct ctl_lun {int flags; int /*<<< orphan*/  lun_lock; int /*<<< orphan*/  ooa_queue; } ;
struct ctl_be_lun {scalar_t__ ctl_lun; } ;

/* Variables and functions */
 int CTL_LUN_DISABLED ; 
 int CTL_LUN_INVALID ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctl_free_lun (struct ctl_lun*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int
ctl_invalidate_lun(struct ctl_be_lun *be_lun)
{
	struct ctl_lun *lun;

	lun = (struct ctl_lun *)be_lun->ctl_lun;

	mtx_lock(&lun->lun_lock);

	/*
	 * The LUN needs to be disabled before it can be marked invalid.
	 */
	if ((lun->flags & CTL_LUN_DISABLED) == 0) {
		mtx_unlock(&lun->lun_lock);
		return (-1);
	}
	/*
	 * Mark the LUN invalid.
	 */
	lun->flags |= CTL_LUN_INVALID;

	/*
	 * If there is nothing in the OOA queue, go ahead and free the LUN.
	 * If we have something in the OOA queue, we'll free it when the
	 * last I/O completes.
	 */
	if (TAILQ_EMPTY(&lun->ooa_queue)) {
		mtx_unlock(&lun->lun_lock);
		ctl_free_lun(lun);
	} else
		mtx_unlock(&lun->lun_lock);

	return (0);
}