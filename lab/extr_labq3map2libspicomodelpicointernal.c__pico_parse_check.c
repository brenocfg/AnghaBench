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
struct TYPE_4__ {int /*<<< orphan*/  token; } ;
typedef  TYPE_1__ picoParser_t ;

/* Variables and functions */
 int /*<<< orphan*/  _pico_parse_ex (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

int _pico_parse_check( picoParser_t *p, int allowLFs, char *str ){
	if ( !_pico_parse_ex( p,allowLFs,1 ) ) {
		return 0;
	}
	if ( !strcmp( p->token,str ) ) {
		return 1;
	}
	return 0;
}