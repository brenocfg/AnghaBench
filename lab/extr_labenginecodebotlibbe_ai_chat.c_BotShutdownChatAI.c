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
struct TYPE_6__ {struct TYPE_6__* chat; } ;

/* Variables and functions */
 int /*<<< orphan*/  BotFreeChatState (int) ; 
 int /*<<< orphan*/  BotFreeMatchTemplates (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BotFreeReplyChat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeMemory (TYPE_1__*) ; 
 int MAX_CLIENTS ; 
 scalar_t__* botchatstates ; 
 TYPE_1__* consolemessageheap ; 
 TYPE_1__** ichatdata ; 
 int /*<<< orphan*/ * matchtemplates ; 
 TYPE_1__* randomstrings ; 
 int /*<<< orphan*/ * replychats ; 
 TYPE_1__* synonyms ; 

void BotShutdownChatAI(void)
{
	int i;

	//free all remaining chat states
	for(i = 0; i < MAX_CLIENTS; i++)
	{
		if (botchatstates[i])
		{
			BotFreeChatState(i);
		} //end if
	} //end for
	//free all cached chats
	for(i = 0; i < MAX_CLIENTS; i++)
	{
		if (ichatdata[i])
		{
			FreeMemory(ichatdata[i]->chat);
			FreeMemory(ichatdata[i]);
			ichatdata[i] = NULL;
		} //end if
	} //end for
	if (consolemessageheap) FreeMemory(consolemessageheap);
	consolemessageheap = NULL;
	if (matchtemplates) BotFreeMatchTemplates(matchtemplates);
	matchtemplates = NULL;
	if (randomstrings) FreeMemory(randomstrings);
	randomstrings = NULL;
	if (synonyms) FreeMemory(synonyms);
	synonyms = NULL;
	if (replychats) BotFreeReplyChat(replychats);
	replychats = NULL;
}