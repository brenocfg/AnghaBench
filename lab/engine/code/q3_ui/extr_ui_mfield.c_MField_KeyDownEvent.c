#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int cursor; int scroll; int widthInChars; scalar_t__ buffer; } ;
typedef  TYPE_1__ mfield_t ;

/* Variables and functions */
 int /*<<< orphan*/  K_CTRL ; 
 int K_DEL ; 
 int K_END ; 
 int K_HOME ; 
 int K_INS ; 
 int K_KP_DEL ; 
 int K_KP_END ; 
 int K_KP_HOME ; 
 int K_KP_INS ; 
 int K_KP_LEFTARROW ; 
 int K_KP_RIGHTARROW ; 
 int K_LEFTARROW ; 
 int K_RIGHTARROW ; 
 int /*<<< orphan*/  K_SHIFT ; 
 int /*<<< orphan*/  MField_Paste (TYPE_1__*) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int) ; 
 int strlen (scalar_t__) ; 
 char tolower (int) ; 
 int /*<<< orphan*/  trap_Key_GetOverstrikeMode () ; 
 scalar_t__ trap_Key_IsDown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_Key_SetOverstrikeMode (int) ; 

void MField_KeyDownEvent( mfield_t *edit, int key ) {
	int		len;

	// shift-insert is paste
	if ( ( ( key == K_INS ) || ( key == K_KP_INS ) ) && trap_Key_IsDown( K_SHIFT ) ) {
		MField_Paste( edit );
		return;
	}

	len = strlen( edit->buffer );

	if ( key == K_DEL || key == K_KP_DEL ) {
		if ( edit->cursor < len ) {
			memmove( edit->buffer + edit->cursor, 
				edit->buffer + edit->cursor + 1, len - edit->cursor );
		}
		return;
	}

	if ( key == K_RIGHTARROW || key == K_KP_RIGHTARROW ) 
	{
		if ( edit->cursor < len ) {
			edit->cursor++;
		}
		if ( edit->cursor >= edit->scroll + edit->widthInChars && edit->cursor <= len )
		{
			edit->scroll++;
		}
		return;
	}

	if ( key == K_LEFTARROW || key == K_KP_LEFTARROW ) 
	{
		if ( edit->cursor > 0 ) {
			edit->cursor--;
		}
		if ( edit->cursor < edit->scroll )
		{
			edit->scroll--;
		}
		return;
	}

	if ( key == K_HOME || key == K_KP_HOME || ( tolower(key) == 'a' && trap_Key_IsDown( K_CTRL ) ) ) {
		edit->cursor = 0;
		edit->scroll = 0;
		return;
	}

	if ( key == K_END || key == K_KP_END || ( tolower(key) == 'e' && trap_Key_IsDown( K_CTRL ) ) ) {
		edit->cursor = len;
		edit->scroll = len - edit->widthInChars + 1;
		if (edit->scroll < 0)
			edit->scroll = 0;
		return;
	}

	if ( key == K_INS || key == K_KP_INS ) {
		trap_Key_SetOverstrikeMode( !trap_Key_GetOverstrikeMode() );
		return;
	}
}