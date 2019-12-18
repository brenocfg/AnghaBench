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
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ is_daemon ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{
	if (is_daemon)
		fprintf(stderr, "usage:\n"
"  watchdogd [-dnSw] [-e cmd] [-I pidfile] [-s sleep] [-t timeout]\n"
"            [-T script_timeout] [-x exit_timeout]\n"
"            [--debug]\n"
"            [--pretimeout seconds] [-pretimeout-action action]\n"
"            [--softtimeout] [-softtimeout-action action]\n"
);
	else
		fprintf(stderr, "usage: watchdog [-d] [-t timeout]\n");
	exit(EX_USAGE);
}