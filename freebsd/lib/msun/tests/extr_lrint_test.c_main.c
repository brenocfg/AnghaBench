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
 int /*<<< orphan*/  FP_PE ; 
 int /*<<< orphan*/  fpsetprec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  run_tests () ; 

int
main(void)
{

	printf("1..1\n");

	run_tests();
#ifdef	__i386__
	fpsetprec(FP_PE);
	run_tests();
#endif

	printf("ok 1 - lrint\n");

	return (0);
}