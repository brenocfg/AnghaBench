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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  cpumask_var_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HK_FLAG_DOMAIN ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  alloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_possible_mask ; 
 int /*<<< orphan*/  cpumask_andnot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_pr_args (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  housekeeping_cpumask (int /*<<< orphan*/ ) ; 
 int scnprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t print_cpus_isolated(struct device *dev,
				  struct device_attribute *attr, char *buf)
{
	int n = 0, len = PAGE_SIZE-2;
	cpumask_var_t isolated;

	if (!alloc_cpumask_var(&isolated, GFP_KERNEL))
		return -ENOMEM;

	cpumask_andnot(isolated, cpu_possible_mask,
		       housekeeping_cpumask(HK_FLAG_DOMAIN));
	n = scnprintf(buf, len, "%*pbl\n", cpumask_pr_args(isolated));

	free_cpumask_var(isolated);

	return n;
}