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
struct TYPE_2__ {scalar_t__ menusp; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEYCATCH_UI ; 
 int /*<<< orphan*/  UI_SPLevelMenu () ; 
 int /*<<< orphan*/  trap_Key_SetCatcher (int /*<<< orphan*/ ) ; 
 TYPE_1__ uis ; 

void UI_SPLevelMenu_f( void ) {
	trap_Key_SetCatcher( KEYCATCH_UI );
	uis.menusp = 0;
	UI_SPLevelMenu();
}