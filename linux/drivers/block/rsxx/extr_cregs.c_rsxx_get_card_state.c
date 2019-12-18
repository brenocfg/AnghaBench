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
struct rsxx_cardinfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CREG_ADD_CARD_STATE ; 
 int rsxx_creg_read (struct rsxx_cardinfo*,int /*<<< orphan*/ ,int,unsigned int*,int /*<<< orphan*/ ) ; 

int rsxx_get_card_state(struct rsxx_cardinfo *card, unsigned int *state)
{
	return rsxx_creg_read(card, CREG_ADD_CARD_STATE,
				  sizeof(*state), state, 0);
}