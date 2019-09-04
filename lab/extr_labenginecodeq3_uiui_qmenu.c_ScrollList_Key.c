#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sfxHandle_t ;
struct TYPE_17__ {int flags; int x; int y; int /*<<< orphan*/  (* callback ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_18__ {int width; int separation; int columns; int height; int top; int numitems; int oldvalue; int curvalue; int** itemnames; TYPE_1__ generic; } ;
typedef  TYPE_2__ menulist_s ;
struct TYPE_19__ {int /*<<< orphan*/  cursory; int /*<<< orphan*/  cursorx; } ;

/* Variables and functions */
#define  K_DOWNARROW 146 
#define  K_END 145 
#define  K_HOME 144 
#define  K_KP_DOWNARROW 143 
#define  K_KP_END 142 
#define  K_KP_HOME 141 
#define  K_KP_LEFTARROW 140 
#define  K_KP_PGDN 139 
#define  K_KP_PGUP 138 
#define  K_KP_RIGHTARROW 137 
#define  K_KP_UPARROW 136 
#define  K_LEFTARROW 135 
#define  K_MOUSE1 134 
#define  K_MWHEELDOWN 133 
#define  K_MWHEELUP 132 
#define  K_PGDN 131 
#define  K_PGUP 130 
#define  K_RIGHTARROW 129 
#define  K_UPARROW 128 
 int QMF_CENTER_JUSTIFY ; 
 int QMF_HASMOUSEFOCUS ; 
 int /*<<< orphan*/  QM_GOTFOCUS ; 
 int /*<<< orphan*/  Q_isprint (int) ; 
 scalar_t__ Q_isupper (int) ; 
 int SMALLCHAR_HEIGHT ; 
 int SMALLCHAR_WIDTH ; 
 int /*<<< orphan*/  UI_CursorInRect (int,int,int,int) ; 
 int /*<<< orphan*/  menu_buzz_sound ; 
 int /*<<< orphan*/  menu_move_sound ; 
 int /*<<< orphan*/  menu_null_sound ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub12 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_3__ uis ; 

sfxHandle_t ScrollList_Key( menulist_s *l, int key )
{
	int	x;
	int	y;
	int	w;
	int	i;
	int	j;	
	int	c;
	int	cursorx;
	int	cursory;
	int	column;
	int	index;

	switch (key)
	{
		case K_MOUSE1:
			if (l->generic.flags & QMF_HASMOUSEFOCUS)
			{
				// check scroll region
				x = l->generic.x;
				y = l->generic.y;
				w = ( (l->width + l->separation) * l->columns - l->separation) * SMALLCHAR_WIDTH;
				if( l->generic.flags & QMF_CENTER_JUSTIFY ) {
					x -= w / 2;
				}
				if (UI_CursorInRect( x, y, w, l->height*SMALLCHAR_HEIGHT ))
				{
					cursorx = (uis.cursorx - x)/SMALLCHAR_WIDTH;
					column = cursorx / (l->width + l->separation);
					cursory = (uis.cursory - y)/SMALLCHAR_HEIGHT;
					index = column * l->height + cursory;
					if (l->top + index < l->numitems)
					{
						l->oldvalue = l->curvalue;
						l->curvalue = l->top + index;

						if (l->oldvalue != l->curvalue && l->generic.callback)
						{
							l->generic.callback( l, QM_GOTFOCUS );
							return (menu_move_sound);
						}
					}
				}
			
				// absorbed, silent sound effect
				return (menu_null_sound);
			}
			break;

		case K_KP_HOME:
		case K_HOME:
			l->oldvalue = l->curvalue;
			l->curvalue = 0;
			l->top      = 0;

			if (l->oldvalue != l->curvalue && l->generic.callback)
			{
				l->generic.callback( l, QM_GOTFOCUS );
				return (menu_move_sound);
			}
			return (menu_buzz_sound);

		case K_KP_END:
		case K_END:
			l->oldvalue = l->curvalue;
			l->curvalue = l->numitems-1;
			if( l->columns > 1 ) {
				c = (l->curvalue / l->height + 1) * l->height;
				l->top = c - (l->columns * l->height);
			}
			else {
				l->top = l->curvalue - (l->height - 1);
			}
			if (l->top < 0)
				l->top = 0;			

			if (l->oldvalue != l->curvalue && l->generic.callback)
			{
				l->generic.callback( l, QM_GOTFOCUS );
				return (menu_move_sound);
			}
			return (menu_buzz_sound);

		case K_PGUP:
		case K_KP_PGUP:
			if( l->columns > 1 ) {
				return menu_null_sound;
			}

			if (l->curvalue > 0)
			{
				l->oldvalue = l->curvalue;
				l->curvalue -= l->height-1;
				if (l->curvalue < 0)
					l->curvalue = 0;
				l->top = l->curvalue;
				if (l->top < 0)
					l->top = 0;

				if (l->generic.callback)
					l->generic.callback( l, QM_GOTFOCUS );

				return (menu_move_sound);
			}
			return (menu_buzz_sound);

		case K_PGDN:
		case K_KP_PGDN:
			if( l->columns > 1 ) {
				return menu_null_sound;
			}

			if (l->curvalue < l->numitems-1)
			{
				l->oldvalue = l->curvalue;
				l->curvalue += l->height-1;
				if (l->curvalue > l->numitems-1)
					l->curvalue = l->numitems-1;
				l->top = l->curvalue - (l->height-1);
				if (l->top < 0)
					l->top = 0;

				if (l->generic.callback)
					l->generic.callback( l, QM_GOTFOCUS );

				return (menu_move_sound);
			}
			return (menu_buzz_sound);

		case K_MWHEELUP:
			if( l->columns > 1 ) {
				return menu_null_sound;
			}

			if (l->top > 0)
			{
				// if scrolling 3 lines would replace over half of the
				// displayed items, only scroll 1 item at a time.
				int scroll = l->height < 6 ? 1 : 3;
				l->top -= scroll;
				if (l->top < 0)
					l->top = 0;

				if (l->generic.callback)
					l->generic.callback( l, QM_GOTFOCUS );

				// make scrolling silent
				return (menu_null_sound);
			}
			return (menu_buzz_sound);

		case K_MWHEELDOWN:
			if( l->columns > 1 ) {
				return menu_null_sound;
			}

			if (l->top < l->numitems-l->height)
			{
				// if scrolling 3 items would replace over half of the
				// displayed items, only scroll 1 item at a time.
				int scroll = l->height < 6 ? 1 : 3;
				l->top += scroll;
				if (l->top > l->numitems-l->height)
					l->top = l->numitems-l->height;

				if (l->generic.callback)
					l->generic.callback( l, QM_GOTFOCUS );

				// make scrolling silent
				return (menu_null_sound);
			}
			return (menu_buzz_sound);

		case K_KP_UPARROW:
		case K_UPARROW:
			if( l->curvalue == 0 ) {
				return menu_buzz_sound;
			}

			l->oldvalue = l->curvalue;
			l->curvalue--;

			if( l->curvalue < l->top ) {
				if( l->columns == 1 ) {
					l->top--;
				}
				else {
					l->top -= l->height;
				}
			}

			if( l->generic.callback ) {
				l->generic.callback( l, QM_GOTFOCUS );
			}

			return (menu_move_sound);

		case K_KP_DOWNARROW:
		case K_DOWNARROW:
			if( l->curvalue == l->numitems - 1 ) {
				return menu_buzz_sound;
			}

			l->oldvalue = l->curvalue;
			l->curvalue++;

			if( l->curvalue >= l->top + l->columns * l->height ) {
				if( l->columns == 1 ) {
					l->top++;
				}
				else {
					l->top += l->height;
				}
			}

			if( l->generic.callback ) {
				l->generic.callback( l, QM_GOTFOCUS );
			}

			return menu_move_sound;

		case K_KP_LEFTARROW:
		case K_LEFTARROW:
			if( l->columns == 1 ) {
				return menu_null_sound;
			}

			if( l->curvalue < l->height ) {
				return menu_buzz_sound;
			}

			l->oldvalue = l->curvalue;
			l->curvalue -= l->height;

			if( l->curvalue < l->top ) {
				l->top -= l->height;
			}

			if( l->generic.callback ) {
				l->generic.callback( l, QM_GOTFOCUS );
			}

			return menu_move_sound;

		case K_KP_RIGHTARROW:
		case K_RIGHTARROW:
			if( l->columns == 1 ) {
				return menu_null_sound;
			}

			c = l->curvalue + l->height;

			if( c >= l->numitems ) {
				return menu_buzz_sound;
			}

			l->oldvalue = l->curvalue;
			l->curvalue = c;

			if( l->curvalue > l->top + l->columns * l->height - 1 ) {
				l->top += l->height;
			}

			if( l->generic.callback ) {
				l->generic.callback( l, QM_GOTFOCUS );
			}

			return menu_move_sound;
	}

	// cycle look for ascii key inside list items
	if ( !Q_isprint( key ) )
		return (0);

	// force to lower for case insensitive compare
	if ( Q_isupper( key ) )
	{
		key -= 'A' - 'a';
	}

	// iterate list items
	for (i=1; i<=l->numitems; i++)
	{
		j = (l->curvalue + i) % l->numitems;
		c = l->itemnames[j][0];
		if ( Q_isupper( c ) )
		{
			c -= 'A' - 'a';
		}

		if (c == key)
		{
			// set current item, mimic windows listbox scroll behavior
			if (j < l->top)
			{
				// behind top most item, set this as new top
				l->top = j;
			}
			else if (j > l->top+l->height-1)
			{
				// past end of list box, do page down
				l->top = (j+1) - l->height;
			}
			
			if (l->curvalue != j)
			{
				l->oldvalue = l->curvalue;
				l->curvalue = j;
				if (l->generic.callback)
					l->generic.callback( l, QM_GOTFOCUS );
				return ( menu_move_sound );			
			}

			return (menu_buzz_sound);
		}
	}

	return (menu_buzz_sound);
}