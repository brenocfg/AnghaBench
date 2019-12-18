#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {int /*<<< orphan*/  cs; } ;
typedef  TYPE_1__ bot_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  BotSayTeamOrderAlways (TYPE_1__*,int) ; 
 int MAX_MESSAGE_SIZE ; 
 int /*<<< orphan*/  trap_BotGetChatMessage (int /*<<< orphan*/ ,char*,int) ; 

void BotSayTeamOrder(bot_state_t *bs, int toclient) {
#ifdef MISSIONPACK
	// voice chats only
	char buf[MAX_MESSAGE_SIZE];

	trap_BotGetChatMessage(bs->cs, buf, sizeof(buf));
#else
	BotSayTeamOrderAlways(bs, toclient);
#endif
}