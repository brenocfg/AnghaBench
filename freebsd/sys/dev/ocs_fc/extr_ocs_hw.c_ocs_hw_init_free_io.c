#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int type; scalar_t__ tgt_wqe_timeout; int /*<<< orphan*/ * ul_io; int /*<<< orphan*/ * wq; int /*<<< orphan*/ * rnode; scalar_t__ port_owned_abort_count; int /*<<< orphan*/  abort_in_progress; scalar_t__ status_saved; int /*<<< orphan*/ * abort_done; int /*<<< orphan*/ * done; } ;
typedef  TYPE_1__ ocs_hw_io_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 

__attribute__((used)) static inline void
ocs_hw_init_free_io(ocs_hw_io_t *io)
{
	/*
	 * Set io->done to NULL, to avoid any callbacks, should
	 * a completion be received for one of these IOs
	 */
	io->done = NULL;
	io->abort_done = NULL;
	io->status_saved = 0;
	io->abort_in_progress = FALSE;
	io->port_owned_abort_count = 0;
	io->rnode = NULL;
	io->type = 0xFFFF;
	io->wq = NULL;
	io->ul_io = NULL;
	io->tgt_wqe_timeout = 0;
}