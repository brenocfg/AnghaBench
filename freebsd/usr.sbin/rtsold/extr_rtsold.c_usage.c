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
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static void
usage(const char *progname)
{

	if (strcmp(progname, "rtsold") == 0) {
		fprintf(stderr, "usage: rtsold [-dDfFm1] [-O script-name] "
		    "[-p pidfile] [-R script-name] interface ...\n");
		fprintf(stderr, "usage: rtsold [-dDfFm1] [-O script-name] "
		    "[-p pidfile] [-R script-name] -a\n");
	} else {
		fprintf(stderr, "usage: rtsol [-dDF] [-O script-name] "
		    "[-p pidfile] [-R script-name] interface ...\n");
		fprintf(stderr, "usage: rtsol [-dDF] [-O script-name] "
		    "[-p pidfile] [-R script-name] -a\n");
	}
	exit(1);
}