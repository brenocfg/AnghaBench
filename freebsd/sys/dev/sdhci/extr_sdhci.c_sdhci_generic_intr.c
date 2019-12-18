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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct sdhci_slot {int intmask; int /*<<< orphan*/  retune_req; TYPE_1__* curcmd; } ;
struct TYPE_2__ {int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMC_ERR_BADCRC ; 
 int /*<<< orphan*/  RD2 (struct sdhci_slot*,int /*<<< orphan*/ ) ; 
 int RD4 (struct sdhci_slot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDHCI_ACMD12_ERR ; 
 int SDHCI_INT_ACMD12ERR ; 
 int SDHCI_INT_BUS_POWER ; 
 int SDHCI_INT_CARD_INSERT ; 
 int SDHCI_INT_CARD_REMOVE ; 
 int SDHCI_INT_CMD_ERROR_MASK ; 
 int SDHCI_INT_CMD_MASK ; 
 int SDHCI_INT_DATA_MASK ; 
 int /*<<< orphan*/  SDHCI_INT_ENABLE ; 
 int SDHCI_INT_ERROR ; 
 int SDHCI_INT_RETUNE ; 
 int /*<<< orphan*/  SDHCI_INT_STATUS ; 
 int SDHCI_INT_TUNEERR ; 
 int /*<<< orphan*/  SDHCI_LOCK (struct sdhci_slot*) ; 
 int /*<<< orphan*/  SDHCI_RETUNE_REQ_NEEDED ; 
 int /*<<< orphan*/  SDHCI_RETUNE_REQ_RESET ; 
 int /*<<< orphan*/  SDHCI_SIGNAL_ENABLE ; 
 int /*<<< orphan*/  SDHCI_UNLOCK (struct sdhci_slot*) ; 
 int /*<<< orphan*/  WR4 (struct sdhci_slot*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  sdhci_acmd_irq (struct sdhci_slot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_cmd_irq (struct sdhci_slot*,int) ; 
 int /*<<< orphan*/  sdhci_data_irq (struct sdhci_slot*,int) ; 
 int sdhci_debug ; 
 int /*<<< orphan*/  sdhci_dumpregs (struct sdhci_slot*) ; 
 int /*<<< orphan*/  sdhci_finish_command (struct sdhci_slot*) ; 
 int /*<<< orphan*/  sdhci_handle_card_present_locked (struct sdhci_slot*,int) ; 
 int /*<<< orphan*/  slot_printf (struct sdhci_slot*,char*,...) ; 

void
sdhci_generic_intr(struct sdhci_slot *slot)
{
	uint32_t intmask, present;
	uint16_t val16;

	SDHCI_LOCK(slot);
	/* Read slot interrupt status. */
	intmask = RD4(slot, SDHCI_INT_STATUS);
	if (intmask == 0 || intmask == 0xffffffff) {
		SDHCI_UNLOCK(slot);
		return;
	}
	if (__predict_false(sdhci_debug > 2))
		slot_printf(slot, "Interrupt %#x\n", intmask);

	/* Handle tuning error interrupt. */
	if (__predict_false(intmask & SDHCI_INT_TUNEERR)) {
		WR4(slot, SDHCI_INT_STATUS, SDHCI_INT_TUNEERR);
		slot_printf(slot, "Tuning error indicated\n");
		slot->retune_req |= SDHCI_RETUNE_REQ_RESET;
		if (slot->curcmd) {
			slot->curcmd->error = MMC_ERR_BADCRC;
			sdhci_finish_command(slot);
		}
	}
	/* Handle re-tuning interrupt. */
	if (__predict_false(intmask & SDHCI_INT_RETUNE))
		slot->retune_req |= SDHCI_RETUNE_REQ_NEEDED;
	/* Handle card presence interrupts. */
	if (intmask & (SDHCI_INT_CARD_INSERT | SDHCI_INT_CARD_REMOVE)) {
		present = (intmask & SDHCI_INT_CARD_INSERT) != 0;
		slot->intmask &=
		    ~(SDHCI_INT_CARD_INSERT | SDHCI_INT_CARD_REMOVE);
		slot->intmask |= present ? SDHCI_INT_CARD_REMOVE :
		    SDHCI_INT_CARD_INSERT;
		WR4(slot, SDHCI_INT_ENABLE, slot->intmask);
		WR4(slot, SDHCI_SIGNAL_ENABLE, slot->intmask);
		WR4(slot, SDHCI_INT_STATUS, intmask &
		    (SDHCI_INT_CARD_INSERT | SDHCI_INT_CARD_REMOVE));
		sdhci_handle_card_present_locked(slot, present);
	}
	/* Handle command interrupts. */
	if (intmask & SDHCI_INT_CMD_MASK) {
		WR4(slot, SDHCI_INT_STATUS, intmask & SDHCI_INT_CMD_MASK);
		sdhci_cmd_irq(slot, intmask & SDHCI_INT_CMD_MASK);
	}
	/* Handle data interrupts. */
	if (intmask & SDHCI_INT_DATA_MASK) {
		WR4(slot, SDHCI_INT_STATUS, intmask & SDHCI_INT_DATA_MASK);
		/* Don't call data_irq in case of errored command. */
		if ((intmask & SDHCI_INT_CMD_ERROR_MASK) == 0)
			sdhci_data_irq(slot, intmask & SDHCI_INT_DATA_MASK);
	}
	/* Handle AutoCMD12 error interrupt. */
	if (intmask & SDHCI_INT_ACMD12ERR) {
		/* Clearing SDHCI_INT_ACMD12ERR may clear SDHCI_ACMD12_ERR. */
		val16 = RD2(slot, SDHCI_ACMD12_ERR);
		WR4(slot, SDHCI_INT_STATUS, SDHCI_INT_ACMD12ERR);
		sdhci_acmd_irq(slot, val16);
	}
	/* Handle bus power interrupt. */
	if (intmask & SDHCI_INT_BUS_POWER) {
		WR4(slot, SDHCI_INT_STATUS, SDHCI_INT_BUS_POWER);
		slot_printf(slot, "Card is consuming too much power!\n");
	}
	intmask &= ~(SDHCI_INT_ERROR | SDHCI_INT_TUNEERR | SDHCI_INT_RETUNE |
	    SDHCI_INT_CARD_INSERT | SDHCI_INT_CARD_REMOVE | SDHCI_INT_CMD_MASK |
	    SDHCI_INT_DATA_MASK | SDHCI_INT_ACMD12ERR | SDHCI_INT_BUS_POWER);
	/* The rest is unknown. */
	if (intmask) {
		WR4(slot, SDHCI_INT_STATUS, intmask);
		slot_printf(slot, "Unexpected interrupt 0x%08x.\n",
		    intmask);
		sdhci_dumpregs(slot);
	}

	SDHCI_UNLOCK(slot);
}