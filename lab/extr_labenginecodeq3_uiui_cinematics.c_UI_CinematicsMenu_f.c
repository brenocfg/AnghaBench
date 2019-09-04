#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * items; } ;
struct TYPE_3__ {TYPE_2__ menu; } ;

/* Variables and functions */
 int /*<<< orphan*/  Menu_SetCursorToItem (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_Argv (int) ; 
 int /*<<< orphan*/  UI_CinematicsMenu () ; 
 int atoi (int /*<<< orphan*/ ) ; 
 TYPE_1__ cinematicsMenuInfo ; 

void UI_CinematicsMenu_f( void ) {
	int		n;

	n = atoi( UI_Argv( 1 ) );
	UI_CinematicsMenu();
	Menu_SetCursorToItem( &cinematicsMenuInfo.menu, cinematicsMenuInfo.menu.items[n + 3] );
}