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
 int /*<<< orphan*/  die (char*) ; 
 int execv_git_cmd (char const**) ; 
 int /*<<< orphan*/  setup_path () ; 
 char* sq_dequote (char*) ; 
 int /*<<< orphan*/  starts_with (char const*,char*) ; 

__attribute__((used)) static int do_generic_cmd(const char *me, char *arg)
{
	const char *my_argv[4];

	setup_path();
	if (!arg || !(arg = sq_dequote(arg)) || *arg == '-')
		die("bad argument");
	if (!starts_with(me, "git-"))
		die("bad command");

	my_argv[0] = me + 4;
	my_argv[1] = arg;
	my_argv[2] = NULL;

	return execv_git_cmd(my_argv);
}