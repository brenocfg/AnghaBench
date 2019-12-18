#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  winding_t ;
typedef  scalar_t__* vec4_t ;
struct TYPE_11__ {size_t planeNum; scalar_t__ planar; TYPE_1__* sideRef; } ;
typedef  TYPE_2__ mapDrawSurface_t ;
struct TYPE_12__ {scalar_t__** planes; } ;
typedef  TYPE_3__ decalProjector_t ;
struct TYPE_13__ {scalar_t__ dist; int /*<<< orphan*/  normal; } ;
struct TYPE_10__ {int /*<<< orphan*/ * side; } ;

/* Variables and functions */
 float DotProduct (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  ProjectDecalOntoWinding (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/ * WindingFromDrawSurf (TYPE_2__*) ; 
 scalar_t__* entityOrigin ; 
 TYPE_4__* mapplanes ; 

__attribute__((used)) static void ProjectDecalOntoFace( decalProjector_t *dp, mapDrawSurface_t *ds ){
	vec4_t plane;
	float d;
	winding_t   *w;


	/* dummy check */
	if ( ds->sideRef == NULL || ds->sideRef->side == NULL ) {
		return;
	}

	/* backface check */
	if ( ds->planar ) {
		VectorCopy( mapplanes[ ds->planeNum ].normal, plane );
		plane[ 3 ] = mapplanes[ ds->planeNum ].dist + DotProduct( plane, entityOrigin );
		d = DotProduct( dp->planes[ 0 ], plane );
		if ( d < -0.0001f ) {
			return;
		}
	}

	/* generate decal */
	w = WindingFromDrawSurf( ds );
	ProjectDecalOntoWinding( dp, ds, w );
}