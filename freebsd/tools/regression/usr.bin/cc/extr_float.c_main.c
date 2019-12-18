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
 int failures ; 
 int /*<<< orphan*/  fpsetprec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  run_tests () ; 

int
main(int argc, char *argv[])
{

	printf("1..26\n");

#ifdef  __i386__
	fpsetprec(FP_PE);
#endif
	run_tests();

	return (failures);
}