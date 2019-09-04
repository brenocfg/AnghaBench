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
typedef  int /*<<< orphan*/  bot_input_t ;
struct TYPE_2__ {int maxclients; } ;

/* Variables and functions */
 int BLERR_NOERROR ; 
 scalar_t__ GetClearedHunkMemory (int) ; 
 int /*<<< orphan*/ * botinputs ; 
 TYPE_1__ botlibglobals ; 

int EA_Setup(void)
{
	//initialize the bot inputs
	botinputs = (bot_input_t *) GetClearedHunkMemory(
									botlibglobals.maxclients * sizeof(bot_input_t));
	return BLERR_NOERROR;
}