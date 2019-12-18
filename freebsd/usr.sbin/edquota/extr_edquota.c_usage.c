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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,char*,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{
	fprintf(stderr, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
		"usage: edquota [-uh] [-f fspath] [-p username] username ...",
		"       edquota [-u] -e fspath[:bslim[:bhlim[:islim[:ihlim]]]] [-e ...]",
		"               username ...",
		"       edquota -g [-h] [-f fspath] [-p groupname] groupname ...",
		"       edquota -g -e fspath[:bslim[:bhlim[:islim[:ihlim]]]] [-e ...]",
		"               groupname ...",
		"       edquota [-u] -t [-f fspath]",
		"       edquota -g -t [-f fspath]");
	exit(1);
}