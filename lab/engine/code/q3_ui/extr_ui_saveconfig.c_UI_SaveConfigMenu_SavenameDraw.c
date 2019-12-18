#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_9__ {int widthInChars; } ;
struct TYPE_7__ {TYPE_1__ generic; TYPE_5__ field; } ;
typedef  TYPE_2__ menufield_s ;
struct TYPE_8__ {int /*<<< orphan*/  menu; } ;

/* Variables and functions */
 int /*<<< orphan*/  MField_Draw (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,float*) ; 
 TYPE_2__* Menu_ItemAtCursor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SMALLCHAR_HEIGHT ; 
 int SMALLCHAR_WIDTH ; 
 int UI_CENTER ; 
 int /*<<< orphan*/  UI_DrawProportionalString (int,int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_FillRect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int UI_LEFT ; 
 int UI_PULSE ; 
 int UI_SMALLFONT ; 
 int /*<<< orphan*/  colorBlack ; 
 float* colorRed ; 
 int /*<<< orphan*/  color_blue ; 
 TYPE_3__ saveConfig ; 
 float* text_color_highlight ; 

__attribute__((used)) static void UI_SaveConfigMenu_SavenameDraw( void *self ) {
	menufield_s		*f;
	int				style;
	float			*color;

	f = (menufield_s *)self;

	if( f == Menu_ItemAtCursor( &saveConfig.menu ) ) {
		style = UI_LEFT|UI_PULSE|UI_SMALLFONT;
		color = text_color_highlight;
	}
	else {
		style = UI_LEFT|UI_SMALLFONT;
		color = colorRed;
	}

	UI_DrawProportionalString( 320, 192, "Enter filename:", UI_CENTER|UI_SMALLFONT, color_blue );
	UI_FillRect( f->generic.x, f->generic.y, f->field.widthInChars*SMALLCHAR_WIDTH, SMALLCHAR_HEIGHT, colorBlack );
	MField_Draw( &f->field, f->generic.x, f->generic.y, style, color );
}