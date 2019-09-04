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
 int /*<<< orphan*/  clar_test_init (int,char**) ; 
 int clar_test_run () ; 
 int /*<<< orphan*/  clar_test_shutdown () ; 

int
clar_test(int argc, char **argv)
{
	int errors;

	clar_test_init(argc, argv);
	errors = clar_test_run();
	clar_test_shutdown();

	return errors;
}