#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vec_t ;
struct TYPE_12__ {size_t planenum; } ;
typedef  TYPE_3__ side_t ;
struct TYPE_11__ {int width; int height; TYPE_1__* verts; } ;
struct TYPE_13__ {TYPE_2__ mesh; struct TYPE_13__* next; } ;
typedef  TYPE_4__ parseMesh_t ;
struct TYPE_14__ {int /*<<< orphan*/  origin; TYPE_4__* patches; TYPE_6__* brushes; } ;
typedef  TYPE_5__ entity_t ;
struct TYPE_15__ {int numsides; TYPE_3__* sides; struct TYPE_15__* next; } ;
typedef  TYPE_6__ brush_t ;
struct TYPE_16__ {int /*<<< orphan*/  normal; scalar_t__ dist; } ;
struct TYPE_10__ {int /*<<< orphan*/  xyz; } ;

/* Variables and functions */
 int /*<<< orphan*/  CreateBrushWindings (TYPE_6__*) ; 
 scalar_t__ DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t FindFloatPlane (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__* mapplanes ; 

void AdjustBrushesForOrigin( entity_t *ent ){

	int i;
	side_t      *s;
	vec_t newdist;
	brush_t     *b;
	parseMesh_t *p;


	/* walk brush list */
	for ( b = ent->brushes; b != NULL; b = b->next )
	{
		/* offset brush planes */
		for ( i = 0; i < b->numsides; i++ )
		{
			/* get brush side */
			s = &b->sides[ i ];

			/* offset side plane */
			newdist = mapplanes[ s->planenum ].dist - DotProduct( mapplanes[ s->planenum ].normal, ent->origin );

			/* find a new plane */
			s->planenum = FindFloatPlane( mapplanes[ s->planenum ].normal, newdist, 0, NULL );
		}

		/* rebuild brush windings (ydnar: just offsetting the winding above should be fine) */
		CreateBrushWindings( b );
	}

	/* walk patch list */
	for ( p = ent->patches; p != NULL; p = p->next )
	{
		for ( i = 0; i < ( p->mesh.width * p->mesh.height ); i++ )
			VectorSubtract( p->mesh.verts[ i ].xyz, ent->origin, p->mesh.verts[ i ].xyz );
	}
}