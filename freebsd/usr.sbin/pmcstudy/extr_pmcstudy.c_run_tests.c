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
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  test_for_a_pmc (char*,int) ; 
 int valid_pmc_cnt ; 
 char** valid_pmcs ; 

__attribute__((used)) static void
run_tests(void)
{
	int i, lenout;
	printf("Running tests on %d PMC's this may take some time\n", valid_pmc_cnt);
	printf("------------------------------------------------------------------------\n");
	for(i=0; i<valid_pmc_cnt; i++) {
		lenout = printf("%s", valid_pmcs[i]);
		fflush(stdout);
		test_for_a_pmc(valid_pmcs[i], lenout);
	}
}