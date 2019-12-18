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
struct TYPE_3__ {char* buffer; char* cursor; char* max; size_t tokenSize; char* token; int /*<<< orphan*/  curLine; } ;
typedef  TYPE_1__ picoParser_t ;

/* Variables and functions */

int _pico_parse_ex( picoParser_t *p, int allowLFs, int handleQuoted ){
	int hasLFs = 0;
	char *old;

	/* sanity checks */
	if ( p == NULL || p->buffer == NULL ||
		 p->cursor <  p->buffer ||
		 p->cursor >= p->max ) {
		return 0;
	}
	/* clear parser token */
	p->tokenSize = 0;
	p->token[ 0 ] = '\0';
	old = p->cursor;

	/* skip whitespaces */
	while ( p->cursor < p->max && *p->cursor <= 32 )
	{
		if ( *p->cursor == '\n' ) {
			p->curLine++;
			hasLFs++;
		}
		p->cursor++;
	}
	/* return if we're not allowed to go beyond lfs */
	if ( ( hasLFs > 0 ) && !allowLFs ) {
		p->cursor = old;
		return 0;
	}
	/* get next quoted string */
	if ( *p->cursor == '\"' && handleQuoted ) {
		p->cursor++;
		while ( p->cursor < p->max && *p->cursor )
		{
			if ( *p->cursor == '\\' ) {
				if ( *( p->cursor + 1 ) == '"' ) {
					p->cursor++;
				}
				p->token[ p->tokenSize++ ] = *p->cursor++;
				continue;
			}
			else if ( *p->cursor == '\"' ) {
				p->cursor++;
				break;
			}
			else if ( *p->cursor == '\n' ) {
				p->curLine++;
			}
			p->token[ p->tokenSize++ ] = *p->cursor++;
		}
		/* terminate token */
		p->token[ p->tokenSize ] = '\0';
		return 1;
	}
	/* otherwise get next word */
	while ( p->cursor < p->max && *p->cursor > 32 )
	{
		if ( *p->cursor == '\n' ) {
			p->curLine++;
		}
		p->token[ p->tokenSize++ ] = *p->cursor++;
	}
	/* terminate token */
	p->token[ p->tokenSize ] = '\0';
	return 1;
}