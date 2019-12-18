#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int qboolean ;
struct TYPE_5__ {int x; int y; scalar_t__ menuPosition; int flags; int /*<<< orphan*/  name; scalar_t__ top; scalar_t__ bottom; scalar_t__ left; scalar_t__ right; TYPE_1__* parent; } ;
struct TYPE_6__ {int /*<<< orphan*/  string; TYPE_2__ generic; } ;
typedef  TYPE_3__ menutext_s ;
struct TYPE_4__ {scalar_t__ cursor; } ;

/* Variables and functions */
 int QMF_BLINK ; 
 int QMF_GRAYED ; 
 scalar_t__ SMALLCHAR_WIDTH ; 
 int UI_BLINK ; 
 int UI_CENTER ; 
 int /*<<< orphan*/  UI_DrawChar (int,int,int,int,float*) ; 
 int /*<<< orphan*/  UI_DrawString (scalar_t__,int,int /*<<< orphan*/ ,int,float*) ; 
 int /*<<< orphan*/  UI_FillRect (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int UI_LEFT ; 
 int UI_PULSE ; 
 int UI_RIGHT ; 
 int UI_SMALLFONT ; 
 int /*<<< orphan*/  listbar_color ; 
 float* text_color_disabled ; 
 float* text_color_highlight ; 
 float* text_color_normal ; 

__attribute__((used)) static void PlayerName_Draw( void *item ) {
	menutext_s	*s;
	float		*color;
	int			x, y;
	int			style;
	qboolean	focus;

	s = (menutext_s *)item;

	x = s->generic.x;
	y =	s->generic.y;

	style = UI_SMALLFONT;
	focus = (s->generic.parent->cursor == s->generic.menuPosition);

	if ( s->generic.flags & QMF_GRAYED )
		color = text_color_disabled;
	else if ( focus )
	{
		color = text_color_highlight;
		style |= UI_PULSE;
	}
	else if ( s->generic.flags & QMF_BLINK )
	{
		color = text_color_highlight;
		style |= UI_BLINK;
	}
	else
		color = text_color_normal;

	if ( focus )
	{
		// draw cursor
		UI_FillRect( s->generic.left, s->generic.top, s->generic.right-s->generic.left+1, s->generic.bottom-s->generic.top+1, listbar_color ); 
		UI_DrawChar( x, y, 13, UI_CENTER|UI_BLINK|UI_SMALLFONT, color);
	}

	UI_DrawString( x - SMALLCHAR_WIDTH, y, s->generic.name, style|UI_RIGHT, color );
	UI_DrawString( x + SMALLCHAR_WIDTH, y, s->string, style|UI_LEFT, color );
}