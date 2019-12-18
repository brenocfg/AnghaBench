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
typedef  scalar_t__ U8 ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
print_spare_pools(U8 HotSparePool)
{
	int i;

	if (HotSparePool == 0) {
		printf("none");
		return;
	}
	for (i = 0; HotSparePool != 0; i++) {
		if (HotSparePool & 1) {
			printf("%d", i);
			if (HotSparePool == 1)
				break;
			printf(", ");
		}
		HotSparePool >>= 1;
	}
}