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
struct TYPE_4__ {int /*<<< orphan*/  vmap; int /*<<< orphan*/  polygon; int /*<<< orphan*/  point; struct TYPE_4__* name; } ;
typedef  TYPE_1__ lwLayer ;
typedef  int /*<<< orphan*/  ListFreeFunc ;

/* Variables and functions */
 int /*<<< orphan*/  _pico_free (TYPE_1__*) ; 
 int /*<<< orphan*/  lwFreePoints (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lwFreePolygons (int /*<<< orphan*/ *) ; 
 scalar_t__ lwFreeVMap ; 
 int /*<<< orphan*/  lwListFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void lwFreeLayer( lwLayer *layer ){
	if ( layer ) {
		if ( layer->name ) {
			_pico_free( layer->name );
		}
		lwFreePoints( &layer->point );
		lwFreePolygons( &layer->polygon );
		lwListFree( layer->vmap, (ListFreeFunc) lwFreeVMap );
		_pico_free( layer );
	}
}