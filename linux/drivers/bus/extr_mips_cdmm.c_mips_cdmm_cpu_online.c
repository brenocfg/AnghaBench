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
struct mips_cdmm_bus {int offline; int /*<<< orphan*/  discovered; } ;

/* Variables and functions */
 long bus_for_each_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_cdmm_bus_discover (struct mips_cdmm_bus*) ; 
 int /*<<< orphan*/  mips_cdmm_bustype ; 
 int /*<<< orphan*/  mips_cdmm_cpu_up_helper ; 
 struct mips_cdmm_bus* mips_cdmm_get_bus () ; 
 long mips_cdmm_setup (struct mips_cdmm_bus*) ; 

__attribute__((used)) static int mips_cdmm_cpu_online(unsigned int cpu)
{
	struct mips_cdmm_bus *bus;
	long ret;

	bus = mips_cdmm_get_bus();
	ret = mips_cdmm_setup(bus);
	if (ret)
		return ret;

	/* Bus now set up, so we can drop the offline flag if still set */
	bus->offline = false;

	if (!bus->discovered)
		mips_cdmm_bus_discover(bus);
	else
		/* Inform all the devices on the bus */
		ret = bus_for_each_dev(&mips_cdmm_bustype, NULL, &cpu,
				       mips_cdmm_cpu_up_helper);

	return ret;
}