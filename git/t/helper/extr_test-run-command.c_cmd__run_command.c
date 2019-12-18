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
struct child_process {char const** argv; int /*<<< orphan*/  env_array; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  argv_array_push (int /*<<< orphan*/ *,char const*) ; 
 int atoi (char const*) ; 
 int /*<<< orphan*/  die (char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  no_job ; 
 int /*<<< orphan*/  parallel_next ; 
 int /*<<< orphan*/  run_command (struct child_process*) ; 
 int /*<<< orphan*/  run_processes_parallel (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct child_process*) ; 
 scalar_t__ start_command (struct child_process*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/ * task_finished ; 
 int /*<<< orphan*/  testsuite (int,char const**) ; 

int cmd__run_command(int argc, const char **argv)
{
	struct child_process proc = CHILD_PROCESS_INIT;
	int jobs;

	if (argc > 1 && !strcmp(argv[1], "testsuite"))
		exit(testsuite(argc - 1, argv + 1));

	if (argc < 3)
		return 1;
	while (!strcmp(argv[1], "env")) {
		if (!argv[2])
			die("env specifier without a value");
		argv_array_push(&proc.env_array, argv[2]);
		argv += 2;
		argc -= 2;
	}
	if (argc < 3)
		return 1;
	proc.argv = (const char **)argv + 2;

	if (!strcmp(argv[1], "start-command-ENOENT")) {
		if (start_command(&proc) < 0 && errno == ENOENT)
			return 0;
		fprintf(stderr, "FAIL %s\n", argv[1]);
		return 1;
	}
	if (!strcmp(argv[1], "run-command"))
		exit(run_command(&proc));

	jobs = atoi(argv[2]);
	proc.argv = (const char **)argv + 3;

	if (!strcmp(argv[1], "run-command-parallel"))
		exit(run_processes_parallel(jobs, parallel_next,
					    NULL, NULL, &proc));

	if (!strcmp(argv[1], "run-command-abort"))
		exit(run_processes_parallel(jobs, parallel_next,
					    NULL, task_finished, &proc));

	if (!strcmp(argv[1], "run-command-no-jobs"))
		exit(run_processes_parallel(jobs, no_job,
					    NULL, task_finished, &proc));

	fprintf(stderr, "check usage\n");
	return 1;
}