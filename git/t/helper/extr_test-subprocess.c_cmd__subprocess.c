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
struct child_process {int git_cmd; char const** argv; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 int /*<<< orphan*/  die (char*) ; 
 int run_command (struct child_process*) ; 
 int /*<<< orphan*/  setup_git_directory_gently (int*) ; 
 int /*<<< orphan*/  setup_work_tree () ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

int cmd__subprocess(int argc, const char **argv)
{
	struct child_process cp = CHILD_PROCESS_INIT;
	int nogit = 0;

	setup_git_directory_gently(&nogit);
	if (nogit)
		die("No git repo found");
	if (argc > 1 && !strcmp(argv[1], "--setup-work-tree")) {
		setup_work_tree();
		argv++;
	}
	cp.git_cmd = 1;
	cp.argv = (const char **)argv + 1;
	return run_command(&cp);
}