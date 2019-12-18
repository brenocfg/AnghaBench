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
struct TYPE_3__ {int* cursor; int* buffer; int* max; int /*<<< orphan*/  curLine; } ;
typedef  TYPE_1__ picoParser_t ;

/* Variables and functions */

void _pico_parse_skip_white( picoParser_t *p, int *hasLFs ){
	/* sanity checks */
	if ( p == NULL || p->cursor == NULL ) {
		return;
	}

	/* skin white spaces */
	while ( 1 )
	{
		/* sanity checks */
		if ( p->cursor <  p->buffer ||
			 p->cursor >= p->max ) {
			return;
		}
		/* break for chars other than white spaces */
		if ( *p->cursor >  0x20 ) {
			break;
		}
		if ( *p->cursor == 0x00 ) {
			return;
		}

		/* a bit of linefeed handling */
		if ( *p->cursor == '\n' ) {
			*hasLFs = 1;
			p->curLine++;
		}
		/* go to next character */
		p->cursor++;
	}
}