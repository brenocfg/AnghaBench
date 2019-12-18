#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sfxHandle_t ;
struct TYPE_6__ {int left; int top; int /*<<< orphan*/  (* callback ) (TYPE_2__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; } ;
struct TYPE_7__ {int oldvalue; int curvalue; int /*<<< orphan*/  numitems; TYPE_1__ generic; } ;
typedef  TYPE_2__ menulist_s ;
struct TYPE_9__ {int /*<<< orphan*/  menu; TYPE_2__ list; } ;
struct TYPE_8__ {int /*<<< orphan*/  cursory; } ;

/* Variables and functions */
#define  K_DOWNARROW 132 
#define  K_KP_DOWNARROW 131 
#define  K_KP_UPARROW 130 
#define  K_MOUSE1 129 
#define  K_UPARROW 128 
 int /*<<< orphan*/  Menu_DefaultKey (int /*<<< orphan*/ *,int) ; 
 scalar_t__ Menu_ItemAtCursor (int /*<<< orphan*/ *) ; 
 int PROP_HEIGHT ; 
 int /*<<< orphan*/  QM_ACTIVATED ; 
 int /*<<< orphan*/  UI_CursorInRect (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_move_sound ; 
 int /*<<< orphan*/  menu_null_sound ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_4__ teamOrdersMenuInfo ; 
 TYPE_3__ uis ; 

sfxHandle_t UI_TeamOrdersMenu_Key( int key ) {
	menulist_s	*l;
	int	x;
	int	y;
	int	index;

	l = (menulist_s	*)Menu_ItemAtCursor( &teamOrdersMenuInfo.menu );
	if( l != &teamOrdersMenuInfo.list ) {
		return Menu_DefaultKey( &teamOrdersMenuInfo.menu, key );
	}

	switch( key ) {
		case K_MOUSE1:
			x = l->generic.left;
			y = l->generic.top;
			if( UI_CursorInRect( x, y, l->generic.right - x, l->generic.bottom - y ) ) {
				index = (uis.cursory - y) / PROP_HEIGHT;
				l->oldvalue = l->curvalue;
				l->curvalue = index;

				if( l->generic.callback ) {
					l->generic.callback( l, QM_ACTIVATED );
					return menu_move_sound;
				}
			}
			return menu_null_sound;

		case K_KP_UPARROW:
		case K_UPARROW:
			l->oldvalue = l->curvalue;

			if( l->curvalue == 0 ) {
				l->curvalue = l->numitems - 1;
			}
			else {
				l->curvalue--;
			}
			return menu_move_sound;

		case K_KP_DOWNARROW:
		case K_DOWNARROW:
			l->oldvalue = l->curvalue;

			if( l->curvalue == l->numitems - 1 ) {
				l->curvalue = 0;;
			}
			else {
				l->curvalue++;
			}
			return menu_move_sound;
	}

	return Menu_DefaultKey( &teamOrdersMenuInfo.menu, key );
}