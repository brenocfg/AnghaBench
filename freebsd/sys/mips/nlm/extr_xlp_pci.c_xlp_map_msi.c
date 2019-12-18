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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  MIPS_MSI_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIPS_MSI_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIC_PCIE_IRQ (int) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
xlp_map_msi(device_t pcib, device_t dev, int irq, uint64_t *addr,
    uint32_t *data)
{
	int link;

	if (irq < 64) {
		device_printf(dev, "%s: map_msi for irq %d  - ignored",
		    device_get_nameunit(pcib), irq);
		return (ENXIO);
	}
	link = (irq - 64) / 32;
	*addr = MIPS_MSI_ADDR(0);
	*data = MIPS_MSI_DATA(PIC_PCIE_IRQ(link));
	return (0);
}