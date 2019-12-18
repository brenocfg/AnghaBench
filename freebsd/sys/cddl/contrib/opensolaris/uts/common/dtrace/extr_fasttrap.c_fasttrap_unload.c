#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* ftp_next; int /*<<< orphan*/  ftp_provid; int /*<<< orphan*/  ftp_mtx; } ;
typedef  TYPE_1__ fasttrap_provider_t ;
struct TYPE_9__ {int /*<<< orphan*/  ftb_mtx; int /*<<< orphan*/  ftb_data; } ;
typedef  TYPE_2__ fasttrap_bucket_t ;
struct TYPE_12__ {int fth_nent; TYPE_2__* fth_table; } ;
struct TYPE_11__ {int fth_nent; TYPE_2__* fth_table; } ;
struct TYPE_10__ {int fth_nent; TYPE_2__* fth_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ DTRACE_METAPROVNONE ; 
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dtrace_fasttrap_exec ; 
 int /*<<< orphan*/ * dtrace_fasttrap_exit ; 
 int /*<<< orphan*/ * dtrace_fasttrap_fork ; 
 int /*<<< orphan*/  dtrace_meta_register (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ dtrace_meta_unregister (scalar_t__) ; 
 scalar_t__ dtrace_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fasttrap_cdev ; 
 int /*<<< orphan*/  fasttrap_cleanup_cv ; 
 int fasttrap_cleanup_drain ; 
 int /*<<< orphan*/  fasttrap_cleanup_mtx ; 
 int /*<<< orphan*/ * fasttrap_cleanup_proc ; 
 int /*<<< orphan*/  fasttrap_count_mtx ; 
 int /*<<< orphan*/  fasttrap_exec_exit ; 
 int /*<<< orphan*/  fasttrap_fork ; 
 scalar_t__ fasttrap_meta_id ; 
 int /*<<< orphan*/  fasttrap_mops ; 
 scalar_t__ fasttrap_pid_count ; 
 TYPE_7__ fasttrap_procs ; 
 int /*<<< orphan*/  fasttrap_provider_free (TYPE_1__*) ; 
 TYPE_5__ fasttrap_provs ; 
 int /*<<< orphan*/  fasttrap_thread_dtor_tag ; 
 int /*<<< orphan*/  fasttrap_tp_lock ; 
 TYPE_4__ fasttrap_tpoints ; 
 int /*<<< orphan*/  kmem_free (TYPE_2__*,int) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_sleep (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rm_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_dtor ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
fasttrap_unload(void)
{
	int i, fail = 0;

	/*
	 * Unregister the meta-provider to make sure no new fasttrap-
	 * managed providers come along while we're trying to close up
	 * shop. If we fail to detach, we'll need to re-register as a
	 * meta-provider. We can fail to unregister as a meta-provider
	 * if providers we manage still exist.
	 */
	if (fasttrap_meta_id != DTRACE_METAPROVNONE &&
	    dtrace_meta_unregister(fasttrap_meta_id) != 0)
		return (-1);

	/*
	 * Iterate over all of our providers. If there's still a process
	 * that corresponds to that pid, fail to detach.
	 */
	for (i = 0; i < fasttrap_provs.fth_nent; i++) {
		fasttrap_provider_t **fpp, *fp;
		fasttrap_bucket_t *bucket = &fasttrap_provs.fth_table[i];

		mutex_enter(&bucket->ftb_mtx);
		fpp = (fasttrap_provider_t **)&bucket->ftb_data;
		while ((fp = *fpp) != NULL) {
			/*
			 * Acquire and release the lock as a simple way of
			 * waiting for any other consumer to finish with
			 * this provider. A thread must first acquire the
			 * bucket lock so there's no chance of another thread
			 * blocking on the provider's lock.
			 */
			mutex_enter(&fp->ftp_mtx);
			mutex_exit(&fp->ftp_mtx);

			if (dtrace_unregister(fp->ftp_provid) != 0) {
				fail = 1;
				fpp = &fp->ftp_next;
			} else {
				*fpp = fp->ftp_next;
				fasttrap_provider_free(fp);
			}
		}

		mutex_exit(&bucket->ftb_mtx);
	}

	if (fail) {
		(void) dtrace_meta_register("fasttrap", &fasttrap_mops, NULL,
		    &fasttrap_meta_id);

		return (-1);
	}

	/*
	 * Stop new processes from entering these hooks now, before the
	 * fasttrap_cleanup thread runs.  That way all processes will hopefully
	 * be out of these hooks before we free fasttrap_provs.fth_table
	 */
	ASSERT(dtrace_fasttrap_fork == &fasttrap_fork);
	dtrace_fasttrap_fork = NULL;

	ASSERT(dtrace_fasttrap_exec == &fasttrap_exec_exit);
	dtrace_fasttrap_exec = NULL;

	ASSERT(dtrace_fasttrap_exit == &fasttrap_exec_exit);
	dtrace_fasttrap_exit = NULL;

	mtx_lock(&fasttrap_cleanup_mtx);
	fasttrap_cleanup_drain = 1;
	/* Wait for the cleanup thread to finish up and signal us. */
	wakeup(&fasttrap_cleanup_cv);
	mtx_sleep(&fasttrap_cleanup_drain, &fasttrap_cleanup_mtx, 0, "ftcld",
	    0);
	fasttrap_cleanup_proc = NULL;
	mtx_destroy(&fasttrap_cleanup_mtx);

#ifdef DEBUG
	mutex_enter(&fasttrap_count_mtx);
	ASSERT(fasttrap_pid_count == 0);
	mutex_exit(&fasttrap_count_mtx);
#endif

#ifndef illumos
	EVENTHANDLER_DEREGISTER(thread_dtor, fasttrap_thread_dtor_tag);

	for (i = 0; i < fasttrap_tpoints.fth_nent; i++)
		mutex_destroy(&fasttrap_tpoints.fth_table[i].ftb_mtx);
	for (i = 0; i < fasttrap_provs.fth_nent; i++)
		mutex_destroy(&fasttrap_provs.fth_table[i].ftb_mtx);
	for (i = 0; i < fasttrap_procs.fth_nent; i++)
		mutex_destroy(&fasttrap_procs.fth_table[i].ftb_mtx);
#endif
	kmem_free(fasttrap_tpoints.fth_table,
	    fasttrap_tpoints.fth_nent * sizeof (fasttrap_bucket_t));
	fasttrap_tpoints.fth_nent = 0;

	kmem_free(fasttrap_provs.fth_table,
	    fasttrap_provs.fth_nent * sizeof (fasttrap_bucket_t));
	fasttrap_provs.fth_nent = 0;

	kmem_free(fasttrap_procs.fth_table,
	    fasttrap_procs.fth_nent * sizeof (fasttrap_bucket_t));
	fasttrap_procs.fth_nent = 0;

#ifndef illumos
	destroy_dev(fasttrap_cdev);
	mutex_destroy(&fasttrap_count_mtx);
	rm_destroy(&fasttrap_tp_lock);
#endif

	return (0);
}