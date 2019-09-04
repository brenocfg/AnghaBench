#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  menutext_s ;
typedef  int /*<<< orphan*/  menuslider_s ;
typedef  int /*<<< orphan*/  menuradiobutton_s ;
typedef  int /*<<< orphan*/  menulist_s ;
struct TYPE_4__ {size_t nitems; void** items; } ;
typedef  TYPE_1__ menuframework_s ;
typedef  int /*<<< orphan*/  menufield_s ;
struct TYPE_5__ {size_t menuPosition; int flags; int type; TYPE_1__* parent; } ;
typedef  TYPE_2__ menucommon_s ;
typedef  int /*<<< orphan*/  menubitmap_s ;
typedef  int /*<<< orphan*/  menuaction_s ;

/* Variables and functions */
 int /*<<< orphan*/  Action_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BText_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Bitmap_Init (int /*<<< orphan*/ *) ; 
 size_t MAX_MENUITEMS ; 
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
 int /*<<< orphan*/  MenuField_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PText_Init (int /*<<< orphan*/ *) ; 
 int QMF_HASMOUSEFOCUS ; 
 int QMF_NODEFAULTINIT ; 
 int /*<<< orphan*/  RadioButton_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ScrollList_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Slider_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinControl_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Text_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trap_Error (char*) ; 
 char* va (char*,int) ; 

void Menu_AddItem( menuframework_s *menu, void *item )
{
	menucommon_s	*itemptr;

	if (menu->nitems >= MAX_MENUITEMS)
		trap_Error ("Menu_AddItem: excessive items");

	menu->items[menu->nitems] = item;
	((menucommon_s*)menu->items[menu->nitems])->parent        = menu;
	((menucommon_s*)menu->items[menu->nitems])->menuPosition  = menu->nitems;
	((menucommon_s*)menu->items[menu->nitems])->flags        &= ~QMF_HASMOUSEFOCUS;

	// perform any item specific initializations
	itemptr = (menucommon_s*)item;
	if (!(itemptr->flags & QMF_NODEFAULTINIT))
	{
		switch (itemptr->type)
		{
			case MTYPE_ACTION:
				Action_Init((menuaction_s*)item);
				break;

			case MTYPE_FIELD:
				MenuField_Init((menufield_s*)item);
				break;

			case MTYPE_SPINCONTROL:
				SpinControl_Init((menulist_s*)item);
				break;

			case MTYPE_RADIOBUTTON:
				RadioButton_Init((menuradiobutton_s*)item);
				break;

			case MTYPE_SLIDER:
				Slider_Init((menuslider_s*)item);
				break;

			case MTYPE_BITMAP:
				Bitmap_Init((menubitmap_s*)item);
				break;

			case MTYPE_TEXT:
				Text_Init((menutext_s*)item);
				break;

			case MTYPE_SCROLLLIST:
				ScrollList_Init((menulist_s*)item);
				break;

			case MTYPE_PTEXT:
				PText_Init((menutext_s*)item);
				break;

			case MTYPE_BTEXT:
				BText_Init((menutext_s*)item);
				break;

			default:
				trap_Error( va("Menu_Init: unknown type %d", itemptr->type) );
		}
	}

	menu->nitems++;
}