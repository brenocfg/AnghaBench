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
struct rsxx_cardinfo {unsigned int state; int size8; int /*<<< orphan*/  gendisk; scalar_t__ config_valid; } ;

/* Variables and functions */
#define  CARD_STATE_DSTROYING 136 
#define  CARD_STATE_FAULT 135 
#define  CARD_STATE_FORMATTING 134 
#define  CARD_STATE_GOOD 133 
#define  CARD_STATE_RD_ONLY_FAULT 132 
#define  CARD_STATE_SHUTDOWN 131 
#define  CARD_STATE_SHUTTING_DOWN 130 
#define  CARD_STATE_STARTING 129 
#define  CARD_STATE_UNINITIALIZED 128 
 int /*<<< orphan*/  CARD_TO_DEV (struct rsxx_cardinfo*) ; 
 int /*<<< orphan*/  dev_crit (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsxx_card_state_to_str (unsigned int) ; 
 int rsxx_get_card_size8 (struct rsxx_cardinfo*,int*) ; 
 int /*<<< orphan*/  set_capacity (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void card_state_change(struct rsxx_cardinfo *card,
			      unsigned int new_state)
{
	int st;

	dev_info(CARD_TO_DEV(card),
		"card state change detected.(%s -> %s)\n",
		rsxx_card_state_to_str(card->state),
		rsxx_card_state_to_str(new_state));

	card->state = new_state;

	/* Don't attach DMA interfaces if the card has an invalid config */
	if (!card->config_valid)
		return;

	switch (new_state) {
	case CARD_STATE_RD_ONLY_FAULT:
		dev_crit(CARD_TO_DEV(card),
			"Hardware has entered read-only mode!\n");
		/*
		 * Fall through so the DMA devices can be attached and
		 * the user can attempt to pull off their data.
		 */
		/* fall through */
	case CARD_STATE_GOOD:
		st = rsxx_get_card_size8(card, &card->size8);
		if (st)
			dev_err(CARD_TO_DEV(card),
				"Failed attaching DMA devices\n");

		if (card->config_valid)
			set_capacity(card->gendisk, card->size8 >> 9);
		break;

	case CARD_STATE_FAULT:
		dev_crit(CARD_TO_DEV(card),
			"Hardware Fault reported!\n");
		/* Fall through. */

	/* Everything else, detach DMA interface if it's attached. */
	case CARD_STATE_SHUTDOWN:
	case CARD_STATE_STARTING:
	case CARD_STATE_FORMATTING:
	case CARD_STATE_UNINITIALIZED:
	case CARD_STATE_SHUTTING_DOWN:
	/*
	 * dStroy is a term coined by marketing to represent the low level
	 * secure erase.
	 */
	case CARD_STATE_DSTROYING:
		set_capacity(card->gendisk, 0);
		break;
	}
}