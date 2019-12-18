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
struct TYPE_4__ {int /*<<< orphan*/  ainode; scalar_t__ standfindenemy_time; } ;
typedef  TYPE_1__ bot_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  AINode_Stand ; 
 int /*<<< orphan*/  BotRecordNodeSwitch (TYPE_1__*,char*,char*,char*) ; 
 scalar_t__ FloatTime () ; 

void AIEnter_Stand(bot_state_t *bs, char *s) {
	BotRecordNodeSwitch(bs, "stand", "", s);
	bs->standfindenemy_time = FloatTime() + 1;
	bs->ainode = AINode_Stand;
}