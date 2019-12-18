#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  menutext_s ;
typedef  int /*<<< orphan*/  menuslider_s ;
typedef  int /*<<< orphan*/  menuradiobutton_s ;
typedef  int /*<<< orphan*/  menulist_s ;
struct TYPE_8__ {int nitems; scalar_t__* items; } ;
typedef  TYPE_1__ menuframework_s ;
typedef  int /*<<< orphan*/  menufield_s ;
struct TYPE_9__ {int flags; int type; int left; int top; int right; int bottom; int /*<<< orphan*/  (* statusbar ) (void*) ;int /*<<< orphan*/  (* ownerdraw ) (TYPE_2__*) ;} ;
typedef  TYPE_2__ menucommon_s ;
typedef  int /*<<< orphan*/  menubitmap_s ;
typedef  int /*<<< orphan*/  menuaction_s ;
struct TYPE_10__ {scalar_t__ debug; } ;

/* Variables and functions */
 int /*<<< orphan*/  Action_Draw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BText_Draw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Bitmap_Draw (int /*<<< orphan*/ *) ; 
#define  MTYPE_ACTION 137 
#define  MTYPE_BITMAP 136 
#define  MTYPE_BTEXT 135 
#define  MTYPE_FIELD 134 
#define  MTYPE_PTEXT 133 
#define  MTYPE_RADIOBUTTON 132 
#define  MTYPE_SCROLLLIST 131 
#define  MTYPE_SLIDER 130 
#define  MTYPE_SPINCONTROL 129 
#define  MTYPE_TEXT 128 
 int /*<<< orphan*/  MenuField_Draw (int /*<<< orphan*/ *) ; 
 TYPE_2__* Menu_ItemAtCursor (TYPE_1__*) ; 
 int /*<<< orphan*/  PText_Draw (int /*<<< orphan*/ *) ; 
 int QMF_HASMOUSEFOCUS ; 
 int QMF_HIDDEN ; 
 int QMF_INACTIVE ; 
 int /*<<< orphan*/  RadioButton_Draw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ScrollList_Draw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Slider_Draw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinControl_Draw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Text_Draw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UI_DrawRect (int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  colorWhite ; 
 int /*<<< orphan*/  colorYellow ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (void*) ; 
 int /*<<< orphan*/  trap_Error (int /*<<< orphan*/ ) ; 
 TYPE_3__ uis ; 
 int /*<<< orphan*/  va (char*,int) ; 

void Menu_Draw( menuframework_s *menu )
{
	int				i;
	menucommon_s	*itemptr;

	// draw menu
	for (i=0; i<menu->nitems; i++)
	{
		itemptr = (menucommon_s*)menu->items[i];

		if (itemptr->flags & QMF_HIDDEN)
			continue;

		if (itemptr->ownerdraw)
		{
			// total subclassing, owner draws everything
			itemptr->ownerdraw( itemptr );
		}	
		else 
		{
			switch (itemptr->type)
			{	
				case MTYPE_RADIOBUTTON:
					RadioButton_Draw( (menuradiobutton_s*)itemptr );
					break;

				case MTYPE_FIELD:
					MenuField_Draw( (menufield_s*)itemptr );
					break;
		
				case MTYPE_SLIDER:
					Slider_Draw( (menuslider_s*)itemptr );
					break;
 
				case MTYPE_SPINCONTROL:
					SpinControl_Draw( (menulist_s*)itemptr );
					break;
		
				case MTYPE_ACTION:
					Action_Draw( (menuaction_s*)itemptr );
					break;
		
				case MTYPE_BITMAP:
					Bitmap_Draw( (menubitmap_s*)itemptr );
					break;

				case MTYPE_TEXT:
					Text_Draw( (menutext_s*)itemptr );
					break;

				case MTYPE_SCROLLLIST:
					ScrollList_Draw( (menulist_s*)itemptr );
					break;
				
				case MTYPE_PTEXT:
					PText_Draw( (menutext_s*)itemptr );
					break;

				case MTYPE_BTEXT:
					BText_Draw( (menutext_s*)itemptr );
					break;

				default:
					trap_Error( va("Menu_Draw: unknown type %d", itemptr->type) );
			}
		}
#ifndef NDEBUG
		if( uis.debug ) {
			int	x;
			int	y;
			int	w;
			int	h;

			if( !( itemptr->flags & QMF_INACTIVE ) ) {
				x = itemptr->left;
				y = itemptr->top;
				w = itemptr->right - itemptr->left + 1;
				h =	itemptr->bottom - itemptr->top + 1;

				if (itemptr->flags & QMF_HASMOUSEFOCUS) {
					UI_DrawRect(x, y, w, h, colorYellow );
				}
				else {
					UI_DrawRect(x, y, w, h, colorWhite );
				}
			}
		}
#endif
	}

	itemptr = Menu_ItemAtCursor( menu );
	if ( itemptr && itemptr->statusbar)
		itemptr->statusbar( ( void * ) itemptr );
}