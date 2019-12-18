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

/* Variables and functions */
 int /*<<< orphan*/  EX_USAGE ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 

void
pmcstat_show_usage(void)
{
	errx(EX_USAGE,
	    "[options] [commandline]\n"
	    "\t Measure process and/or system performance using hardware\n"
	    "\t performance monitoring counters.\n"
	    "\t Options include:\n"
	    "\t -C\t\t (toggle) show cumulative counts\n"
	    "\t -D path\t create profiles in directory \"path\"\n"
	    "\t -E\t\t (toggle) show counts at process exit\n"
	    "\t -F file\t write a system-wide callgraph (Kcachegrind format)"
		" to \"file\"\n"
	    "\t -G file\t write a system-wide callgraph to \"file\"\n"
	    "\t -I\t\t don't resolve leaf function name, show address instead\n"
	    "\t -L\t\t list all counters available on this host\n"
	    "\t -M file\t print executable/gmon file map to \"file\"\n"
	    "\t -N\t\t (toggle) capture callchains\n"
	    "\t -O file\t send log output to \"file\"\n"
	    "\t -P spec\t allocate a process-private sampling PMC\n"
	    "\t -R file\t read events from \"file\"\n"
	    "\t -S spec\t allocate a system-wide sampling PMC\n"
	    "\t -T\t\t start in top mode\n"
	    "\t -U \t\n merged user kernel stack capture\n"
	    "\t -W\t\t (toggle) show counts per context switch\n"
	    "\t -a file\t print sampled PCs and callgraph to \"file\"\n"
	    "\t -c cpu-list\t set cpus for subsequent system-wide PMCs\n"
	    "\t -d\t\t (toggle) track descendants\n"
	    "\t -e\t\t use wide history counter for gprof(1) output\n"
	    "\t -f spec\t pass \"spec\" to as plugin option\n"
	    "\t -g\t\t produce gprof(1) compatible profiles\n"
	    "\t -i lwp\t\t filter on thread id \"lwp\" in post-processing\n"
	    "\t -k dir\t\t set the path to the kernel\n"
	    "\t -l secs\t set duration time\n"
	    "\t -m file\t print sampled PCs to \"file\"\n"
	    "\t -n rate\t set sampling rate\n"
	    "\t -o file\t send print output to \"file\"\n"
	    "\t -p spec\t allocate a process-private counting PMC\n"
	    "\t -q\t\t suppress verbosity\n"
	    "\t -r fsroot\t specify FS root directory\n"
	    "\t -s spec\t allocate a system-wide counting PMC\n"
	    "\t -t process-spec attach to running processes matching "
		"\"process-spec\"\n"
	    "\t -u spec \t provide short description of counters matching spec\n"
	    "\t -v\t\t increase verbosity\n"
	    "\t -w secs\t set printing time interval\n"
	    "\t -z depth\t limit callchain display depth"
	);
}