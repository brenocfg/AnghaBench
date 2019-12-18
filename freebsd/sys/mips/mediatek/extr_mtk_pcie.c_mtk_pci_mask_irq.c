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
 int /*<<< orphan*/  MTK_PCI_PCIENA ; 
 int MT_READ32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT_WRITE32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt_sc ; 

__attribute__((used)) static void
mtk_pci_mask_irq(void *source)
{
	MT_WRITE32(mt_sc, MTK_PCI_PCIENA,
		MT_READ32(mt_sc, MTK_PCI_PCIENA) & ~(1<<((int)source)));
}