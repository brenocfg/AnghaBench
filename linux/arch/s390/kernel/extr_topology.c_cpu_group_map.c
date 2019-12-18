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
struct mask_info {struct mask_info* next; int /*<<< orphan*/  mask; } ;
typedef  int /*<<< orphan*/  cpumask_t ;

/* Variables and functions */
#define  TOPOLOGY_MODE_HW 130 
#define  TOPOLOGY_MODE_PACKAGE 129 
#define  TOPOLOGY_MODE_SINGLE 128 
 int /*<<< orphan*/  cpu_present_mask ; 
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_of (unsigned int) ; 
 int /*<<< orphan*/  cpumask_test_cpu (unsigned int,int /*<<< orphan*/ *) ; 
 int topology_mode ; 

__attribute__((used)) static cpumask_t cpu_group_map(struct mask_info *info, unsigned int cpu)
{
	cpumask_t mask;

	cpumask_copy(&mask, cpumask_of(cpu));
	switch (topology_mode) {
	case TOPOLOGY_MODE_HW:
		while (info) {
			if (cpumask_test_cpu(cpu, &info->mask)) {
				mask = info->mask;
				break;
			}
			info = info->next;
		}
		if (cpumask_empty(&mask))
			cpumask_copy(&mask, cpumask_of(cpu));
		break;
	case TOPOLOGY_MODE_PACKAGE:
		cpumask_copy(&mask, cpu_present_mask);
		break;
	default:
		/* fallthrough */
	case TOPOLOGY_MODE_SINGLE:
		cpumask_copy(&mask, cpumask_of(cpu));
		break;
	}
	return mask;
}