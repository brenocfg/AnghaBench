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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  size_t u_int ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 size_t MAXCPU ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/ * cpu_get_cpuid (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/ ** cpu_list ; 
 size_t device_get_unit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*) ; 
 size_t mp_maxid ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
riscv64_cpu_attach(device_t dev)
{
	const uint32_t *reg;
	size_t reg_size;
	u_int cpuid;
	int i;

	cpuid = device_get_unit(dev);

	if (cpuid >= MAXCPU || cpuid > mp_maxid)
		return (EINVAL);
	KASSERT(cpu_list[cpuid] == NULL, ("Already have cpu %u", cpuid));

	reg = cpu_get_cpuid(dev, &reg_size);
	if (reg == NULL)
		return (EINVAL);

	if (bootverbose) {
		device_printf(dev, "register <");
		for (i = 0; i < reg_size; i++)
			printf("%s%x", (i == 0) ? "" : " ", reg[i]);
		printf(">\n");
	}

	/* Set the device to start it later */
	cpu_list[cpuid] = dev;

	return (0);
}