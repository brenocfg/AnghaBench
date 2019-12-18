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
struct statfs {scalar_t__ f_bavail; int f_blocks; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_2__ {scalar_t__ v_type; int /*<<< orphan*/  v_mount; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACCT_EXITREQ ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 int /*<<< orphan*/  M_STATFS ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  SX_XLOCKED ; 
 scalar_t__ VBAD ; 
 scalar_t__ VFS_STATFS (int /*<<< orphan*/ ,struct statfs*) ; 
 int /*<<< orphan*/  acct_disable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  acct_state ; 
 int acct_suspended ; 
 int /*<<< orphan*/  acct_sx ; 
 TYPE_1__* acct_vp ; 
 int acctresume ; 
 int acctsuspend ; 
 int /*<<< orphan*/  free (struct statfs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*) ; 
 struct statfs* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
acctwatch(void)
{
	struct statfs *sp;

	sx_assert(&acct_sx, SX_XLOCKED);

	/*
	 * If accounting was disabled before our kthread was scheduled,
	 * then acct_vp might be NULL.  If so, just ask our kthread to
	 * exit and return.
	 */
	if (acct_vp == NULL) {
		acct_state |= ACCT_EXITREQ;
		return;
	}

	/*
	 * If our vnode is no longer valid, tear it down and signal the
	 * accounting thread to die.
	 */
	if (acct_vp->v_type == VBAD) {
		(void) acct_disable(NULL, 1);
		acct_state |= ACCT_EXITREQ;
		return;
	}

	/*
	 * Stopping here is better than continuing, maybe it will be VBAD
	 * next time around.
	 */
	sp = malloc(sizeof(struct statfs), M_STATFS, M_WAITOK);
	if (VFS_STATFS(acct_vp->v_mount, sp) < 0) {
		free(sp, M_STATFS);
		return;
	}
	if (acct_suspended) {
		if (sp->f_bavail > (int64_t)(acctresume * sp->f_blocks /
		    100)) {
			acct_suspended = 0;
			log(LOG_NOTICE, "Accounting resumed\n");
		}
	} else {
		if (sp->f_bavail <= (int64_t)(acctsuspend * sp->f_blocks /
		    100)) {
			acct_suspended = 1;
			log(LOG_NOTICE, "Accounting suspended\n");
		}
	}
	free(sp, M_STATFS);
}