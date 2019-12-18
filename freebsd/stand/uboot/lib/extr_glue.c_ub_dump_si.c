#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sys_info {int clk_bus; int clk_cpu; int mr_no; TYPE_1__* mr; int /*<<< orphan*/  bar; } ;
struct TYPE_2__ {scalar_t__ flags; int /*<<< orphan*/  size; int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 
 char* ub_mem_type (scalar_t__) ; 

void
ub_dump_si(struct sys_info *si)
{
	int i;

	printf("sys info:\n");
	printf("  clkbus\t= %ld MHz\n", si->clk_bus / 1000 / 1000);
	printf("  clkcpu\t= %ld MHz\n", si->clk_cpu / 1000 / 1000);
	printf("  bar\t\t= 0x%08lx\n", si->bar);

	printf("---\n");
	for (i = 0; i < si->mr_no; i++) {
		if (si->mr[i].flags == 0)
			break;

		printf("  start\t= 0x%08lx\n", si->mr[i].start);
		printf("  size\t= 0x%08lx\n", si->mr[i].size);
		printf("  type\t= %s\n", ub_mem_type(si->mr[i].flags));
		printf("---\n");
	}
}