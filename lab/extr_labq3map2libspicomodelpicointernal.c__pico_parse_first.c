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

char *_pico_parse_first( picoParser_t *p ){
	/* sanity check */
	if ( p == NULL ) {
		return NULL;
	}

	/* try to read next token (with lfs & quots) */
	if ( !_pico_parse_ex( p,1,1 ) ) {
		return NULL;
	}

	/* return ptr to the token string */
	return p->token;
}