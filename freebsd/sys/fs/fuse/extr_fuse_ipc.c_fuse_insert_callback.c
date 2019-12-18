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
struct fuse_ticket {TYPE_1__* tk_data; int /*<<< orphan*/ * tk_aw_handler; } ;
typedef  int /*<<< orphan*/  fuse_handler_t ;
struct TYPE_2__ {int /*<<< orphan*/  aw_mtx; } ;

/* Variables and functions */
 scalar_t__ fdata_get_dead (TYPE_1__*) ; 
 int /*<<< orphan*/  fuse_aw_push (struct fuse_ticket*) ; 
 int /*<<< orphan*/  fuse_lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_lck_mtx_unlock (int /*<<< orphan*/ ) ; 

void
fuse_insert_callback(struct fuse_ticket *ftick, fuse_handler_t * handler)
{
	if (fdata_get_dead(ftick->tk_data)) {
		return;
	}
	ftick->tk_aw_handler = handler;

	fuse_lck_mtx_lock(ftick->tk_data->aw_mtx);
	fuse_aw_push(ftick);
	fuse_lck_mtx_unlock(ftick->tk_data->aw_mtx);
}