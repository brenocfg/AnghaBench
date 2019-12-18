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
struct TYPE_3__ {int gender; } ;
typedef  TYPE_1__ bot_chatstate_t ;

/* Variables and functions */
 TYPE_1__* BotChatStateFromHandle (int) ; 
#define  CHAT_GENDERFEMALE 129 
 int CHAT_GENDERLESS ; 
#define  CHAT_GENDERMALE 128 

void BotSetChatGender(int chatstate, int gender)
{
	bot_chatstate_t *cs;

	cs = BotChatStateFromHandle(chatstate);
	if (!cs) return;
	switch(gender)
	{
		case CHAT_GENDERFEMALE: cs->gender = CHAT_GENDERFEMALE; break;
		case CHAT_GENDERMALE: cs->gender = CHAT_GENDERMALE; break;
		default: cs->gender = CHAT_GENDERLESS; break;
	} //end switch
}