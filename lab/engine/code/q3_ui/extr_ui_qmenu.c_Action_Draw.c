#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; scalar_t__ menuPosition; int x; int y; TYPE_1__* parent; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {TYPE_2__ generic; } ;
typedef  TYPE_3__ menuaction_s ;
struct TYPE_5__ {scalar_t__ cursor; } ;

/* Variables and functions */
 scalar_t__ BIGCHAR_WIDTH ; 
 int QMF_BLINK ; 
 int QMF_GRAYED ; 
 int QMF_HIGHLIGHT_IF_FOCUS ; 
 int QMF_PULSEIFFOCUS ; 
 int UI_BLINK ; 
 int /*<<< orphan*/  UI_DrawChar (scalar_t__,int,int,int,float*) ; 
 int /*<<< orphan*/  UI_DrawString (int,int,int /*<<< orphan*/ ,int,float*) ; 
 int UI_LEFT ; 
 int UI_PULSE ; 
 float* color_blue ; 
 float* text_color_disabled ; 

__attribute__((used)) static void Action_Draw( menuaction_s *a )
{
	int		x, y;
	int		style;
	float*	color;

	style = 0;
  //edited
	color = color_blue; //menu_text_color
	if ( a->generic.flags & QMF_GRAYED )
	{
		color = text_color_disabled;
	}
	else if (( a->generic.flags & QMF_PULSEIFFOCUS ) && ( a->generic.parent->cursor == a->generic.menuPosition ))
	{
		color = color_blue; //text_color_highlight
		style = UI_PULSE;
	}
	else if (( a->generic.flags & QMF_HIGHLIGHT_IF_FOCUS ) && ( a->generic.parent->cursor == a->generic.menuPosition ))
	{
		color = color_blue; //text_color_highlight
	}
	else if ( a->generic.flags & QMF_BLINK )
	{
		style = UI_BLINK;
		color = color_blue; //text_color_highlight
	}

	x = a->generic.x;
	y = a->generic.y;

	UI_DrawString( x, y, a->generic.name, UI_LEFT|style, color );

	if ( a->generic.parent->cursor == a->generic.menuPosition )
	{
		// draw cursor
		UI_DrawChar( x - BIGCHAR_WIDTH, y, 13, UI_LEFT|UI_BLINK, color);
	}
}