#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* t_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 TYPE_1__* tests ; 
 int tests_count ; 

__attribute__((used)) static void
usage(void)
{
	int i;

	fprintf(stderr, "syscall_timing [-i iterations] [-l loops] "
	    "[-p path] [-s seconds] test\n");
	for (i = 0; i < tests_count; i++)
		fprintf(stderr, "  %s\n", tests[i].t_name);
	exit(-1);
}