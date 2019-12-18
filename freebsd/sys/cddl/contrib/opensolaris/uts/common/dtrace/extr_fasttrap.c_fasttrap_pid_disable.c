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
typedef  int /*<<< orphan*/  proc_t ;
struct TYPE_4__ {scalar_t__ ftp_rcount; int ftp_marked; int /*<<< orphan*/  ftp_mtx; scalar_t__ ftp_retired; } ;
typedef  TYPE_1__ fasttrap_provider_t ;
struct TYPE_5__ {scalar_t__ ftp_id; int ftp_ntps; scalar_t__ ftp_enabled; int /*<<< orphan*/  ftp_pid; TYPE_1__* ftp_prov; } ;
typedef  TYPE_2__ fasttrap_probe_t ;
typedef  scalar_t__ dtrace_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int PGET_HOLD ; 
 int PGET_NOTWEXIT ; 
 int /*<<< orphan*/  PRELE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_lock ; 
 int /*<<< orphan*/  fasttrap_disable_callbacks () ; 
 int /*<<< orphan*/  fasttrap_pid_cleanup () ; 
 int /*<<< orphan*/  fasttrap_tracepoint_disable (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ pget (int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void
fasttrap_pid_disable(void *arg, dtrace_id_t id, void *parg)
{
	fasttrap_probe_t *probe = parg;
	fasttrap_provider_t *provider = probe->ftp_prov;
	proc_t *p;
	int i, whack = 0;

	ASSERT(id == probe->ftp_id);

	mutex_enter(&provider->ftp_mtx);

	/*
	 * We won't be able to acquire a /proc-esque lock on the process
	 * iff the process is dead and gone. In this case, we rely on the
	 * provider lock as a point of mutual exclusion to prevent other
	 * DTrace consumers from disabling this probe.
	 */
	if (pget(probe->ftp_pid, PGET_HOLD | PGET_NOTWEXIT, &p) != 0)
		p = NULL;

	/*
	 * Disable all the associated tracepoints (for fully enabled probes).
	 */
	if (probe->ftp_enabled) {
		for (i = 0; i < probe->ftp_ntps; i++) {
			fasttrap_tracepoint_disable(p, probe, i);
		}
	}

	ASSERT(provider->ftp_rcount > 0);
	provider->ftp_rcount--;

	if (p != NULL) {
		/*
		 * Even though we may not be able to remove it entirely, we
		 * mark this retired provider to get a chance to remove some
		 * of the associated probes.
		 */
		if (provider->ftp_retired && !provider->ftp_marked)
			whack = provider->ftp_marked = 1;
		mutex_exit(&provider->ftp_mtx);
	} else {
		/*
		 * If the process is dead, we're just waiting for the
		 * last probe to be disabled to be able to free it.
		 */
		if (provider->ftp_rcount == 0 && !provider->ftp_marked)
			whack = provider->ftp_marked = 1;
		mutex_exit(&provider->ftp_mtx);
	}

	if (whack)
		fasttrap_pid_cleanup();

#ifdef __FreeBSD__
	if (p != NULL)
		PRELE(p);
#endif
	if (!probe->ftp_enabled)
		return;

	probe->ftp_enabled = 0;

#ifdef illumos
	ASSERT(MUTEX_HELD(&cpu_lock));
#endif
	fasttrap_disable_callbacks();
}