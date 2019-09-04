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
struct TYPE_2__ {int /*<<< orphan*/  menu; } ;

/* Variables and functions */
 int /*<<< orphan*/  UI_PushMenu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UI_SetupMenu_Init () ; 
 TYPE_1__ setupMenuInfo ; 

void UI_SetupMenu( void ) {
	UI_SetupMenu_Init();
	UI_PushMenu( &setupMenuInfo.menu );
}