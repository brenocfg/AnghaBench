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
struct TYPE_2__ {int /*<<< orphan*/  demoversion; } ;

/* Variables and functions */
 int /*<<< orphan*/  UI_InitMemory () ; 
 int /*<<< orphan*/  UI_LoadArenas () ; 
 int /*<<< orphan*/  UI_LoadBots () ; 
 int /*<<< orphan*/  qfalse ; 
 TYPE_1__ uis ; 

void UI_InitGameinfo( void ) {

	UI_InitMemory();
	UI_LoadArenas();
	UI_LoadBots();

	uis.demoversion = qfalse;
}