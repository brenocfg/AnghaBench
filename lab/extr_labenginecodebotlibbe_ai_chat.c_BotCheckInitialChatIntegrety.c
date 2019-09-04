#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct TYPE_9__* next; } ;
typedef  TYPE_1__ bot_stringlist_t ;
struct TYPE_10__ {TYPE_3__* firstchatmessage; struct TYPE_10__* next; } ;
typedef  TYPE_2__ bot_chattype_t ;
struct TYPE_11__ {int /*<<< orphan*/  chatmessage; struct TYPE_11__* next; } ;
typedef  TYPE_3__ bot_chatmessage_t ;
struct TYPE_12__ {TYPE_2__* types; } ;
typedef  TYPE_4__ bot_chat_t ;

/* Variables and functions */
 TYPE_1__* BotCheckChatMessageIntegrety (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  FreeMemory (TYPE_1__*) ; 

void BotCheckInitialChatIntegrety(bot_chat_t *chat)
{
	bot_chattype_t *t;
	bot_chatmessage_t *cm;
	bot_stringlist_t *stringlist, *s, *nexts;

	stringlist = NULL;
	for (t = chat->types; t; t = t->next)
	{
		for (cm = t->firstchatmessage; cm; cm = cm->next)
		{
			stringlist = BotCheckChatMessageIntegrety(cm->chatmessage, stringlist);
		} //end for
	} //end for
	for (s = stringlist; s; s = nexts)
	{
		nexts = s->next;
		FreeMemory(s);
	} //end for
}