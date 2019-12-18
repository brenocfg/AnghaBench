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
 char* getprogname () ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{

	fprintf(stderr,
                "usage: %s -f device "
                "[-l] [-n] [-r] [-t tablefile] [-v] [-x] [-z] name ...\n",
                getprogname());
	fprintf(stderr,
                "       %s -f device "
                "[-l] [-n] [-r] [-t tablefile] [-v] [-x] [-z] -a\n",
                getprogname());
	fprintf(stderr,
                "       %s -f device "
                "[-t tablefile] [-v] [-z] -w name=value\n",
                getprogname());
	exit(1);
}