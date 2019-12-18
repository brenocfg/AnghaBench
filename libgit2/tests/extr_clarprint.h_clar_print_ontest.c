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
typedef  enum cl_test_status { ____Placeholder_cl_test_status } cl_test_status ;

/* Variables and functions */
#define  CL_TEST_FAILURE 131 
#define  CL_TEST_NOTRUN 130 
#define  CL_TEST_OK 129 
#define  CL_TEST_SKIP 128 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void clar_print_ontest(const char *test_name, int test_number, enum cl_test_status status)
{
	(void)test_name;
	(void)test_number;

	switch(status) {
	case CL_TEST_OK: printf("."); break;
	case CL_TEST_FAILURE: printf("F"); break;
	case CL_TEST_SKIP: printf("S"); break;
	case CL_TEST_NOTRUN: printf("N"); break;
	}

	fflush(stdout);
}