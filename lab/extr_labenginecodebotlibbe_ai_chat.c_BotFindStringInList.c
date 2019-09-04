#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  string; struct TYPE_4__* next; } ;
typedef  TYPE_1__ bot_stringlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

bot_stringlist_t *BotFindStringInList(bot_stringlist_t *list, char *string)
{
	bot_stringlist_t *s;

	for (s = list; s; s = s->next)
	{
		if (!strcmp(s->string, string)) return s;
	} //end for
	return NULL;
}