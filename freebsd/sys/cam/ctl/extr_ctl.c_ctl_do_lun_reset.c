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
struct TYPE_2__ {int flags; } ;
union ctl_io {TYPE_1__ io_hdr; } ;
typedef  int uint32_t ;
struct ctl_lun {int /*<<< orphan*/  lun_lock; scalar_t__ prevent_count; scalar_t__ prevent; int /*<<< orphan*/  flags; int /*<<< orphan*/ ** pending_sense; int /*<<< orphan*/  ooa_queue; } ;
typedef  int /*<<< orphan*/  ctl_ua_type ;

/* Variables and functions */
 int CTL_FLAG_ABORT ; 
 int CTL_FLAG_ABORT_STATUS ; 
 int /*<<< orphan*/  CTL_LUN_RESERVED ; 
 int CTL_MAX_INITIATORS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  M_CTL ; 
 scalar_t__ TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 scalar_t__ TAILQ_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_clear_mask (scalar_t__,int) ; 
 int /*<<< orphan*/  ctl_est_ua_all (struct ctl_lun*,int,int /*<<< orphan*/ ) ; 
 int ctl_max_ports ; 
 int /*<<< orphan*/  ctl_tpc_lun_clear (struct ctl_lun*,int) ; 
 int /*<<< orphan*/  ctl_try_unblock_io (struct ctl_lun*,union ctl_io*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ooa_links ; 

__attribute__((used)) static void
ctl_do_lun_reset(struct ctl_lun *lun, uint32_t initidx, ctl_ua_type ua_type)
{
	union ctl_io *xio;
	int i;

	mtx_lock(&lun->lun_lock);
	/* Abort tasks. */
	for (xio = (union ctl_io *)TAILQ_FIRST(&lun->ooa_queue); xio != NULL;
	     xio = (union ctl_io *)TAILQ_NEXT(&xio->io_hdr, ooa_links)) {
		xio->io_hdr.flags |= CTL_FLAG_ABORT | CTL_FLAG_ABORT_STATUS;
		ctl_try_unblock_io(lun, xio, FALSE);
	}
	/* Clear CA. */
	for (i = 0; i < ctl_max_ports; i++) {
		free(lun->pending_sense[i], M_CTL);
		lun->pending_sense[i] = NULL;
	}
	/* Clear reservation. */
	lun->flags &= ~CTL_LUN_RESERVED;
	/* Clear prevent media removal. */
	if (lun->prevent) {
		for (i = 0; i < CTL_MAX_INITIATORS; i++)
			ctl_clear_mask(lun->prevent, i);
		lun->prevent_count = 0;
	}
	/* Clear TPC status */
	ctl_tpc_lun_clear(lun, -1);
	/* Establish UA. */
#if 0
	ctl_est_ua_all(lun, initidx, ua_type);
#else
	ctl_est_ua_all(lun, -1, ua_type);
#endif
	mtx_unlock(&lun->lun_lock);
}