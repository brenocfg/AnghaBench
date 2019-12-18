#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ sfxHandle_t ;
typedef  int /*<<< orphan*/  menuslider_s ;
typedef  int /*<<< orphan*/  menuradiobutton_s ;
typedef  int /*<<< orphan*/  menulist_s ;
struct TYPE_11__ {int cursor; int cursor_prev; int /*<<< orphan*/  nitems; } ;
typedef  TYPE_1__ menuframework_s ;
typedef  int /*<<< orphan*/  menufield_s ;
struct TYPE_12__ {int flags; int type; } ;
typedef  TYPE_2__ menucommon_s ;
struct TYPE_13__ {int debug; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXEC_APPEND ; 
#define  K_AUX1 165 
#define  K_AUX10 164 
#define  K_AUX11 163 
#define  K_AUX12 162 
#define  K_AUX13 161 
#define  K_AUX14 160 
#define  K_AUX15 159 
#define  K_AUX16 158 
#define  K_AUX2 157 
#define  K_AUX3 156 
#define  K_AUX4 155 
#define  K_AUX5 154 
#define  K_AUX6 153 
#define  K_AUX7 152 
#define  K_AUX8 151 
#define  K_AUX9 150 
#define  K_DOWNARROW 149 
#define  K_ENTER 148 
#define  K_ESCAPE 147 
#define  K_F11 146 
#define  K_F12 145 
#define  K_JOY1 144 
#define  K_JOY2 143 
#define  K_JOY3 142 
#define  K_JOY4 141 
#define  K_KP_DOWNARROW 140 
#define  K_KP_ENTER 139 
#define  K_KP_UPARROW 138 
#define  K_MOUSE1 137 
#define  K_MOUSE2 136 
#define  K_MOUSE3 135 
#define  K_TAB 134 
#define  K_UPARROW 133 
#define  MTYPE_FIELD 132 
#define  MTYPE_RADIOBUTTON 131 
#define  MTYPE_SCROLLLIST 130 
#define  MTYPE_SLIDER 129 
#define  MTYPE_SPINCONTROL 128 
 scalar_t__ MenuField_Key (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ Menu_ActivateItem (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  Menu_AdjustCursor (TYPE_1__*,int) ; 
 int /*<<< orphan*/  Menu_CursorMoved (TYPE_1__*) ; 
 TYPE_2__* Menu_ItemAtCursor (TYPE_1__*) ; 
 int QMF_GRAYED ; 
 int QMF_HASMOUSEFOCUS ; 
 int QMF_INACTIVE ; 
 int QMF_MOUSEONLY ; 
 scalar_t__ RadioButton_Key (int /*<<< orphan*/ *,int) ; 
 scalar_t__ ScrollList_Key (int /*<<< orphan*/ *,int) ; 
 scalar_t__ Slider_Key (int /*<<< orphan*/ *,int) ; 
 scalar_t__ SpinControl_Key (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  UI_PopMenu () ; 
 scalar_t__ menu_move_sound ; 
 scalar_t__ menu_out_sound ; 
 int /*<<< orphan*/  trap_Cmd_ExecuteText (int /*<<< orphan*/ ,char*) ; 
 TYPE_3__ uis ; 

sfxHandle_t Menu_DefaultKey( menuframework_s *m, int key )
{
	sfxHandle_t		sound = 0;
	menucommon_s	*item;
	int				cursor_prev;

	// menu system keys
	switch ( key )
	{
		case K_MOUSE2:
		case K_ESCAPE:
			UI_PopMenu();
			return menu_out_sound;
	}

	if (!m || !m->nitems)
		return 0;

	// route key stimulus to widget
	item = Menu_ItemAtCursor( m );
	if (item && !(item->flags & (QMF_GRAYED|QMF_INACTIVE)))
	{
		switch (item->type)
		{
			case MTYPE_SPINCONTROL:
				sound = SpinControl_Key( (menulist_s*)item, key );
				break;

			case MTYPE_RADIOBUTTON:
				sound = RadioButton_Key( (menuradiobutton_s*)item, key );
				break;

			case MTYPE_SLIDER:
				sound = Slider_Key( (menuslider_s*)item, key );
				break;

			case MTYPE_SCROLLLIST:
				sound = ScrollList_Key( (menulist_s*)item, key );
				break;

			case MTYPE_FIELD:
				sound = MenuField_Key( (menufield_s*)item, &key );
				break;
		}

		if (sound) {
			// key was handled
			return sound;		
		}
	}

	// default handling
	switch ( key )
	{
#ifndef NDEBUG
		case K_F11:
			uis.debug ^= 1;
			break;

		case K_F12:
			trap_Cmd_ExecuteText(EXEC_APPEND, "screenshot\n");
			break;
#endif
		case K_KP_UPARROW:
		case K_UPARROW:
			cursor_prev    = m->cursor;
			m->cursor_prev = m->cursor;
			m->cursor--;
			Menu_AdjustCursor( m, -1 );
			if ( cursor_prev != m->cursor ) {
				Menu_CursorMoved( m );
				sound = menu_move_sound;
			}
			break;

		case K_TAB:
		case K_KP_DOWNARROW:
		case K_DOWNARROW:
			cursor_prev    = m->cursor;
			m->cursor_prev = m->cursor;
			m->cursor++;
			Menu_AdjustCursor( m, 1 );
			if ( cursor_prev != m->cursor ) {
				Menu_CursorMoved( m );
				sound = menu_move_sound;
			}
			break;

		case K_MOUSE1:
		case K_MOUSE3:
			if (item)
				if ((item->flags & QMF_HASMOUSEFOCUS) && !(item->flags & (QMF_GRAYED|QMF_INACTIVE)))
					return (Menu_ActivateItem( m, item ));
			break;

		case K_JOY1:
		case K_JOY2:
		case K_JOY3:
		case K_JOY4:
		case K_AUX1:
		case K_AUX2:
		case K_AUX3:
		case K_AUX4:
		case K_AUX5:
		case K_AUX6:
		case K_AUX7:
		case K_AUX8:
		case K_AUX9:
		case K_AUX10:
		case K_AUX11:
		case K_AUX12:
		case K_AUX13:
		case K_AUX14:
		case K_AUX15:
		case K_AUX16:
		case K_KP_ENTER:
		case K_ENTER:
			if (item)
				if (!(item->flags & (QMF_MOUSEONLY|QMF_GRAYED|QMF_INACTIVE)))
					return (Menu_ActivateItem( m, item ));
			break;
	}

	return sound;
}