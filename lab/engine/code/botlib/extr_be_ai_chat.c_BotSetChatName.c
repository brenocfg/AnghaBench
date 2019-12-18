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
struct TYPE_3__ {int client; char* name; } ;
typedef  TYPE_1__ bot_chatstate_t ;

/* Variables and functions */
 TYPE_1__* BotChatStateFromHandle (int) ; 
 int /*<<< orphan*/  Com_Memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

void BotSetChatName(int chatstate, char *name, int client)
{
	bot_chatstate_t *cs;

	cs = BotChatStateFromHandle(chatstate);
	if (!cs) return;
	cs->client = client;
	Com_Memset(cs->name, 0, sizeof(cs->name));
	strncpy(cs->name, name, sizeof(cs->name)-1);
	cs->name[sizeof(cs->name)-1] = '\0';
}