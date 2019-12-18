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
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc_printf (char*,int) ; 
 int /*<<< orphan*/  mallocx (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_hooked (int) ; 
 int /*<<< orphan*/  test_unhooked (int) ; 

int
main(void) {
	/* Initialize */
	free(mallocx(1, 0));
	int iters = 10 * 1000 * 1000;
	malloc_printf("Benchmarking hooks with %d iterations:\n", iters);
	test_hooked(iters);
	test_unhooked(iters);
}