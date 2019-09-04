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
typedef  scalar_t__ uint64_t ;
struct option {int dummy; } ;

/* Variables and functions */
 struct option OPT_BOOL (char,char*,scalar_t__*,char*) ; 
 struct option OPT_END () ; 
 struct option OPT_INTEGER (char,char*,int*,char*) ; 
 int analyze ; 
 int /*<<< orphan*/  analyze_run () ; 
 int analyze_step ; 
 int count ; 
 int /*<<< orphan*/  die (char*) ; 
 scalar_t__ dump ; 
 int /*<<< orphan*/  dump_run () ; 
 int ignore_case ; 
 scalar_t__ multi ; 
 int parse_options (int,char const**,char const*,struct option*,char const**,int /*<<< orphan*/ ) ; 
 scalar_t__ perf ; 
 char* setup_git_directory () ; 
 scalar_t__ single ; 
 scalar_t__ time_runs (int) ; 

int cmd__lazy_init_name_hash(int argc, const char **argv)
{
	const char *usage[] = {
		"test-tool lazy-init-name-hash -d (-s | -m)",
		"test-tool lazy-init-name-hash -p [-c c]",
		"test-tool lazy-init-name-hash -a a [--step s] [-c c]",
		"test-tool lazy-init-name-hash (-s | -m) [-c c]",
		"test-tool lazy-init-name-hash -s -m [-c c]",
		NULL
	};
	struct option options[] = {
		OPT_BOOL('s', "single", &single, "run single-threaded code"),
		OPT_BOOL('m', "multi", &multi, "run multi-threaded code"),
		OPT_INTEGER('c', "count", &count, "number of passes"),
		OPT_BOOL('d', "dump", &dump, "dump hash tables"),
		OPT_BOOL('p', "perf", &perf, "compare single vs multi"),
		OPT_INTEGER('a', "analyze", &analyze, "analyze different multi sizes"),
		OPT_INTEGER(0, "step", &analyze_step, "analyze step factor"),
		OPT_END(),
	};
	const char *prefix;
	uint64_t avg_single, avg_multi;

	prefix = setup_git_directory();

	argc = parse_options(argc, argv, prefix, options, usage, 0);

	/*
	 * istate->dir_hash is only created when ignore_case is set.
	 */
	ignore_case = 1;

	if (dump) {
		if (perf || analyze > 0)
			die("cannot combine dump, perf, or analyze");
		if (count > 1)
			die("count not valid with dump");
		if (single && multi)
			die("cannot use both single and multi with dump");
		if (!single && !multi)
			die("dump requires either single or multi");
		dump_run();
		return 0;
	}

	if (perf) {
		if (analyze > 0)
			die("cannot combine dump, perf, or analyze");
		if (single || multi)
			die("cannot use single or multi with perf");
		avg_single = time_runs(0);
		avg_multi = time_runs(1);
		if (avg_multi > avg_single)
			die("multi is slower");
		return 0;
	}

	if (analyze) {
		if (analyze < 500)
			die("analyze must be at least 500");
		if (!analyze_step)
			analyze_step = analyze;
		if (single || multi)
			die("cannot use single or multi with analyze");
		analyze_run();
		return 0;
	}

	if (!single && !multi)
		die("require either -s or -m or both");

	if (single)
		time_runs(0);
	if (multi)
		time_runs(1);

	return 0;
}