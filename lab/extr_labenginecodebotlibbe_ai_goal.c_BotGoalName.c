#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int number; size_t iteminfo; struct TYPE_6__* next; } ;
typedef  TYPE_2__ levelitem_t ;
struct TYPE_7__ {TYPE_1__* iteminfo; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  Q_strncpyz (char*,int /*<<< orphan*/ ,int) ; 
 TYPE_4__* itemconfig ; 
 TYPE_2__* levelitems ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

void BotGoalName(int number, char *name, int size)
{
	levelitem_t *li;

	if (!itemconfig) return;
	//
	for (li = levelitems; li; li = li->next)
	{
		if (li->number == number)
		{
			Q_strncpyz(name, itemconfig->iteminfo[li->iteminfo].name, size);
			return;
		} //end for
	} //end for
	strcpy(name, "");
}