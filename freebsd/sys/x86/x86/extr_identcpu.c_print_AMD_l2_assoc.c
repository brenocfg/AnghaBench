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

__attribute__((used)) static void
print_AMD_l2_assoc(int i)
{
	switch (i & 0x0f) {
	case 0: printf(", disabled/not present\n"); break;
	case 1: printf(", direct mapped\n"); break;
	case 2: printf(", 2-way associative\n"); break;
	case 4: printf(", 4-way associative\n"); break;
	case 6: printf(", 8-way associative\n"); break;
	case 8: printf(", 16-way associative\n"); break;
	case 15: printf(", fully associative\n"); break;
	default: printf(", reserved configuration\n"); break;
	}
}