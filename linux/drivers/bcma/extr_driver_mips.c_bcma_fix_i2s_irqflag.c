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
struct bcma_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ id; } ;
struct bcma_bus {TYPE_1__ chipinfo; } ;

/* Variables and functions */
 scalar_t__ BCMA_CHIP_ID_BCM4716 ; 
 scalar_t__ BCMA_CHIP_ID_BCM4748 ; 
 int /*<<< orphan*/  BCMA_CORE_I2S ; 
 int /*<<< orphan*/  BCMA_CORE_MIPS_74K ; 
 int /*<<< orphan*/  BCMA_CORE_PCIE ; 
 int /*<<< orphan*/  BCMA_MIPS_OOBSELINA74 ; 
 int /*<<< orphan*/  BCMA_MIPS_OOBSELOUTA30 ; 
 int bcma_aread32 (struct bcma_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_awrite32 (struct bcma_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bcma_debug (struct bcma_bus*,char*) ; 
 struct bcma_device* bcma_find_core (struct bcma_bus*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcma_fix_i2s_irqflag(struct bcma_bus *bus)
{
	struct bcma_device *cpu, *pcie, *i2s;

	/* Fixup the interrupts in 4716/4748 for i2s core (2010 Broadcom SDK)
	 * (IRQ flags > 7 are ignored when setting the interrupt masks)
	 */
	if (bus->chipinfo.id != BCMA_CHIP_ID_BCM4716 &&
	    bus->chipinfo.id != BCMA_CHIP_ID_BCM4748)
		return;

	cpu = bcma_find_core(bus, BCMA_CORE_MIPS_74K);
	pcie = bcma_find_core(bus, BCMA_CORE_PCIE);
	i2s = bcma_find_core(bus, BCMA_CORE_I2S);
	if (cpu && pcie && i2s &&
	    bcma_aread32(cpu, BCMA_MIPS_OOBSELINA74) == 0x08060504 &&
	    bcma_aread32(pcie, BCMA_MIPS_OOBSELINA74) == 0x08060504 &&
	    bcma_aread32(i2s, BCMA_MIPS_OOBSELOUTA30) == 0x88) {
		bcma_awrite32(cpu, BCMA_MIPS_OOBSELINA74, 0x07060504);
		bcma_awrite32(pcie, BCMA_MIPS_OOBSELINA74, 0x07060504);
		bcma_awrite32(i2s, BCMA_MIPS_OOBSELOUTA30, 0x87);
		bcma_debug(bus,
			   "Moved i2s interrupt to oob line 7 instead of 8\n");
	}
}