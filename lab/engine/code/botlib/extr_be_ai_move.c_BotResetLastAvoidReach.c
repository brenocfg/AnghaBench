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
struct TYPE_3__ {float* avoidreachtimes; scalar_t__* avoidreachtries; } ;
typedef  TYPE_1__ bot_movestate_t ;

/* Variables and functions */
 TYPE_1__* BotMoveStateFromHandle (int) ; 
 int MAX_AVOIDREACH ; 

void BotResetLastAvoidReach(int movestate)
{
	int i, latest;
	float latesttime;
	bot_movestate_t *ms;

	ms = BotMoveStateFromHandle(movestate);
	if (!ms) return;
	latesttime = 0;
	latest = 0;
	for (i = 0; i < MAX_AVOIDREACH; i++)
	{
		if (ms->avoidreachtimes[i] > latesttime)
		{
			latesttime = ms->avoidreachtimes[i];
			latest = i;
		} //end if
	} //end for
	if (latesttime)
	{
		ms->avoidreachtimes[latest] = 0;
		if (ms->avoidreachtries[latest] > 0) ms->avoidreachtries[latest]--;
	} //end if
}