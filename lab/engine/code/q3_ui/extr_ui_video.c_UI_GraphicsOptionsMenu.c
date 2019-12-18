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
struct TYPE_2__ {int /*<<< orphan*/  graphics; int /*<<< orphan*/  menu; } ;

/* Variables and functions */
 int /*<<< orphan*/  GraphicsOptions_MenuInit () ; 
 int /*<<< orphan*/  Menu_SetCursorToItem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UI_PushMenu (int /*<<< orphan*/ *) ; 
 TYPE_1__ s_graphicsoptions ; 

void UI_GraphicsOptionsMenu( void ) {
	GraphicsOptions_MenuInit();
	UI_PushMenu( &s_graphicsoptions.menu );
	Menu_SetCursorToItem( &s_graphicsoptions.menu, &s_graphicsoptions.graphics );
}