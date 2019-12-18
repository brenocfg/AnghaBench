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
struct sysctl_req {int dummy; } ;
struct sysctl_oid {int oid_kind; int (* oid_handler ) (struct sysctl_oid*,void*,int /*<<< orphan*/ ,struct sysctl_req*) ;int /*<<< orphan*/  oid_running; } ;
struct rm_priotracker {int dummy; } ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 int CTLFLAG_DYING ; 
 int CTLFLAG_DYN ; 
 int CTLFLAG_MPSAFE ; 
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  KFAIL_POINT_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SYSCTL_RLOCK (struct rm_priotracker*) ; 
 int /*<<< orphan*/  SYSCTL_RUNLOCK (struct rm_priotracker*) ; 
 int /*<<< orphan*/  SYSCTL_WLOCK () ; 
 int /*<<< orphan*/  SYSCTL_WUNLOCK () ; 
 int /*<<< orphan*/  _debug_fail_point ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int atomic_fetchadd_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct sysctl_oid*,void*,int /*<<< orphan*/ ,struct sysctl_req*) ; 
 int /*<<< orphan*/  sysctl_running ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
sysctl_root_handler_locked(struct sysctl_oid *oid, void *arg1, intmax_t arg2,
    struct sysctl_req *req, struct rm_priotracker *tracker)
{
	int error;

	if (oid->oid_kind & CTLFLAG_DYN)
		atomic_add_int(&oid->oid_running, 1);

	if (tracker != NULL)
		SYSCTL_RUNLOCK(tracker);
	else
		SYSCTL_WUNLOCK();

	if (!(oid->oid_kind & CTLFLAG_MPSAFE))
		mtx_lock(&Giant);
	error = oid->oid_handler(oid, arg1, arg2, req);
	if (!(oid->oid_kind & CTLFLAG_MPSAFE))
		mtx_unlock(&Giant);

	KFAIL_POINT_ERROR(_debug_fail_point, sysctl_running, error);

	if (tracker != NULL)
		SYSCTL_RLOCK(tracker);
	else
		SYSCTL_WLOCK();

	if (oid->oid_kind & CTLFLAG_DYN) {
		if (atomic_fetchadd_int(&oid->oid_running, -1) == 1 &&
		    (oid->oid_kind & CTLFLAG_DYING) != 0)
			wakeup(&oid->oid_running);
	}

	return (error);
}