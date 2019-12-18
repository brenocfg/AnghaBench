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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MAXCPU ; 
 scalar_t__ device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_quiet (int /*<<< orphan*/ ) ; 
 scalar_t__ mp_maxid ; 

__attribute__((used)) static int
riscv64_cpu_probe(device_t dev)
{
	u_int cpuid;

	cpuid = device_get_unit(dev);
	if (cpuid >= MAXCPU || cpuid > mp_maxid)
		return (EINVAL);

	device_quiet(dev);
	return (0);
}