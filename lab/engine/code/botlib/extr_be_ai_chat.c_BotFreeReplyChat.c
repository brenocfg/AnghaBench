#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* next; struct TYPE_6__* firstchatmessage; struct TYPE_6__* string; scalar_t__ match; struct TYPE_6__* keys; } ;
typedef  TYPE_1__ bot_replychatkey_t ;
typedef  TYPE_1__ bot_replychat_t ;
typedef  TYPE_1__ bot_chatmessage_t ;

/* Variables and functions */
 int /*<<< orphan*/  BotFreeMatchPieces (scalar_t__) ; 
 int /*<<< orphan*/  FreeMemory (TYPE_1__*) ; 

void BotFreeReplyChat(bot_replychat_t *replychat)
{
	bot_replychat_t *rp, *nextrp;
	bot_replychatkey_t *key, *nextkey;
	bot_chatmessage_t *cm, *nextcm;

	for (rp = replychat; rp; rp = nextrp)
	{
		nextrp = rp->next;
		for (key = rp->keys; key; key = nextkey)
		{
			nextkey = key->next;
			if (key->match) BotFreeMatchPieces(key->match);
			if (key->string) FreeMemory(key->string);
			FreeMemory(key);
		} //end for
		for (cm = rp->firstchatmessage; cm; cm = nextcm)
		{
			nextcm = cm->next;
			FreeMemory(cm);
		} //end for
		FreeMemory(rp);
	} //end for
}