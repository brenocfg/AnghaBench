#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ culled; TYPE_2__* shaderInfo; int /*<<< orphan*/ * winding; } ;
typedef  TYPE_3__ side_t ;
typedef  scalar_t__ qboolean ;
struct TYPE_12__ {int /*<<< orphan*/  dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_4__ plane_t ;
struct TYPE_13__ {int compileFlags; int numsides; TYPE_1__* sides; } ;
typedef  TYPE_5__ brush_t ;
struct TYPE_10__ {scalar_t__ polygonOffset; scalar_t__ autosprite; } ;
struct TYPE_9__ {int compileFlags; size_t planenum; } ;

/* Variables and functions */
 int C_NODRAW ; 
 int C_TRANSLUCENT ; 
 int SIDE_CROSS ; 
 int SIDE_FRONT ; 
 int WindingOnPlaneSide (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_numHiddenFaces ; 
 TYPE_4__* mapplanes ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 

qboolean SideInBrush( side_t *side, brush_t *b ){
	int i, s;
	plane_t     *plane;


	/* ignore sides w/o windings or shaders */
	if ( side->winding == NULL || side->shaderInfo == NULL ) {
		return qtrue;
	}

	/* ignore culled sides and translucent brushes */
	if ( side->culled == qtrue || ( b->compileFlags & C_TRANSLUCENT ) ) {
		return qfalse;
	}

	/* side iterator */
	for ( i = 0; i < b->numsides; i++ )
	{
		/* fail if any sides are caulk */
		if ( b->sides[ i ].compileFlags & C_NODRAW ) {
			return qfalse;
		}

		/* check if side's winding is on or behind the plane */
		plane = &mapplanes[ b->sides[ i ].planenum ];
		s = WindingOnPlaneSide( side->winding, plane->normal, plane->dist );
		if ( s == SIDE_FRONT || s == SIDE_CROSS ) {
			return qfalse;
		}
	}

	/* don't cull autosprite or polygonoffset surfaces */
	if ( side->shaderInfo ) {
		if ( side->shaderInfo->autosprite || side->shaderInfo->polygonOffset ) {
			return qfalse;
		}
	}

	/* inside */
	side->culled = qtrue;
	g_numHiddenFaces++;
	return qtrue;
}