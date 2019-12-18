#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  chatmessage; int /*<<< orphan*/  client; } ;
typedef  TYPE_1__ bot_chatstate_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__* BotChatStateFromHandle (int) ; 
 int /*<<< orphan*/  BotRemoveTildes (int /*<<< orphan*/ ) ; 
#define  CHAT_TEAM 129 
#define  CHAT_TELL 128 
 int /*<<< orphan*/  EA_Command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ LibVarGetValue (char*) ; 
 int /*<<< orphan*/  PRT_MESSAGE ; 
 TYPE_2__ botimport ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va (char*,int,...) ; 

void BotEnterChat(int chatstate, int clientto, int sendto)
{
	bot_chatstate_t *cs;

	cs = BotChatStateFromHandle(chatstate);
	if (!cs) return;

	if (strlen(cs->chatmessage))
	{
		BotRemoveTildes(cs->chatmessage);
		if (LibVarGetValue("bot_testichat")) {
			botimport.Print(PRT_MESSAGE, "%s\n", cs->chatmessage);
		}
		else {
			switch(sendto) {
				case CHAT_TEAM:
					EA_Command(cs->client, va("say_team %s", cs->chatmessage));
					break;
				case CHAT_TELL:
					EA_Command(cs->client, va("tell %d %s", clientto, cs->chatmessage));
					break;
				default: //CHAT_ALL
					EA_Command(cs->client, va("say %s", cs->chatmessage));
					break;
			}
		}
		//clear the chat message from the state
		strcpy(cs->chatmessage, "");
	} //end if
}