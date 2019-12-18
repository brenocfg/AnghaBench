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
typedef  int /*<<< orphan*/  bot_goalstate_t ;
struct TYPE_3__ {int client; } ;

/* Variables and functions */
 TYPE_1__* GetClearedMemory (int) ; 
 int MAX_CLIENTS ; 
 TYPE_1__** botgoalstates ; 

int BotAllocGoalState(int client)
{
	int i;

	for (i = 1; i <= MAX_CLIENTS; i++)
	{
		if (!botgoalstates[i])
		{
			botgoalstates[i] = GetClearedMemory(sizeof(bot_goalstate_t));
			botgoalstates[i]->client = client;
			return i;
		} //end if
	} //end for
	return 0;
}