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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(const char *myname)
{
	fprintf(stderr, "usage: %s [-A [-][[hh]mm]SS] [-achm] [-r file] "
		"[-t [[CC]YY]MMDDhhmm[.SS]]\n"
		"       [-d YYYY-MM-DDThh:mm:SS[.frac][tz]] "
		"file ...\n", myname);
	exit(1);
}