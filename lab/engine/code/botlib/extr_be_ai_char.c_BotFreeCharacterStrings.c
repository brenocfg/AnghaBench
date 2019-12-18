#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* c; } ;
typedef  TYPE_3__ bot_character_t ;
struct TYPE_5__ {int /*<<< orphan*/  string; } ;
struct TYPE_6__ {scalar_t__ type; TYPE_1__ value; } ;

/* Variables and functions */
 scalar_t__ CT_STRING ; 
 int /*<<< orphan*/  FreeMemory (int /*<<< orphan*/ ) ; 
 int MAX_CHARACTERISTICS ; 

void BotFreeCharacterStrings(bot_character_t *ch)
{
	int i;

	for (i = 0; i < MAX_CHARACTERISTICS; i++)
	{
		if (ch->c[i].type == CT_STRING)
		{
			FreeMemory(ch->c[i].value.string);
		} //end if
	} //end for
}