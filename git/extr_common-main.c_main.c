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
 int /*<<< orphan*/  TRACE2_PROCESS_INFO_STARTUP ; 
 int /*<<< orphan*/  attr_start () ; 
 int cmd_main (int,char const**) ; 
 int /*<<< orphan*/  git_resolve_executable_dir (char const*) ; 
 int /*<<< orphan*/  git_setup_gettext () ; 
 int /*<<< orphan*/  initialize_the_repository () ; 
 int /*<<< orphan*/  restore_sigpipe_to_default () ; 
 int /*<<< orphan*/  sanitize_stdfds () ; 
 int /*<<< orphan*/  trace2_cmd_exit (int) ; 
 int /*<<< orphan*/  trace2_cmd_start (char const**) ; 
 int /*<<< orphan*/  trace2_collect_process_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace2_initialize () ; 
 int /*<<< orphan*/  trace2_initialize_clock () ; 

int main(int argc, const char **argv)
{
	int result;

	trace2_initialize_clock();

	/*
	 * Always open file descriptors 0/1/2 to avoid clobbering files
	 * in die().  It also avoids messing up when the pipes are dup'ed
	 * onto stdin/stdout/stderr in the child processes we spawn.
	 */
	sanitize_stdfds();
	restore_sigpipe_to_default();

	git_resolve_executable_dir(argv[0]);

	git_setup_gettext();

	initialize_the_repository();

	attr_start();

	trace2_initialize();
	trace2_cmd_start(argv);
	trace2_collect_process_info(TRACE2_PROCESS_INFO_STARTUP);

	result = cmd_main(argc, argv);

	trace2_cmd_exit(result);

	return result;
}