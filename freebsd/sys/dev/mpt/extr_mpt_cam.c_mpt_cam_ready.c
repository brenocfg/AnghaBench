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
struct mpt_softc {int role; int ready; scalar_t__ is_fc; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  MPT_LOCK (struct mpt_softc*) ; 
 int MPT_ROLE_TARGET ; 
 int /*<<< orphan*/  MPT_UNLOCK (struct mpt_softc*) ; 
 scalar_t__ mpt_add_target_commands (struct mpt_softc*) ; 
 int /*<<< orphan*/  mpt_prt (struct mpt_softc*,char*) ; 

__attribute__((used)) static void
mpt_cam_ready(struct mpt_softc *mpt)
{

	/*
	 * If we're in target mode, hang out resources now
	 * so we don't cause the world to hang talking to us.
	 */
	if (mpt->is_fc && (mpt->role & MPT_ROLE_TARGET)) {
		/*
		 * Try to add some target command resources
		 */
		MPT_LOCK(mpt);
		if (mpt_add_target_commands(mpt) == FALSE) {
			mpt_prt(mpt, "failed to add target commands\n");
		}
		MPT_UNLOCK(mpt);
	}
	mpt->ready = 1;
}