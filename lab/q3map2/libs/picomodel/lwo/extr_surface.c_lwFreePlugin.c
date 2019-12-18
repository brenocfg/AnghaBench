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
struct TYPE_4__ {struct TYPE_4__* data; struct TYPE_4__* name; struct TYPE_4__* ord; } ;
typedef  TYPE_1__ lwPlugin ;

/* Variables and functions */
 int /*<<< orphan*/  _pico_free (TYPE_1__*) ; 

void lwFreePlugin( lwPlugin *p ){
	if ( p ) {
		if ( p->ord ) {
			_pico_free( p->ord );
		}
		if ( p->name ) {
			_pico_free( p->name );
		}
		if ( p->data ) {
			_pico_free( p->data );
		}
		_pico_free( p );
	}
}