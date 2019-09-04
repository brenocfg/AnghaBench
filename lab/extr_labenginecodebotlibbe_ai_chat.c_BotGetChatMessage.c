#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  chatmessage; } ;
typedef  TYPE_1__ bot_chatstate_t ;

/* Variables and functions */
 TYPE_1__* BotChatStateFromHandle (int) ; 
 int /*<<< orphan*/  BotRemoveTildes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 

void BotGetChatMessage(int chatstate, char *buf, int size)
{
	bot_chatstate_t *cs;

	cs = BotChatStateFromHandle(chatstate);
	if (!cs) return;

	BotRemoveTildes(cs->chatmessage);
	strncpy(buf, cs->chatmessage, size-1);
	buf[size-1] = '\0';
	//clear the chat message from the state
	strcpy(cs->chatmessage, "");
}