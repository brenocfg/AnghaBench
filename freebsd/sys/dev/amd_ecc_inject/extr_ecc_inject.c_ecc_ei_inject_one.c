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
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int DRAM_ECC_SEL ; 
 int DRAM_WR_REQ ; 
 int INJ_WORD_SHIFT ; 
 int /*<<< orphan*/  NB_ARRAY_ADDR ; 
 int /*<<< orphan*/  NB_ARRAY_PORT ; 
 int QUADRANT_SHIFT ; 
 int bit_mask ; 
 int /*<<< orphan*/  nbdev ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int quadrant ; 
 int word_mask ; 

__attribute__((used)) static void
ecc_ei_inject_one(void *arg, size_t size)
{
	volatile uint64_t *memory = arg;
	uint32_t val;
	int i;

	val = DRAM_ECC_SEL | (quadrant << QUADRANT_SHIFT);
	pci_write_config(nbdev, NB_ARRAY_ADDR, val, 4);

	val = (word_mask << INJ_WORD_SHIFT) | DRAM_WR_REQ | bit_mask;
	pci_write_config(nbdev, NB_ARRAY_PORT, val, 4);

	for (i = 0; i < size / sizeof(uint64_t); i++) {
		memory[i] = 0;
		val = pci_read_config(nbdev, NB_ARRAY_PORT, 4);
		if ((val & DRAM_WR_REQ) == 0)
			break;
	}
	for (i = 0; i < size / sizeof(uint64_t); i++)
		memory[0] = memory[i];
}