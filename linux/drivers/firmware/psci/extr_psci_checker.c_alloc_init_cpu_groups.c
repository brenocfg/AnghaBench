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
struct cpumask {int dummy; } ;
typedef  int /*<<< orphan*/  cpumask_var_t ;
typedef  int /*<<< orphan*/  cpu_groups ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  alloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct cpumask const* cpu_online_mask ; 
 int /*<<< orphan*/  cpumask_andnot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cpumask const*) ; 
 int /*<<< orphan*/  cpumask_any (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ ,struct cpumask const*) ; 
 int /*<<< orphan*/  cpumask_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_cpu_groups (int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nb_available_cpus ; 
 struct cpumask* topology_core_cpumask (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alloc_init_cpu_groups(cpumask_var_t **pcpu_groups)
{
	int num_groups = 0;
	cpumask_var_t tmp, *cpu_groups;

	if (!alloc_cpumask_var(&tmp, GFP_KERNEL))
		return -ENOMEM;

	cpu_groups = kcalloc(nb_available_cpus, sizeof(cpu_groups),
			     GFP_KERNEL);
	if (!cpu_groups)
		return -ENOMEM;

	cpumask_copy(tmp, cpu_online_mask);

	while (!cpumask_empty(tmp)) {
		const struct cpumask *cpu_group =
			topology_core_cpumask(cpumask_any(tmp));

		if (!alloc_cpumask_var(&cpu_groups[num_groups], GFP_KERNEL)) {
			free_cpu_groups(num_groups, &cpu_groups);
			return -ENOMEM;
		}
		cpumask_copy(cpu_groups[num_groups++], cpu_group);
		cpumask_andnot(tmp, tmp, cpu_group);
	}

	free_cpumask_var(tmp);
	*pcpu_groups = cpu_groups;

	return num_groups;
}