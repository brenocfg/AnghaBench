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
struct TYPE_4__ {int /*<<< orphan*/  taglist; int /*<<< orphan*/  surf; int /*<<< orphan*/  clip; int /*<<< orphan*/  env; int /*<<< orphan*/  layer; } ;
typedef  TYPE_1__ lwObject ;
typedef  int /*<<< orphan*/  ListFreeFunc ;

/* Variables and functions */
 int /*<<< orphan*/  _pico_free (TYPE_1__*) ; 
 scalar_t__ lwFreeClip ; 
 scalar_t__ lwFreeEnvelope ; 
 scalar_t__ lwFreeLayer ; 
 scalar_t__ lwFreeSurface ; 
 int /*<<< orphan*/  lwFreeTags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lwListFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void lwFreeObject( lwObject *object ){
	if ( object ) {
		lwListFree( object->layer, (ListFreeFunc) lwFreeLayer );
		lwListFree( object->env, (ListFreeFunc) lwFreeEnvelope );
		lwListFree( object->clip, (ListFreeFunc) lwFreeClip );
		lwListFree( object->surf, (ListFreeFunc) lwFreeSurface );
		lwFreeTags( &object->taglist );
		_pico_free( object );
	}
}