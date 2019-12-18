#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec4_t ;
struct TYPE_3__ {int widthInChars; char* buffer; int scroll; int cursor; } ;
typedef  TYPE_1__ mfield_t ;

/* Variables and functions */
 int BIGCHAR_WIDTH ; 
 int GIANTCHAR_WIDTH ; 
 int MAX_STRING_CHARS ; 
 int SMALLCHAR_WIDTH ; 
 int UI_BLINK ; 
 int UI_CENTER ; 
 int /*<<< orphan*/  UI_DrawChar (int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_DrawString (int,int,char*,int,int /*<<< orphan*/ ) ; 
 int UI_GIANTFONT ; 
 int UI_PULSE ; 
 int UI_RIGHT ; 
 int UI_SMALLFONT ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  trap_Error (char*) ; 
 scalar_t__ trap_Key_GetOverstrikeMode () ; 

void MField_Draw( mfield_t *edit, int x, int y, int style, vec4_t color ) {
	int		len;
	int		charw;
	int		drawLen;
	int		prestep;
	int		cursorChar;
	char	str[MAX_STRING_CHARS];

	drawLen = edit->widthInChars;
	len     = strlen( edit->buffer ) + 1;

	// guarantee that cursor will be visible
	if ( len <= drawLen ) {
		prestep = 0;
	} else {
		if ( edit->scroll + drawLen > len ) {
			edit->scroll = len - drawLen;
			if ( edit->scroll < 0 ) {
				edit->scroll = 0;
			}
		}
		prestep = edit->scroll;
	}

	if ( prestep + drawLen > len ) {
		drawLen = len - prestep;
	}

	// extract <drawLen> characters from the field at <prestep>
	if ( drawLen >= MAX_STRING_CHARS ) {
		trap_Error( "drawLen >= MAX_STRING_CHARS" );
	}
	memcpy( str, edit->buffer + prestep, drawLen );
	str[ drawLen ] = 0;

	UI_DrawString( x, y, str, style, color );

	// draw the cursor
	if (!(style & UI_PULSE)) {
		return;
	}

	if ( trap_Key_GetOverstrikeMode() ) {
		cursorChar = 11;
	} else {
		cursorChar = 10;
	}

	style &= ~UI_PULSE;
	style |= UI_BLINK;

	if (style & UI_SMALLFONT)
	{
		charw =	SMALLCHAR_WIDTH;
	}
	else if (style & UI_GIANTFONT)
	{
		charw =	GIANTCHAR_WIDTH;
	}
	else
	{
		charw =	BIGCHAR_WIDTH;
	}

	if (style & UI_CENTER)
	{
		len = strlen(str);
		x = x - len*charw/2;
	}
	else if (style & UI_RIGHT)
	{
		len = strlen(str);
		x = x - len*charw;
	}
	
	UI_DrawChar( x + ( edit->cursor - prestep ) * charw, y, cursorChar, style & ~(UI_CENTER|UI_RIGHT), color );
}