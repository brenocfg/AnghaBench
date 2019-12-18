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

/* Variables and functions */
 int /*<<< orphan*/  IRQ_LEVEL_LOW ; 
 int /*<<< orphan*/  IRQ_SIGNAL_THROUGH ; 
 int /*<<< orphan*/  IRQ_TRIGGER_LEVEL ; 
 int /*<<< orphan*/  TB0219_PCI_SLOT1_PIN ; 
 int /*<<< orphan*/  TB0219_PCI_SLOT2_PIN ; 
 int /*<<< orphan*/  TB0219_PCI_SLOT3_PIN ; 
 int /*<<< orphan*/  vr41xx_set_irq_level (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vr41xx_set_irq_trigger (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tb0219_pci_irq_init(void)
{
	/* PCI Slot 1 */
	vr41xx_set_irq_trigger(TB0219_PCI_SLOT1_PIN, IRQ_TRIGGER_LEVEL, IRQ_SIGNAL_THROUGH);
	vr41xx_set_irq_level(TB0219_PCI_SLOT1_PIN, IRQ_LEVEL_LOW);

	/* PCI Slot 2 */
	vr41xx_set_irq_trigger(TB0219_PCI_SLOT2_PIN, IRQ_TRIGGER_LEVEL, IRQ_SIGNAL_THROUGH);
	vr41xx_set_irq_level(TB0219_PCI_SLOT2_PIN, IRQ_LEVEL_LOW);

	/* PCI Slot 3 */
	vr41xx_set_irq_trigger(TB0219_PCI_SLOT3_PIN, IRQ_TRIGGER_LEVEL, IRQ_SIGNAL_THROUGH);
	vr41xx_set_irq_level(TB0219_PCI_SLOT3_PIN, IRQ_LEVEL_LOW);
}