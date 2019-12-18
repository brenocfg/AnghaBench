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
struct teo_cpu {int /*<<< orphan*/ * intervals; } ;
struct cpuidle_driver {int dummy; } ;
struct cpuidle_device {int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int INTERVALS ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int /*<<< orphan*/  memset (struct teo_cpu*,int /*<<< orphan*/ ,int) ; 
 struct teo_cpu* per_cpu_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  teo_cpus ; 

__attribute__((used)) static int teo_enable_device(struct cpuidle_driver *drv,
			     struct cpuidle_device *dev)
{
	struct teo_cpu *cpu_data = per_cpu_ptr(&teo_cpus, dev->cpu);
	int i;

	memset(cpu_data, 0, sizeof(*cpu_data));

	for (i = 0; i < INTERVALS; i++)
		cpu_data->intervals[i] = UINT_MAX;

	return 0;
}