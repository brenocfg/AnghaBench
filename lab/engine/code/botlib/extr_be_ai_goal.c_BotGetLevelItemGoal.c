#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int number; int flags; size_t iteminfo; scalar_t__ timeout; int /*<<< orphan*/  entitynum; int /*<<< orphan*/  goalorigin; int /*<<< orphan*/  goalareanum; struct TYPE_8__* next; } ;
typedef  TYPE_2__ levelitem_t ;
struct TYPE_9__ {int number; size_t iteminfo; int /*<<< orphan*/  flags; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; int /*<<< orphan*/  entitynum; int /*<<< orphan*/  origin; int /*<<< orphan*/  areanum; } ;
typedef  TYPE_3__ bot_goal_t ;
struct TYPE_10__ {TYPE_1__* iteminfo; } ;
struct TYPE_7__ {int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFL_DROPPED ; 
 int /*<<< orphan*/  GFL_ITEM ; 
 scalar_t__ GT_SINGLE_PLAYER ; 
 scalar_t__ GT_TEAM ; 
 int IFL_NOTBOT ; 
 int IFL_NOTFREE ; 
 int IFL_NOTSINGLE ; 
 int IFL_NOTTEAM ; 
 int /*<<< orphan*/  Q_stricmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ g_gametype ; 
 TYPE_5__* itemconfig ; 
 TYPE_2__* levelitems ; 

int BotGetLevelItemGoal(int index, char *name, bot_goal_t *goal)
{
	levelitem_t *li;

	if (!itemconfig) return -1;
	li = levelitems;
	if (index >= 0)
	{
		for (; li; li = li->next)
		{
			if (li->number == index)
			{
				li = li->next;
				break;
			} //end if
		} //end for
	} //end for
	for (; li; li = li->next)
	{
		//
		if (g_gametype == GT_SINGLE_PLAYER) {
			if (li->flags & IFL_NOTSINGLE) continue;
		}
		else if (g_gametype >= GT_TEAM) {
			if (li->flags & IFL_NOTTEAM) continue;
		}
		else {
			if (li->flags & IFL_NOTFREE) continue;
		}
		if (li->flags & IFL_NOTBOT) continue;
		//
		if (!Q_stricmp(name, itemconfig->iteminfo[li->iteminfo].name))
		{
			goal->areanum = li->goalareanum;
			VectorCopy(li->goalorigin, goal->origin);
			goal->entitynum = li->entitynum;
			VectorCopy(itemconfig->iteminfo[li->iteminfo].mins, goal->mins);
			VectorCopy(itemconfig->iteminfo[li->iteminfo].maxs, goal->maxs);
			goal->number = li->number;
			goal->flags = GFL_ITEM;
			if (li->timeout) goal->flags |= GFL_DROPPED;
			goal->iteminfo = li->iteminfo;
			//botimport.Print(PRT_MESSAGE, "found li %s\n", itemconfig->iteminfo[li->iteminfo].name);
			return li->number;
		} //end if
	} //end for
	return -1;
}