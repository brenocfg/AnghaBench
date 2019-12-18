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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct bcma_device {int dummy; } ;
struct bcma_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcma_core_mips_set_irq (struct bcma_device*,unsigned int) ; 
 struct bcma_device* bcma_find_core_unit (struct bcma_bus*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_warn (struct bcma_bus*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcma_core_mips_set_irq_name(struct bcma_bus *bus, unsigned int irq,
					u16 coreid, u8 unit)
{
	struct bcma_device *core;

	core = bcma_find_core_unit(bus, coreid, unit);
	if (!core) {
		bcma_warn(bus,
			  "Can not find core (id: 0x%x, unit %i) for IRQ configuration.\n",
			  coreid, unit);
		return;
	}

	bcma_core_mips_set_irq(core, irq);
}