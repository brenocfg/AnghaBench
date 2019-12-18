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
struct pmcstat_ev {int ev_cpu; int /*<<< orphan*/ * ev_spec; int /*<<< orphan*/  ev_saved; int /*<<< orphan*/  ev_pmcid; int /*<<< orphan*/ * ev_name; int /*<<< orphan*/  ev_mode; int /*<<< orphan*/  ev_flags; int /*<<< orphan*/  ev_cumulative; int /*<<< orphan*/  ev_count; } ;
struct pmcstat_args {int /*<<< orphan*/  pa_events; } ;
typedef  int /*<<< orphan*/  cpuset_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_ISSET (int,int /*<<< orphan*/  const*) ; 
 int CPU_SETSIZE ; 
 int /*<<< orphan*/  EX_SOFTWARE ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct pmcstat_ev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ev_next ; 
 struct pmcstat_ev* malloc (int) ; 
 int /*<<< orphan*/  memset (struct pmcstat_ev*,int /*<<< orphan*/ ,int) ; 
 void* strdup (int /*<<< orphan*/ *) ; 

void
pmcstat_clone_event_descriptor(struct pmcstat_ev *ev, const cpuset_t *cpumask,
    struct pmcstat_args *args)
{
	int cpu;
	struct pmcstat_ev *ev_clone;

	for (cpu = 0; cpu < CPU_SETSIZE; cpu++) {
		if (!CPU_ISSET(cpu, cpumask))
			continue;

		if ((ev_clone = malloc(sizeof(*ev_clone))) == NULL)
			errx(EX_SOFTWARE, "ERROR: Out of memory");
		(void) memset(ev_clone, 0, sizeof(*ev_clone));

		ev_clone->ev_count = ev->ev_count;
		ev_clone->ev_cpu   = cpu;
		ev_clone->ev_cumulative = ev->ev_cumulative;
		ev_clone->ev_flags = ev->ev_flags;
		ev_clone->ev_mode  = ev->ev_mode;
		ev_clone->ev_name  = strdup(ev->ev_name);
		if (ev_clone->ev_name == NULL)
			errx(EX_SOFTWARE, "ERROR: Out of memory");
		ev_clone->ev_pmcid = ev->ev_pmcid;
		ev_clone->ev_saved = ev->ev_saved;
		ev_clone->ev_spec  = strdup(ev->ev_spec);
		if (ev_clone->ev_spec == NULL)
			errx(EX_SOFTWARE, "ERROR: Out of memory");

		STAILQ_INSERT_TAIL(&args->pa_events, ev_clone, ev_next);
	}
}