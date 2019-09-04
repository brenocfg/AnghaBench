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
struct argv_array {scalar_t__ argv; } ;

/* Variables and functions */
 struct argv_array ARGV_ARRAY_INIT ; 
 int /*<<< orphan*/  argv_array_clear (struct argv_array*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  prepare_git_cmd (struct argv_array*,char const**) ; 
 int /*<<< orphan*/  sane_execvp (char*,char**) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_argv_printf (scalar_t__,char*) ; 
 int /*<<< orphan*/  trace_printf (char*,int /*<<< orphan*/ ) ; 

int execv_git_cmd(const char **argv)
{
	struct argv_array nargv = ARGV_ARRAY_INIT;

	prepare_git_cmd(&nargv, argv);
	trace_argv_printf(nargv.argv, "trace: exec:");

	/* execvp() can only ever return if it fails */
	sane_execvp("git", (char **)nargv.argv);

	trace_printf("trace: exec failed: %s\n", strerror(errno));

	argv_array_clear(&nargv);
	return -1;
}