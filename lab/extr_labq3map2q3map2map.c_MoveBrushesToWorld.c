#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* next; } ;
typedef  TYPE_1__ parseMesh_t ;
struct TYPE_7__ {TYPE_1__* patches; TYPE_3__* colorModBrushes; TYPE_3__* brushes; } ;
typedef  TYPE_2__ entity_t ;
struct TYPE_8__ {struct TYPE_8__* nextColorModBrush; struct TYPE_8__* next; scalar_t__ opaque; } ;
typedef  TYPE_3__ brush_t ;
struct TYPE_9__ {TYPE_1__* patches; TYPE_3__* colorModBrushes; TYPE_3__* lastBrush; TYPE_3__* brushes; } ;

/* Variables and functions */
 TYPE_4__* entities ; 

void MoveBrushesToWorld( entity_t *ent ){
	brush_t     *b, *next;
	parseMesh_t *pm;


	/* move brushes */
	for ( b = ent->brushes; b != NULL; b = next )
	{
		/* get next brush */
		next = b->next;

		/* link opaque brushes to head of list, translucent brushes to end */
		if ( b->opaque || entities[ 0 ].lastBrush == NULL ) {
			b->next = entities[ 0 ].brushes;
			entities[ 0 ].brushes = b;
			if ( entities[ 0 ].lastBrush == NULL ) {
				entities[ 0 ].lastBrush = b;
			}
		}
		else
		{
			b->next = NULL;
			entities[ 0 ].lastBrush->next = b;
			entities[ 0 ].lastBrush = b;
		}
	}
	ent->brushes = NULL;

	/* ydnar: move colormod brushes */
	if ( ent->colorModBrushes != NULL ) {
		for ( b = ent->colorModBrushes; b->nextColorModBrush != NULL; b = b->nextColorModBrush ) ;

		b->nextColorModBrush = entities[ 0 ].colorModBrushes;
		entities[ 0 ].colorModBrushes = ent->colorModBrushes;

		ent->colorModBrushes = NULL;
	}

	/* move patches */
	if ( ent->patches != NULL ) {
		for ( pm = ent->patches; pm->next != NULL; pm = pm->next ) ;

		pm->next = entities[ 0 ].patches;
		entities[ 0 ].patches = ent->patches;

		ent->patches = NULL;
	}
}