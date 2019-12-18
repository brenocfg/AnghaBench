#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int cursor; int scroll; int widthInChars; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ field_t ;
struct TYPE_6__ {scalar_t__ down; } ;

/* Variables and functions */
 int /*<<< orphan*/  Field_Paste (TYPE_1__*) ; 
#define  K_DEL 133 
#define  K_END 132 
#define  K_HOME 131 
#define  K_INS 130 
 int K_KP_INS ; 
#define  K_LEFTARROW 129 
#define  K_RIGHTARROW 128 
 size_t K_SHIFT ; 
 int key_overstrikeMode ; 
 TYPE_2__* keys ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int tolower (int) ; 

void Field_KeyDownEvent( field_t *edit, int key ) {
	int		len;

	// shift-insert is paste
	if ( ( ( key == K_INS ) || ( key == K_KP_INS ) ) && keys[K_SHIFT].down ) {
		Field_Paste( edit );
		return;
	}

	key = tolower( key );
	len = strlen( edit->buffer );

	switch ( key ) {
		case K_DEL:
			if ( edit->cursor < len ) {
				memmove( edit->buffer + edit->cursor, 
					edit->buffer + edit->cursor + 1, len - edit->cursor );
			}
			break;

		case K_RIGHTARROW:
			if ( edit->cursor < len ) {
				edit->cursor++;
			}
			break;

		case K_LEFTARROW:
			if ( edit->cursor > 0 ) {
				edit->cursor--;
			}
			break;

		case K_HOME:
			edit->cursor = 0;
			break;

		case K_END:
			edit->cursor = len;
			break;

		case K_INS:
			key_overstrikeMode = !key_overstrikeMode;
			break;

		default:
			break;
	}

	// Change scroll if cursor is no longer visible
	if ( edit->cursor < edit->scroll ) {
		edit->scroll = edit->cursor;
	} else if ( edit->cursor >= edit->scroll + edit->widthInChars && edit->cursor <= len ) {
		edit->scroll = edit->cursor - edit->widthInChars + 1;
	}
}