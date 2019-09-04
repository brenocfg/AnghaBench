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
typedef  int /*<<< orphan*/  sfxHandle_t ;
struct TYPE_2__ {int /*<<< orphan*/  menu; int /*<<< orphan*/  list; scalar_t__ refreshservers; } ;

/* Variables and functions */
 int /*<<< orphan*/  ArenaServers_Remove () ; 
 int /*<<< orphan*/  ArenaServers_SaveChanges () ; 
 int /*<<< orphan*/  ArenaServers_StopRefresh () ; 
 int /*<<< orphan*/  ArenaServers_UpdateMenu () ; 
 int K_DEL ; 
 int K_ESCAPE ; 
 int K_KP_DEL ; 
 int K_MOUSE2 ; 
 int K_SPACE ; 
 int /*<<< orphan*/  Menu_DefaultKey (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * Menu_ItemAtCursor (int /*<<< orphan*/ *) ; 
 scalar_t__ UIAS_FAVORITES ; 
 TYPE_1__ g_arenaservers ; 
 scalar_t__ g_servertype ; 
 int /*<<< orphan*/  menu_move_sound ; 

__attribute__((used)) static sfxHandle_t ArenaServers_MenuKey( int key ) {
	if( key == K_SPACE  && g_arenaservers.refreshservers ) {
		ArenaServers_StopRefresh();	
		return menu_move_sound;
	}

	if( ( key == K_DEL || key == K_KP_DEL ) && ( g_servertype == UIAS_FAVORITES ) &&
		( Menu_ItemAtCursor( &g_arenaservers.menu) == &g_arenaservers.list ) ) {
		ArenaServers_Remove();
		ArenaServers_UpdateMenu();
		return menu_move_sound;
	}

	if( key == K_MOUSE2 || key == K_ESCAPE ) {
		ArenaServers_StopRefresh();
		ArenaServers_SaveChanges();
	}


	return Menu_DefaultKey( &g_arenaservers.menu, key );
}