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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

void
usage(void)
{
	extern char *__progname;

	fprintf(stderr,
"usage: %s [-AdeghmNnOPqRrvz] [-a anchor] [-D macro=value] [-F modifier]\n"
	"\t[-f file] [-i interface] [-K host | network]\n"
	"\t[-k host | network | label | id] [-o level] [-p device]\n"
	"\t[-s modifier] [-t table -T command [address ...]] [-x level]\n",
	    __progname);

	exit(1);
}