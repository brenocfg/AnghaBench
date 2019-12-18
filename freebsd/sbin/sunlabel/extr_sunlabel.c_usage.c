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
 char* __progname ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{

	fprintf(stderr, "usage:"
"\t%s [-r] [-c | -h] disk\n"
"\t\t(to read label)\n"
"\t%s -B [-b boot1] [-n] disk\n"
"\t\t(to install boot program only)\n"
"\t%s -R [-B [-b boot1]] [-r] [-n] [-c] disk protofile\n"
"\t\t(to restore label)\n"
"\t%s -e [-B [-b boot1]] [-r] [-n] [-c] disk\n"
"\t\t(to edit label)\n"
"\t%s -w [-B [-b boot1]] [-r] [-n] disk type\n"
"\t\t(to write default label)\n",
	     __progname,
	     __progname,
	     __progname,
	     __progname,
	     __progname);
	exit(1);
}