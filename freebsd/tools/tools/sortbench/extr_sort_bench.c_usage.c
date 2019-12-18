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
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
usage(const char *progname)
{
	printf("Usage:\n");
	printf("\t%s: [alg] [test] [runs] [elt_power]\n", progname);
	printf("\n");
	printf("Valid algs:\n");
#ifdef WIKI
	printf("\theap merge quick wiki\n");
#else
	printf("\theap merge quick\n");
#endif
	printf("Valid tests:\n");
	printf("\trand sort part rev\n");
	printf("\trand: Random element array \n");
	printf("\tsort: Increasing order array \n");
	printf("\tpart: Partially ordered array\n");
	printf("\trev: Decreasing order array\n");
	printf("Run the algorithm [runs] times with 2^[elt_power] elements\n");
	exit(EX_USAGE);
}