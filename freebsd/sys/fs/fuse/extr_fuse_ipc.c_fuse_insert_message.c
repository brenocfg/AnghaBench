#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct fuse_ticket {int tk_flag; TYPE_1__* tk_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  si_note; } ;
struct TYPE_4__ {int /*<<< orphan*/  ms_mtx; TYPE_2__ ks_rsel; } ;

/* Variables and functions */
 int FT_DIRTY ; 
 int /*<<< orphan*/  KNOTE_LOCKED (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ PZERO ; 
 scalar_t__ fdata_get_dead (TYPE_1__*) ; 
 int /*<<< orphan*/  fuse_lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_ms_push (struct fuse_ticket*) ; 
 int /*<<< orphan*/  fuse_ms_push_head (struct fuse_ticket*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  selwakeuppri (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  wakeup_one (TYPE_1__*) ; 

void
fuse_insert_message(struct fuse_ticket *ftick, bool urgent)
{
	if (ftick->tk_flag & FT_DIRTY) {
		panic("FUSE: ticket reused without being refreshed");
	}
	ftick->tk_flag |= FT_DIRTY;

	if (fdata_get_dead(ftick->tk_data)) {
		return;
	}
	fuse_lck_mtx_lock(ftick->tk_data->ms_mtx);
	if (urgent)
		fuse_ms_push_head(ftick);
	else
		fuse_ms_push(ftick);
	wakeup_one(ftick->tk_data);
	selwakeuppri(&ftick->tk_data->ks_rsel, PZERO + 1);
	KNOTE_LOCKED(&ftick->tk_data->ks_rsel.si_note, 0);
	fuse_lck_mtx_unlock(ftick->tk_data->ms_mtx);
}