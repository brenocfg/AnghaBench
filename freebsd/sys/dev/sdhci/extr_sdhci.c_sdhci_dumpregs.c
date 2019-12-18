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
struct sdhci_slot {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RD1 (struct sdhci_slot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RD2 (struct sdhci_slot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RD4 (struct sdhci_slot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDHCI_ACMD12_ERR ; 
 int /*<<< orphan*/  SDHCI_ADMA_ADDRESS_LO ; 
 int /*<<< orphan*/  SDHCI_ADMA_ERR ; 
 int /*<<< orphan*/  SDHCI_ARGUMENT ; 
 int /*<<< orphan*/  SDHCI_BLOCK_COUNT ; 
 int /*<<< orphan*/  SDHCI_BLOCK_GAP_CONTROL ; 
 int /*<<< orphan*/  SDHCI_BLOCK_SIZE ; 
 int /*<<< orphan*/  SDHCI_CAPABILITIES ; 
 int /*<<< orphan*/  SDHCI_CAPABILITIES2 ; 
 int /*<<< orphan*/  SDHCI_CLOCK_CONTROL ; 
 int /*<<< orphan*/  SDHCI_DMA_ADDRESS ; 
 int /*<<< orphan*/  SDHCI_HOST_CONTROL ; 
 int /*<<< orphan*/  SDHCI_HOST_CONTROL2 ; 
 int /*<<< orphan*/  SDHCI_HOST_VERSION ; 
 int /*<<< orphan*/  SDHCI_INT_ENABLE ; 
 int /*<<< orphan*/  SDHCI_INT_STATUS ; 
 int /*<<< orphan*/  SDHCI_MAX_CURRENT ; 
 int /*<<< orphan*/  SDHCI_POWER_CONTROL ; 
 int /*<<< orphan*/  SDHCI_PRESENT_STATE ; 
 int /*<<< orphan*/  SDHCI_SIGNAL_ENABLE ; 
 int /*<<< orphan*/  SDHCI_SLOT_INT_STATUS ; 
 int /*<<< orphan*/  SDHCI_TIMEOUT_CONTROL ; 
 int /*<<< orphan*/  SDHCI_TRANSFER_MODE ; 
 int /*<<< orphan*/  SDHCI_WAKE_UP_CONTROL ; 
 int /*<<< orphan*/  slot_printf (struct sdhci_slot*,char*,...) ; 

__attribute__((used)) static void
sdhci_dumpregs(struct sdhci_slot *slot)
{

	slot_printf(slot,
	    "============== REGISTER DUMP ==============\n");

	slot_printf(slot, "Sys addr: 0x%08x | Version:  0x%08x\n",
	    RD4(slot, SDHCI_DMA_ADDRESS), RD2(slot, SDHCI_HOST_VERSION));
	slot_printf(slot, "Blk size: 0x%08x | Blk cnt:  0x%08x\n",
	    RD2(slot, SDHCI_BLOCK_SIZE), RD2(slot, SDHCI_BLOCK_COUNT));
	slot_printf(slot, "Argument: 0x%08x | Trn mode: 0x%08x\n",
	    RD4(slot, SDHCI_ARGUMENT), RD2(slot, SDHCI_TRANSFER_MODE));
	slot_printf(slot, "Present:  0x%08x | Host ctl: 0x%08x\n",
	    RD4(slot, SDHCI_PRESENT_STATE), RD1(slot, SDHCI_HOST_CONTROL));
	slot_printf(slot, "Power:    0x%08x | Blk gap:  0x%08x\n",
	    RD1(slot, SDHCI_POWER_CONTROL), RD1(slot, SDHCI_BLOCK_GAP_CONTROL));
	slot_printf(slot, "Wake-up:  0x%08x | Clock:    0x%08x\n",
	    RD1(slot, SDHCI_WAKE_UP_CONTROL), RD2(slot, SDHCI_CLOCK_CONTROL));
	slot_printf(slot, "Timeout:  0x%08x | Int stat: 0x%08x\n",
	    RD1(slot, SDHCI_TIMEOUT_CONTROL), RD4(slot, SDHCI_INT_STATUS));
	slot_printf(slot, "Int enab: 0x%08x | Sig enab: 0x%08x\n",
	    RD4(slot, SDHCI_INT_ENABLE), RD4(slot, SDHCI_SIGNAL_ENABLE));
	slot_printf(slot, "AC12 err: 0x%08x | Host ctl2:0x%08x\n",
	    RD2(slot, SDHCI_ACMD12_ERR), RD2(slot, SDHCI_HOST_CONTROL2));
	slot_printf(slot, "Caps:     0x%08x | Caps2:    0x%08x\n",
	    RD4(slot, SDHCI_CAPABILITIES), RD4(slot, SDHCI_CAPABILITIES2));
	slot_printf(slot, "Max curr: 0x%08x | ADMA err: 0x%08x\n",
	    RD4(slot, SDHCI_MAX_CURRENT), RD1(slot, SDHCI_ADMA_ERR));
	slot_printf(slot, "ADMA addr:0x%08x | Slot int: 0x%08x\n",
	    RD4(slot, SDHCI_ADMA_ADDRESS_LO), RD2(slot, SDHCI_SLOT_INT_STATUS));

	slot_printf(slot,
	    "===========================================\n");
}