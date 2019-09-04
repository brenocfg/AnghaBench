#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  BOTAI_START_FRAME ; 
 int /*<<< orphan*/  VM_Call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bot_enable ; 
 int /*<<< orphan*/  gvm ; 

void SV_BotFrame( int time ) {
	if (!bot_enable) return;
	//NOTE: maybe the game is already shutdown
	if (!gvm) return;
	VM_Call( gvm, BOTAI_START_FRAME, time );
}