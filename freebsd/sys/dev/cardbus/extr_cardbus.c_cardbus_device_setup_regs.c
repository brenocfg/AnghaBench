#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int intline; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ pcicfgregs ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCIR_BAR (int) ; 
 int /*<<< orphan*/  PCIR_CACHELNSZ ; 
 int /*<<< orphan*/  PCIR_INTLINE ; 
 int /*<<< orphan*/  PCIR_LATTIMER ; 
 int /*<<< orphan*/  PCIR_MAXLAT ; 
 int PCIR_MAX_BAR_0 ; 
 int /*<<< orphan*/  PCIR_MINGNT ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int pci_get_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
cardbus_device_setup_regs(pcicfgregs *cfg)
{
	device_t dev = cfg->dev;
	int i;

	/*
	 * Some cards power up with garbage in their BARs.  This
	 * code clears all that junk out.
	 */
	for (i = 0; i < PCIR_MAX_BAR_0; i++)
		pci_write_config(dev, PCIR_BAR(i), 0, 4);

	cfg->intline =
	    pci_get_irq(device_get_parent(device_get_parent(dev)));
	pci_write_config(dev, PCIR_INTLINE, cfg->intline, 1);
	pci_write_config(dev, PCIR_CACHELNSZ, 0x08, 1);
	pci_write_config(dev, PCIR_LATTIMER, 0xa8, 1);
	pci_write_config(dev, PCIR_MINGNT, 0x14, 1);
	pci_write_config(dev, PCIR_MAXLAT, 0x14, 1);
}