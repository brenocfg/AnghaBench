#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bot_character_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*,int,float,float) ;} ;

/* Variables and functions */
 int /*<<< orphan*/ * BotCharacterFromHandle (int) ; 
 float Characteristic_Float (int,int) ; 
 int /*<<< orphan*/  PRT_ERROR ; 
 TYPE_1__ botimport ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int,float,float) ; 

float Characteristic_BFloat(int character, int index, float min, float max)
{
	float value;
	bot_character_t *ch;

	ch = BotCharacterFromHandle(character);
	if (!ch) return 0;
	if (min > max)
	{
		botimport.Print(PRT_ERROR, "cannot bound characteristic %d between %f and %f\n", index, min, max);
		return 0;
	} //end if
	value = Characteristic_Float(character, index);
	if (value < min) return min;
	if (value > max) return max;
	return value;
}