#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int cursorItem; int /*<<< orphan*/  window; int /*<<< orphan*/  fadeCycle; int /*<<< orphan*/  fadeClamp; int /*<<< orphan*/  fadeAmount; } ;
typedef  TYPE_2__ menuDef_t ;
struct TYPE_6__ {int /*<<< orphan*/  fadeCycle; int /*<<< orphan*/  fadeClamp; int /*<<< orphan*/  fadeAmount; } ;
struct TYPE_8__ {TYPE_1__ Assets; } ;

/* Variables and functions */
 TYPE_5__* DC ; 
 int /*<<< orphan*/  Window_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

void Menu_Init(menuDef_t *menu) {
	memset(menu, 0, sizeof(menuDef_t));
	menu->cursorItem = -1;
	menu->fadeAmount = DC->Assets.fadeAmount;
	menu->fadeClamp = DC->Assets.fadeClamp;
	menu->fadeCycle = DC->Assets.fadeCycle;
	Window_Init(&menu->window);
}