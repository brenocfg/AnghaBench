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
struct mips_cdmm_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct mips_cdmm_bus* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  cpu_has_cdmm ; 
 struct mips_cdmm_bus* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 struct mips_cdmm_bus mips_cdmm_boot_bus ; 
 int /*<<< orphan*/  mips_cdmm_buses ; 
 struct mips_cdmm_bus** per_cpu_ptr (int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int smp_processor_id () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct mips_cdmm_bus *mips_cdmm_get_bus(void)
{
	struct mips_cdmm_bus *bus, **bus_p;
	unsigned long flags;
	unsigned int cpu;

	if (!cpu_has_cdmm)
		return ERR_PTR(-ENODEV);

	cpu = smp_processor_id();
	/* Avoid early use of per-cpu primitives before initialised */
	if (cpu == 0)
		return &mips_cdmm_boot_bus;

	/* Get bus pointer */
	bus_p = per_cpu_ptr(&mips_cdmm_buses, cpu);
	local_irq_save(flags);
	bus = *bus_p;
	/* Attempt allocation if NULL */
	if (unlikely(!bus)) {
		bus = kzalloc(sizeof(*bus), GFP_ATOMIC);
		if (unlikely(!bus))
			bus = ERR_PTR(-ENOMEM);
		else
			*bus_p = bus;
	}
	local_irq_restore(flags);
	return bus;
}