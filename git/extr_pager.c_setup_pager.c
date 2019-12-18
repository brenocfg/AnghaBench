#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {int in; int /*<<< orphan*/  env_array; } ;

/* Variables and functions */
 int /*<<< orphan*/  argv_array_push (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 char* git_pager (scalar_t__) ; 
 scalar_t__ isatty (int) ; 
 TYPE_1__ pager_process ; 
 int /*<<< orphan*/  prepare_pager_args (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 
 int /*<<< orphan*/  sigchain_push_common (int /*<<< orphan*/ ) ; 
 scalar_t__ start_command (TYPE_1__*) ; 
 int /*<<< orphan*/  term_columns () ; 
 int /*<<< orphan*/  wait_for_pager_atexit ; 
 int /*<<< orphan*/  wait_for_pager_signal ; 
 int /*<<< orphan*/  xsnprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

void setup_pager(void)
{
	const char *pager = git_pager(isatty(1));

	if (!pager)
		return;

	/*
	 * After we redirect standard output, we won't be able to use an ioctl
	 * to get the terminal size. Let's grab it now, and then set $COLUMNS
	 * to communicate it to any sub-processes.
	 */
	{
		char buf[64];
		xsnprintf(buf, sizeof(buf), "%d", term_columns());
		setenv("COLUMNS", buf, 0);
	}

	setenv("GIT_PAGER_IN_USE", "true", 1);

	/* spawn the pager */
	prepare_pager_args(&pager_process, pager);
	pager_process.in = -1;
	argv_array_push(&pager_process.env_array, "GIT_PAGER_IN_USE");
	if (start_command(&pager_process))
		return;

	/* original process continues, but writes to the pipe */
	dup2(pager_process.in, 1);
	if (isatty(2))
		dup2(pager_process.in, 2);
	close(pager_process.in);

	/* this makes sure that the parent terminates after the pager */
	sigchain_push_common(wait_for_pager_signal);
	atexit(wait_for_pager_atexit);
}