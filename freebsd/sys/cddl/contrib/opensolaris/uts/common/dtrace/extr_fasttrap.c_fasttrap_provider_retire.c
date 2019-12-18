#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ pid_t ;
struct TYPE_6__ {scalar_t__ ftp_pid; int ftp_retired; scalar_t__ ftp_mcount; int ftp_marked; int /*<<< orphan*/  ftp_mtx; int /*<<< orphan*/  ftp_provid; TYPE_1__* ftp_proc; int /*<<< orphan*/  ftp_name; struct TYPE_6__* ftp_next; } ;
typedef  TYPE_2__ fasttrap_provider_t ;
struct TYPE_7__ {int /*<<< orphan*/  ftb_mtx; TYPE_2__* ftb_data; } ;
typedef  TYPE_3__ fasttrap_bucket_t ;
typedef  int /*<<< orphan*/  dtrace_provider_id_t ;
struct TYPE_8__ {TYPE_3__* fth_table; } ;
struct TYPE_5__ {scalar_t__ ftpc_acount; scalar_t__ ftpc_rcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 size_t FASTTRAP_PROVS_INDEX (scalar_t__,char const*) ; 
 int /*<<< orphan*/  atomic_dec_64 (scalar_t__*) ; 
 int /*<<< orphan*/  dtrace_invalidate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fasttrap_pid_cleanup () ; 
 TYPE_4__ fasttrap_provs ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void
fasttrap_provider_retire(pid_t pid, const char *name, int mprov)
{
	fasttrap_provider_t *fp;
	fasttrap_bucket_t *bucket;
	dtrace_provider_id_t provid;

	ASSERT(strlen(name) < sizeof (fp->ftp_name));

	bucket = &fasttrap_provs.fth_table[FASTTRAP_PROVS_INDEX(pid, name)];
	mutex_enter(&bucket->ftb_mtx);

	for (fp = bucket->ftb_data; fp != NULL; fp = fp->ftp_next) {
		if (fp->ftp_pid == pid && strcmp(fp->ftp_name, name) == 0 &&
		    !fp->ftp_retired)
			break;
	}

	if (fp == NULL) {
		mutex_exit(&bucket->ftb_mtx);
		return;
	}

	mutex_enter(&fp->ftp_mtx);
	ASSERT(!mprov || fp->ftp_mcount > 0);
	if (mprov && --fp->ftp_mcount != 0)  {
		mutex_exit(&fp->ftp_mtx);
		mutex_exit(&bucket->ftb_mtx);
		return;
	}

	/*
	 * Mark the provider to be removed in our post-processing step, mark it
	 * retired, and drop the active count on its proc. Marking it indicates
	 * that we should try to remove it; setting the retired flag indicates
	 * that we're done with this provider; dropping the active the proc
	 * releases our hold, and when this reaches zero (as it will during
	 * exit or exec) the proc and associated providers become defunct.
	 *
	 * We obviously need to take the bucket lock before the provider lock
	 * to perform the lookup, but we need to drop the provider lock
	 * before calling into the DTrace framework since we acquire the
	 * provider lock in callbacks invoked from the DTrace framework. The
	 * bucket lock therefore protects the integrity of the provider hash
	 * table.
	 */
	atomic_dec_64(&fp->ftp_proc->ftpc_acount);
	ASSERT(fp->ftp_proc->ftpc_acount < fp->ftp_proc->ftpc_rcount);

	fp->ftp_retired = 1;
	fp->ftp_marked = 1;
	provid = fp->ftp_provid;
	mutex_exit(&fp->ftp_mtx);

	/*
	 * We don't have to worry about invalidating the same provider twice
	 * since fasttrap_provider_lookup() will ignore provider that have
	 * been marked as retired.
	 */
	dtrace_invalidate(provid);

	mutex_exit(&bucket->ftb_mtx);

	fasttrap_pid_cleanup();
}