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
struct TYPE_2__ {int /*<<< orphan*/  blocked_queue; int /*<<< orphan*/ * blocker; } ;
union ctl_io {TYPE_1__ io_hdr; } ;
struct ctl_lun {int /*<<< orphan*/  lun_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 scalar_t__ TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 scalar_t__ TAILQ_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blocked_links ; 
 int /*<<< orphan*/  ctl_try_unblock_io (struct ctl_lun*,union ctl_io*,int) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ctl_try_unblock_others(struct ctl_lun *lun, union ctl_io *bio, bool skip)
{
	union ctl_io *io, *next_io;

	mtx_assert(&lun->lun_lock, MA_OWNED);

	for (io = (union ctl_io *)TAILQ_FIRST(&bio->io_hdr.blocked_queue);
	     io != NULL; io = next_io) {
		next_io = (union ctl_io *)TAILQ_NEXT(&io->io_hdr, blocked_links);

		KASSERT(io->io_hdr.blocker != NULL,
		    ("I/O %p on blocked list without blocker", io));
		ctl_try_unblock_io(lun, io, skip);
	}
	KASSERT(!skip || TAILQ_EMPTY(&bio->io_hdr.blocked_queue),
	    ("blocked_queue is not empty after skipping %p", bio));
}