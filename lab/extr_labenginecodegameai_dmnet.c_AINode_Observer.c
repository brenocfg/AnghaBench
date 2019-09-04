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
typedef  int /*<<< orphan*/  bot_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  AIEnter_Stand (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  BotIsObserver (int /*<<< orphan*/ *) ; 
 int qtrue ; 

int AINode_Observer(bot_state_t *bs) {
	//if the bot left observer mode
	if (!BotIsObserver(bs)) {
		AIEnter_Stand(bs, "observer: left observer");
	}
	return qtrue;
}