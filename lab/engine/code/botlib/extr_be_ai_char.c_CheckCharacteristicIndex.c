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
struct TYPE_6__ {TYPE_1__* c; } ;
typedef  TYPE_2__ bot_character_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*,int) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 TYPE_2__* BotCharacterFromHandle (int) ; 
 int MAX_CHARACTERISTICS ; 
 int /*<<< orphan*/  PRT_ERROR ; 
 TYPE_3__ botimport ; 
 int qfalse ; 
 int qtrue ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*,int) ; 

int CheckCharacteristicIndex(int character, int index)
{
	bot_character_t *ch;

	ch = BotCharacterFromHandle(character);
	if (!ch) return qfalse;
	if (index < 0 || index >= MAX_CHARACTERISTICS)
	{
		botimport.Print(PRT_ERROR, "characteristic %d does not exist\n", index);
		return qfalse;
	} //end if
	if (!ch->c[index].type)
	{
		botimport.Print(PRT_ERROR, "characteristic %d is not initialized\n", index);
		return qfalse;
	} //end if
	return qtrue;
}