#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int handle; struct TYPE_7__* next; TYPE_1__* prev; } ;
typedef  TYPE_2__ bot_consolemessage_t ;
struct TYPE_8__ {int /*<<< orphan*/  numconsolemessages; TYPE_2__* firstmessage; TYPE_1__* lastmessage; } ;
typedef  TYPE_3__ bot_chatstate_t ;
struct TYPE_6__ {TYPE_2__* next; } ;

/* Variables and functions */
 TYPE_3__* BotChatStateFromHandle (int) ; 
 int /*<<< orphan*/  FreeConsoleMessage (TYPE_2__*) ; 

void BotRemoveConsoleMessage(int chatstate, int handle)
{
	bot_consolemessage_t *m, *nextm;
	bot_chatstate_t *cs;

	cs = BotChatStateFromHandle(chatstate);
	if (!cs) return;

	for (m = cs->firstmessage; m; m = nextm)
	{
		nextm = m->next;
		if (m->handle == handle)
		{
			if (m->next) m->next->prev = m->prev;
			else cs->lastmessage = m->prev;
			if (m->prev) m->prev->next = m->next;
			else cs->firstmessage = m->next;

			FreeConsoleMessage(m);
			cs->numconsolemessages--;
			break;
		} //end if
	} //end for
}