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
struct uio {int dummy; } ;
struct fuse_ticket {int tk_aw_errno; int /*<<< orphan*/  tk_aw_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  fticket_answered (struct fuse_ticket*) ; 
 int fticket_pull (struct fuse_ticket*,struct uio*) ; 
 int /*<<< orphan*/  fticket_set_answered (struct fuse_ticket*) ; 
 int /*<<< orphan*/  fuse_lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (struct fuse_ticket*) ; 

__attribute__((used)) static int
fuse_standard_handler(struct fuse_ticket *ftick, struct uio *uio)
{
	int err = 0;

	err = fticket_pull(ftick, uio);

	fuse_lck_mtx_lock(ftick->tk_aw_mtx);

	if (!fticket_answered(ftick)) {
		fticket_set_answered(ftick);
		ftick->tk_aw_errno = err;
		wakeup(ftick);
	}
	fuse_lck_mtx_unlock(ftick->tk_aw_mtx);

	return err;
}