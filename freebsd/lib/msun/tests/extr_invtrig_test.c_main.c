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
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  test_accuracy () ; 
 int /*<<< orphan*/  test_atan_huge () ; 
 int /*<<< orphan*/  test_inverse () ; 
 int /*<<< orphan*/  test_p2x_atan2 () ; 
 int /*<<< orphan*/  test_special () ; 
 int /*<<< orphan*/  test_special_atan2 () ; 
 int /*<<< orphan*/  test_tiny () ; 

int
main(void)
{

#if defined(__i386__)
	printf("1..0 # SKIP fails all assertions on i386\n");
	return (0);
#endif

	printf("1..7\n");

	test_special();
	printf("ok 1 - special\n");

	test_special_atan2();
	printf("ok 2 - atan2 special\n");

	test_accuracy();
	printf("ok 3 - accuracy\n");

	test_p2x_atan2();
	printf("ok 4 - atan2 p2x\n");

	test_tiny();
	printf("ok 5 - tiny inputs\n");

	test_atan_huge();
	printf("ok 6 - atan huge inputs\n");

	test_inverse();
	printf("ok 7 - inverse\n");

	return (0);
}