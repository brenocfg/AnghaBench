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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

__attribute__((used)) static void
usage(const char *cp)
{
	if (cp != NULL)
		warnx("%s", cp);
	(void)fprintf(stderr,
	    "usage: shutdown [-] [-c | -h | -p | -r | -k] [-o [-n]] time [warning-message ...]\n"
	    "       poweroff\n");
	exit(1);
}