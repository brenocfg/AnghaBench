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
struct device {int /*<<< orphan*/  kobj; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_device ; 
 int /*<<< orphan*/  cpu_online_attr_group ; 
 TYPE_1__* per_cpu (int /*<<< orphan*/ ,unsigned int) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smp_cpu_online(unsigned int cpu)
{
	struct device *s = &per_cpu(cpu_device, cpu)->dev;

	return sysfs_create_group(&s->kobj, &cpu_online_attr_group);
}