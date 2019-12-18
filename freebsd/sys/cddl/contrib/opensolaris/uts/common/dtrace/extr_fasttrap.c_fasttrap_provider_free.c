#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  p_dtrace_probes; } ;
typedef  TYPE_1__ proc_t ;
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_9__ {scalar_t__ ftp_rcount; scalar_t__ ftp_ccount; scalar_t__ ftp_mcount; int /*<<< orphan*/  ftp_cmtx; int /*<<< orphan*/  ftp_mtx; TYPE_6__* ftp_proc; int /*<<< orphan*/  ftp_retired; int /*<<< orphan*/  ftp_pid; } ;
typedef  TYPE_2__ fasttrap_provider_t ;
struct TYPE_10__ {scalar_t__ ftpc_acount; scalar_t__ ftpc_rcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  PROC_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  atomic_dec_64 (scalar_t__*) ; 
 int /*<<< orphan*/  fasttrap_proc_release (TYPE_6__*) ; 
 int /*<<< orphan*/  kmem_free (TYPE_2__*,int) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 TYPE_1__* pfind (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fasttrap_provider_free(fasttrap_provider_t *provider)
{
	pid_t pid = provider->ftp_pid;
	proc_t *p;

	/*
	 * There need to be no associated enabled probes, no consumers
	 * creating probes, and no meta providers referencing this provider.
	 */
	ASSERT(provider->ftp_rcount == 0);
	ASSERT(provider->ftp_ccount == 0);
	ASSERT(provider->ftp_mcount == 0);

	/*
	 * If this provider hasn't been retired, we need to explicitly drop the
	 * count of active providers on the associated process structure.
	 */
	if (!provider->ftp_retired) {
		atomic_dec_64(&provider->ftp_proc->ftpc_acount);
		ASSERT(provider->ftp_proc->ftpc_acount <
		    provider->ftp_proc->ftpc_rcount);
	}

	fasttrap_proc_release(provider->ftp_proc);

#ifndef illumos
	mutex_destroy(&provider->ftp_mtx);
	mutex_destroy(&provider->ftp_cmtx);
#endif
	kmem_free(provider, sizeof (fasttrap_provider_t));

	/*
	 * Decrement p_dtrace_probes on the process whose provider we're
	 * freeing. We don't have to worry about clobbering somone else's
	 * modifications to it because we have locked the bucket that
	 * corresponds to this process's hash chain in the provider hash
	 * table. Don't sweat it if we can't find the process.
	 */
	if ((p = pfind(pid)) == NULL) {
		return;
	}

	p->p_dtrace_probes--;
#ifndef illumos
	PROC_UNLOCK(p);
#endif
}