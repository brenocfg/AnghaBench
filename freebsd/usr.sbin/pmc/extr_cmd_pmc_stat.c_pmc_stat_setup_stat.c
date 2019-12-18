#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pmcstat_ev {char* ev_name; int ev_count; int ev_cumulative; long long ev_saved; scalar_t__ ev_cpu; int /*<<< orphan*/  ev_pmcid; int /*<<< orphan*/  ev_flags; int /*<<< orphan*/ * ev_spec; int /*<<< orphan*/  ev_mode; } ;
typedef  int /*<<< orphan*/  rootmask ;
typedef  int /*<<< orphan*/  cpuset_t ;
struct TYPE_3__ {int pa_flags; int pa_required; int /*<<< orphan*/  pa_events; void* pa_outputpath; int /*<<< orphan*/  pa_logfd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  CPU_CLR (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ CPU_FFS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_LEVEL_ROOT ; 
 int /*<<< orphan*/  CPU_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_WHICH_PID ; 
 scalar_t__ DEFAULT_SAMPLE_COUNT ; 
 int EX_OSERR ; 
 int /*<<< orphan*/  EX_SOFTWARE ; 
 int /*<<< orphan*/  EX_USAGE ; 
 int FIXED_MODE_NPMCS ; 
 int FLAG_HAS_COMMANDLINE ; 
 int FLAG_HAS_COUNTING_PMCS ; 
 int FLAG_HAS_OUTPUT_LOGFILE ; 
 int FLAG_HAS_PIPE ; 
 int FLAG_HAS_PROCESS_PMCS ; 
 int FLAG_HAS_SYSTEM_PMCS ; 
 int FLAG_HAS_TARGET ; 
 int IAP_START ; 
 int /*<<< orphan*/  PMCSTAT_OPEN_FOR_WRITE ; 
 scalar_t__ PMC_CPU_ANY ; 
 int /*<<< orphan*/  PMC_F_DESCENDANTS ; 
 int /*<<< orphan*/  PMC_ID_INVALID ; 
 int /*<<< orphan*/  PMC_MODE_SC ; 
 int /*<<< orphan*/  PMC_MODE_TC ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct pmcstat_ev*,int /*<<< orphan*/ ) ; 
 int STAT_MODE_NPMCS ; 
 int /*<<< orphan*/  before_ts ; 
 scalar_t__ clock_gettime (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int cpuset_getaffinity (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ev_next ; 
 scalar_t__ geteuid () ; 
 void* malloc (int) ; 
 TYPE_1__ pmc_args ; 
 scalar_t__ pmc_pmu_sample_rate_get (char*) ; 
 scalar_t__ pmc_pmu_stat_mode (char const***) ; 
 char** pmc_stat_mode_names ; 
 int /*<<< orphan*/  pmcstat_clone_event_descriptor (struct pmcstat_ev*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  pmcstat_open_log (void*,int /*<<< orphan*/ ) ; 
 char** stat_mode_cntrs ; 
 char const** stat_mode_names ; 
 int strcspn (void*,char*) ; 
 void* strdup (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static void
pmc_stat_setup_stat(int system_mode, const char *arg)
{
	const char *new_cntrs[STAT_MODE_NPMCS];
	static const char **pmc_stat_mode_cntrs;
	struct pmcstat_ev *ev;
	char *counters, *counter;
	int i, c, start, newcnt;
	cpuset_t cpumask, rootmask;

	if (cpuset_getaffinity(CPU_LEVEL_ROOT, CPU_WHICH_PID, -1,
	    sizeof(rootmask), &rootmask) == -1)
		err(EX_OSERR, "ERROR: Cannot determine the root set of CPUs");
	CPU_COPY(&rootmask, &cpumask);

	if (pmc_pmu_stat_mode(&pmc_stat_mode_cntrs) != 0)
		errx(EX_USAGE, "ERROR: hwmpc.ko not loaded or stat not supported on host.");
	if (system_mode && geteuid() != 0)
		errx(EX_USAGE, "ERROR: system mode counters can only be used as root");
	counters = NULL;
	for (i = 0; i < STAT_MODE_NPMCS; i++) {
		stat_mode_cntrs[i] = pmc_stat_mode_cntrs[i];
		stat_mode_names[i] = pmc_stat_mode_names[i];
	}
	if (arg) {
		counters = strdup(arg);
		newcnt = 0;
		while ((counter = strsep(&counters, ",")) != NULL &&
		    newcnt < STAT_MODE_NPMCS - IAP_START) {
			new_cntrs[newcnt++] = counter;
			if (pmc_pmu_sample_rate_get(counter) == DEFAULT_SAMPLE_COUNT)
				errx(EX_USAGE, "ERROR: %s not recognized on host", counter);
		}
		start = IAP_START + STAT_MODE_NPMCS - FIXED_MODE_NPMCS - newcnt;
		for (i = 0; i < newcnt; i++) {
			stat_mode_cntrs[start + i] = new_cntrs[i];
			stat_mode_names[start + i] = new_cntrs[i];
		}
	}
	if (system_mode)
		pmc_args.pa_flags |= FLAG_HAS_SYSTEM_PMCS;
	else
		pmc_args.pa_flags |= FLAG_HAS_PROCESS_PMCS;
	pmc_args.pa_flags |= FLAG_HAS_COUNTING_PMCS;
	pmc_args.pa_flags |= FLAG_HAS_COMMANDLINE | FLAG_HAS_TARGET;
	pmc_args.pa_flags |= FLAG_HAS_PIPE;
	pmc_args.pa_required |= FLAG_HAS_COMMANDLINE | FLAG_HAS_TARGET | FLAG_HAS_OUTPUT_LOGFILE;
	pmc_args.pa_outputpath = strdup("/dev/null");
	pmc_args.pa_logfd = pmcstat_open_log(pmc_args.pa_outputpath,
	    PMCSTAT_OPEN_FOR_WRITE);
	for (i = 0; i < STAT_MODE_NPMCS; i++) {
		if ((ev = malloc(sizeof(*ev))) == NULL)
			errx(EX_SOFTWARE, "ERROR: Out of memory.");
		if (system_mode)
			ev->ev_mode = PMC_MODE_SC;
		else
			ev->ev_mode = PMC_MODE_TC;
		ev->ev_spec = strdup(stat_mode_cntrs[i]);
		if (ev->ev_spec == NULL)
			errx(EX_SOFTWARE, "ERROR: Out of memory.");
		c = strcspn(strdup(stat_mode_cntrs[i]), ", \t");
		ev->ev_name = malloc(c + 1);
		if (ev->ev_name == NULL)
			errx(EX_SOFTWARE, "ERROR: Out of memory.");
		(void)strncpy(ev->ev_name, stat_mode_cntrs[i], c);
		*(ev->ev_name + c) = '\0';

		ev->ev_count = -1;
		ev->ev_flags = 0;
		ev->ev_flags |= PMC_F_DESCENDANTS;
		ev->ev_cumulative = 1;

		ev->ev_saved = 0LL;
		ev->ev_pmcid = PMC_ID_INVALID;
		STAILQ_INSERT_TAIL(&pmc_args.pa_events, ev, ev_next);
		if (system_mode) {
			ev->ev_cpu = CPU_FFS(&cpumask) - 1;
			CPU_CLR(ev->ev_cpu, &cpumask);
			pmcstat_clone_event_descriptor(ev, &cpumask, &pmc_args);
			CPU_SET(ev->ev_cpu, &cpumask);
		} else
			ev->ev_cpu = PMC_CPU_ANY;

	}
	if (clock_gettime(CLOCK_MONOTONIC, &before_ts))
		err(1, "clock_gettime");
}