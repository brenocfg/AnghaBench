#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {float dist; int /*<<< orphan*/  normal; } ;
struct TYPE_12__ {float fraction; TYPE_1__ plane; } ;
struct TYPE_13__ {TYPE_2__ trace; int /*<<< orphan*/  end; int /*<<< orphan*/  start; int /*<<< orphan*/ * offsets; int /*<<< orphan*/  isPoint; } ;
typedef  TYPE_3__ traceWork_t ;
struct patchCollide_s {int numPlanes; int numFacets; TYPE_4__* planes; TYPE_5__* facets; } ;
typedef  int qboolean ;
struct TYPE_14__ {size_t signbits; float* plane; } ;
typedef  TYPE_4__ patchPlane_t ;
struct TYPE_15__ {size_t surfacePlane; int numBorders; int* borderPlanes; int* borderInward; } ;
typedef  TYPE_5__ facet_t ;
struct TYPE_16__ {scalar_t__ integer; } ;
typedef  TYPE_6__ cvar_t ;
struct TYPE_17__ {int /*<<< orphan*/  integer; } ;

/* Variables and functions */
 TYPE_6__* Cvar_Get (char*,char*,int /*<<< orphan*/ ) ; 
 float DotProduct (int /*<<< orphan*/ ,float*) ; 
 int MAX_PATCH_PLANES ; 
 float SURFACE_CLIP_EPSILON ; 
 int /*<<< orphan*/  VectorCopy (float*,int /*<<< orphan*/ ) ; 
 TYPE_8__* cm_playerCurveClip ; 
 TYPE_5__ const* debugFacet ; 
 struct patchCollide_s const* debugPatchCollide ; 
 int qfalse ; 
 int qtrue ; 

void CM_TracePointThroughPatchCollide( traceWork_t *tw, const struct patchCollide_s *pc ) {
	qboolean	frontFacing[MAX_PATCH_PLANES];
	float		intersection[MAX_PATCH_PLANES];
	float		intersect;
	const patchPlane_t	*planes;
	const facet_t	*facet;
	int			i, j, k;
	float		offset;
	float		d1, d2;
#ifndef BSPC
	static cvar_t *cv;
#endif //BSPC

#ifndef BSPC
	if ( !cm_playerCurveClip->integer || !tw->isPoint ) {
		return;
	}
#endif

	// determine the trace's relationship to all planes
	planes = pc->planes;
	for ( i = 0 ; i < pc->numPlanes ; i++, planes++ ) {
		offset = DotProduct( tw->offsets[ planes->signbits ], planes->plane );
		d1 = DotProduct( tw->start, planes->plane ) - planes->plane[3] + offset;
		d2 = DotProduct( tw->end, planes->plane ) - planes->plane[3] + offset;
		if ( d1 <= 0 ) {
			frontFacing[i] = qfalse;
		} else {
			frontFacing[i] = qtrue;
		}
		if ( d1 == d2 ) {
			intersection[i] = 99999;
		} else {
			intersection[i] = d1 / ( d1 - d2 );
			if ( intersection[i] <= 0 ) {
				intersection[i] = 99999;
			}
		}
	}


	// see if any of the surface planes are intersected
	facet = pc->facets;
	for ( i = 0 ; i < pc->numFacets ; i++, facet++ ) {
		if ( !frontFacing[facet->surfacePlane] ) {
			continue;
		}
		intersect = intersection[facet->surfacePlane];
		if ( intersect < 0 ) {
			continue;		// surface is behind the starting point
		}
		if ( intersect > tw->trace.fraction ) {
			continue;		// already hit something closer
		}
		for ( j = 0 ; j < facet->numBorders ; j++ ) {
			k = facet->borderPlanes[j];
			if ( frontFacing[k] ^ facet->borderInward[j] ) {
				if ( intersection[k] > intersect ) {
					break;
				}
			} else {
				if ( intersection[k] < intersect ) {
					break;
				}
			}
		}
		if ( j == facet->numBorders ) {
			// we hit this facet
#ifndef BSPC
			if (!cv) {
				cv = Cvar_Get( "r_debugSurfaceUpdate", "1", 0 );
			}
			if (cv->integer) {
				debugPatchCollide = pc;
				debugFacet = facet;
			}
#endif //BSPC
			planes = &pc->planes[facet->surfacePlane];

			// calculate intersection with a slight pushoff
			offset = DotProduct( tw->offsets[ planes->signbits ], planes->plane );
			d1 = DotProduct( tw->start, planes->plane ) - planes->plane[3] + offset;
			d2 = DotProduct( tw->end, planes->plane ) - planes->plane[3] + offset;
			tw->trace.fraction = ( d1 - SURFACE_CLIP_EPSILON ) / ( d1 - d2 );

			if ( tw->trace.fraction < 0 ) {
				tw->trace.fraction = 0;
			}

			VectorCopy( planes->plane,  tw->trace.plane.normal );
			tw->trace.plane.dist = planes->plane[3];
		}
	}
}