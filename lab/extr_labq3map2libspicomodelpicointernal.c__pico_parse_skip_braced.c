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
struct TYPE_4__ {char* token; } ;
typedef  TYPE_1__ picoParser_t ;

/* Variables and functions */
 int /*<<< orphan*/  _pico_parse_ex (TYPE_1__*,int,int) ; 

int _pico_parse_skip_braced( picoParser_t *p ){
	int firstToken = 1;
	int level;

	/* sanity check */
	if ( p == NULL ) {
		return 0;
	}

	/* set the initial level for parsing */
	level = 0;

	/* skip braced section */
	while ( 1 )
	{
		/* read next token (lfs allowed) */
		if ( !_pico_parse_ex( p,1,1 ) ) {
			/* end of parser buffer reached */
			return 0;
		}
		/* first token must be an opening bracket */
		if ( firstToken && p->token[0] != '{' ) {
			/* opening bracket missing */
			return 0;
		}
		/* we only check this once */
		firstToken = 0;

		/* update level */
		if ( p->token[1] == '\0' ) {
			if ( p->token[0] == '{' ) {
				level++;
			}
			if ( p->token[0] == '}' ) {
				level--;
			}
		}
		/* break if we're back at our starting level */
		if ( level == 0 ) {
			break;
		}
	}
	/* successfully skipped braced section */
	return 1;
}