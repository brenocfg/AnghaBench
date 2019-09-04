#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t id; } ;
typedef  TYPE_2__ menucommon_s ;
struct TYPE_6__ {size_t selectedBotNum; TYPE_1__* bots; } ;
struct TYPE_4__ {int /*<<< orphan*/  color; } ;

/* Variables and functions */
 size_t ID_BOTNAME0 ; 
 int QM_ACTIVATED ; 
 int /*<<< orphan*/  color_blue ; 
 int /*<<< orphan*/  color_white ; 
 TYPE_3__ removeBotsMenuInfo ; 

__attribute__((used)) static void UI_RemoveBotsMenu_BotEvent( void* ptr, int event ) {
	if (event != QM_ACTIVATED) {
		return;
	}

	removeBotsMenuInfo.bots[removeBotsMenuInfo.selectedBotNum].color = color_blue;
	removeBotsMenuInfo.selectedBotNum = ((menucommon_s*)ptr)->id - ID_BOTNAME0;
	removeBotsMenuInfo.bots[removeBotsMenuInfo.selectedBotNum].color = color_white;
}