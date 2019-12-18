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
 unsigned int nitems (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,size_t) ; 
 int /*<<< orphan*/  test_modf (unsigned int) ; 
 int /*<<< orphan*/  test_nearby (unsigned int) ; 
 int testnum ; 
 int /*<<< orphan*/  tests ; 

int
main(void)
{
	unsigned i;

	printf("1..%zu\n", (size_t)(nitems(tests) * 2));
	testnum = 1;
	for (i = 0; i < nitems(tests); i++) {
		test_nearby(i);
		test_modf(i);
	}

	return (0);
}