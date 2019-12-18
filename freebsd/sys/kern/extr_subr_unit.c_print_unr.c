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
typedef  scalar_t__ u_int ;
struct unrhdr {int /*<<< orphan*/  map; } ;
struct unrb {int /*<<< orphan*/  map; } ;
struct unr {int len; struct unrhdr* ptr; } ;

/* Variables and functions */
 scalar_t__ bit_test (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
print_unr(struct unrhdr *uh, struct unr *up)
{
	u_int x;
	struct unrb *ub;

	printf("  %p len = %5u ", up, up->len);
	if (up->ptr == NULL)
		printf("free\n");
	else if (up->ptr == uh)
		printf("alloc\n");
	else {
		ub = up->ptr;
		printf("bitmap [");
		for (x = 0; x < up->len; x++) {
			if (bit_test(ub->map, x))
				printf("#");
			else
				printf(" ");
		}
		printf("]\n");
	}
}