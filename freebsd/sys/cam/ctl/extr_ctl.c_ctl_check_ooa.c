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
union ctl_io {int /*<<< orphan*/  io_hdr; } ;
struct ctl_lun {int /*<<< orphan*/  lun_lock; } ;
typedef  scalar_t__ ctl_action ;

/* Variables and functions */
 scalar_t__ CTL_ACTION_PASS ; 
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ TAILQ_PREV (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ctl_check_for_blockage (struct ctl_lun*,union ctl_io*,union ctl_io*) ; 
 int /*<<< orphan*/  ctl_ooaq ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ooa_links ; 

__attribute__((used)) static ctl_action
ctl_check_ooa(struct ctl_lun *lun, union ctl_io *pending_io,
	      union ctl_io **starting_io)
{
	union ctl_io *ooa_io;
	ctl_action action;

	mtx_assert(&lun->lun_lock, MA_OWNED);

	/*
	 * Run back along the OOA queue, starting with the current
	 * blocked I/O and going through every I/O before it on the
	 * queue.  If starting_io is NULL, we'll just end up returning
	 * CTL_ACTION_PASS.
	 */
	for (ooa_io = *starting_io; ooa_io != NULL;
	     ooa_io = (union ctl_io *)TAILQ_PREV(&ooa_io->io_hdr, ctl_ooaq,
	     ooa_links)){
		action = ctl_check_for_blockage(lun, pending_io, ooa_io);
		if (action != CTL_ACTION_PASS) {
			*starting_io = ooa_io;
			return (action);
		}
	}

	*starting_io = NULL;
	return (CTL_ACTION_PASS);
}