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
typedef  int /*<<< orphan*/  bot_state_t ;

/* Variables and functions */

void BotVoiceChat(bot_state_t *bs, int toclient, char *voicechat) {
#ifdef MISSIONPACK
	if (toclient == -1)
		// voice only say team
		trap_EA_Command(bs->client, va("vsay_team %s", voicechat));
	else
		// voice only tell single player
		trap_EA_Command(bs->client, va("vtell %d %s", toclient, voicechat));
#endif
}