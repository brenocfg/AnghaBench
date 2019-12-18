#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int numsides; TYPE_1__* sides; int /*<<< orphan*/ * next; } ;
typedef  TYPE_2__ brush_t ;
struct TYPE_8__ {int /*<<< orphan*/ * winding; } ;

/* Variables and functions */
 TYPE_2__* AllocBrush (int) ; 
 int /*<<< orphan*/ * CopyWinding (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,size_t) ; 

brush_t *CopyBrush( brush_t *brush ){
	brush_t     *newBrush;
	size_t size;
	int i;


	/* copy brush */
	size = sizeof( *brush ) + sizeof( *brush->sides ) * brush->numsides;
	newBrush = AllocBrush( brush->numsides );
	memcpy( newBrush, brush, size );

	/* ydnar: nuke linked list */
	newBrush->next = NULL;

	/* copy sides */
	for ( i = 0; i < brush->numsides; i++ )
	{
		if ( brush->sides[ i ].winding != NULL ) {
			newBrush->sides[ i ].winding = CopyWinding( brush->sides[ i ].winding );
		}
	}

	/* return it */
	return newBrush;
}