#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int qboolean ;
struct TYPE_7__ {int cursor; int /*<<< orphan*/  buffer; } ;
struct TYPE_6__ {scalar_t__ menuPosition; TYPE_1__* parent; } ;
struct TYPE_8__ {TYPE_3__ field; TYPE_2__ generic; } ;
typedef  TYPE_4__ menufield_s ;
struct TYPE_5__ {scalar_t__ cursor; } ;

/* Variables and functions */
 int BIGCHAR_HEIGHT ; 
 int BIGCHAR_WIDTH ; 
 int UI_BLINK ; 
 int UI_CDKeyMenu_PreValidateKey (int /*<<< orphan*/ ) ; 
 int UI_CENTER ; 
 int /*<<< orphan*/  UI_DrawChar (int,int,char,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_DrawProportionalString (int,int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_DrawString (int,int,int /*<<< orphan*/ ,int,float*) ; 
 int /*<<< orphan*/  UI_FillRect (int,int,int,int,int /*<<< orphan*/ ) ; 
 int UI_LEFT ; 
 int UI_PULSE ; 
 int UI_SMALLFONT ; 
 float* color_blue ; 
 int /*<<< orphan*/  color_red ; 
 int /*<<< orphan*/  color_white ; 
 int /*<<< orphan*/  color_yellow ; 
 int /*<<< orphan*/  listbar_color ; 
 scalar_t__ trap_Key_GetOverstrikeMode () ; 

__attribute__((used)) static void UI_CDKeyMenu_DrawKey( void *self ) {
	menufield_s		*f;
	qboolean		focus;
	int				style;
	char			c;
	float			*color;
	int				x, y;
	int				val;

	f = (menufield_s *)self;

	focus = (f->generic.parent->cursor == f->generic.menuPosition);

	style = UI_LEFT;
	if( focus ) {
		color = color_blue;
	}
	else {
		color = color_blue;
	}

	x = 320 - 8 * BIGCHAR_WIDTH;
	y = 240 - BIGCHAR_HEIGHT / 2;
	UI_FillRect( x, y, 16 * BIGCHAR_WIDTH, BIGCHAR_HEIGHT, listbar_color );
	UI_DrawString( x, y, f->field.buffer, style, color );

	// draw cursor if we have focus
	if( focus ) {
		if ( trap_Key_GetOverstrikeMode() ) {
			c = 11;
		} else {
			c = 10;
		}

		style &= ~UI_PULSE;
		style |= UI_BLINK;

		UI_DrawChar( x + f->field.cursor * BIGCHAR_WIDTH, y, c, style, color_white );
	}

	val = UI_CDKeyMenu_PreValidateKey( f->field.buffer );
	if( val == 1 ) {
		UI_DrawProportionalString( 320, 376, "Please enter your CD Key", UI_CENTER|UI_SMALLFONT, color_yellow );
	}
	else if ( val == 0 ) {
		UI_DrawProportionalString( 320, 376, "The CD Key appears to be valid, thank you", UI_CENTER|UI_SMALLFONT, color_white );
	}
	else {
		UI_DrawProportionalString( 320, 376, "The CD Key is not valid", UI_CENTER|UI_SMALLFONT, color_red );
	}
}