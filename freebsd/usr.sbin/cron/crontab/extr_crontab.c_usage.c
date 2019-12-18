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
 int /*<<< orphan*/  ERROR_EXIT ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(char *msg)
{
	fprintf(stderr, "crontab: usage error: %s\n", msg);
	fprintf(stderr, "%s\n%s\n",
		"usage: crontab [-u user] file",
		"       crontab [-u user] { -l | -r [-f] | -e }");
	exit(ERROR_EXIT);
}