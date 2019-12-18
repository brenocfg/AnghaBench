#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int handle; int /*<<< orphan*/  message; int /*<<< orphan*/  type; int /*<<< orphan*/  time; } ;
typedef  TYPE_1__ bot_consolemessage_t ;
struct TYPE_6__ {TYPE_1__* firstmessage; } ;
typedef  TYPE_2__ bot_chatstate_t ;

/* Variables and functions */
 TYPE_2__* BotChatStateFromHandle (int) ; 
 int /*<<< orphan*/  Q_strncpyz (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int BotNextConsoleMessage(int chatstate, bot_consolemessage_t *cm)
{
	bot_chatstate_t *cs;
	bot_consolemessage_t *firstmsg;

	cs = BotChatStateFromHandle(chatstate);
	if (!cs) return 0;
	if ((firstmsg = cs->firstmessage))
	{
		cm->handle = firstmsg->handle;
		cm->time = firstmsg->time;
		cm->type = firstmsg->type;
		Q_strncpyz(cm->message, firstmsg->message,
			   sizeof(cm->message));
		
		/* We omit setting the two pointers in cm because pointer
		 * size in the VM differs between the size in the engine on
		 * 64 bit machines, which would lead to a buffer overflow if
		 * this functions is called from the VM. The pointers are
		 * of no interest to functions calling
		 * BotNextConsoleMessage anyways.
		 */
		
		return cm->handle;
	} //end if
	return 0;
}