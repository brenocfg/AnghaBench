#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ order_time; } ;
typedef  TYPE_1__ bot_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  Bot1FCTFRetreatGoals (TYPE_1__*) ; 
 int /*<<< orphan*/  Bot1FCTFSeekGoals (TYPE_1__*) ; 
 int /*<<< orphan*/  BotCTFRetreatGoals (TYPE_1__*) ; 
 int /*<<< orphan*/  BotCTFSeekGoals (TYPE_1__*) ; 
 int /*<<< orphan*/  BotHarvesterRetreatGoals (TYPE_1__*) ; 
 int /*<<< orphan*/  BotHarvesterSeekGoals (TYPE_1__*) ; 
 int /*<<< orphan*/  BotObeliskRetreatGoals (TYPE_1__*) ; 
 int /*<<< orphan*/  BotObeliskSeekGoals (TYPE_1__*) ; 
 scalar_t__ GT_1FCTF ; 
 scalar_t__ GT_CTF ; 
 scalar_t__ GT_HARVESTER ; 
 scalar_t__ GT_OBELISK ; 
 scalar_t__ gametype ; 

void BotTeamGoals(bot_state_t *bs, int retreat) {

	if ( retreat ) {
		if (gametype == GT_CTF) {
			BotCTFRetreatGoals(bs);
		}
#ifdef MISSIONPACK
		else if (gametype == GT_1FCTF) {
			Bot1FCTFRetreatGoals(bs);
		}
		else if (gametype == GT_OBELISK) {
			BotObeliskRetreatGoals(bs);
		}
		else if (gametype == GT_HARVESTER) {
			BotHarvesterRetreatGoals(bs);
		}
#endif
	}
	else {
		if (gametype == GT_CTF) {
			//decide what to do in CTF mode
			BotCTFSeekGoals(bs);
		}
#ifdef MISSIONPACK
		else if (gametype == GT_1FCTF) {
			Bot1FCTFSeekGoals(bs);
		}
		else if (gametype == GT_OBELISK) {
			BotObeliskSeekGoals(bs);
		}
		else if (gametype == GT_HARVESTER) {
			BotHarvesterSeekGoals(bs);
		}
#endif
	}
	// reset the order time which is used to see if
	// we decided to refuse an order
	bs->order_time = 0;
}