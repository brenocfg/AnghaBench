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
struct TYPE_3__ {int /*<<< orphan*/  actionflags; } ;
typedef  TYPE_1__ bot_input_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_RESPAWN ; 
 TYPE_1__* botinputs ; 

void EA_Respawn(int client)
{
	bot_input_t *bi;

	bi = &botinputs[client];

	bi->actionflags |= ACTION_RESPAWN;
}