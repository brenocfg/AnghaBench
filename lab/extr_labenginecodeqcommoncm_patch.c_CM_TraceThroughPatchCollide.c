#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  float* vec3_t ;
struct TYPE_12__ {float* normal; float dist; } ;
struct TYPE_13__ {float fraction; TYPE_1__ plane; } ;
struct TYPE_14__ {float* offset; scalar_t__ radius; scalar_t__ use; } ;
struct TYPE_15__ {float* start; float* end; float** offsets; TYPE_2__ trace; TYPE_3__ sphere; scalar_t__ isPoint; int /*<<< orphan*/ * bounds; } ;
typedef  TYPE_4__ traceWork_t ;
struct patchCollide_s {int numFacets; TYPE_5__* planes; TYPE_6__* facets; int /*<<< orphan*/ * bounds; } ;
struct TYPE_16__ {float* plane; size_t signbits; } ;
typedef  TYPE_5__ patchPlane_t ;
struct TYPE_17__ {size_t surfacePlane; int numBorders; size_t* borderPlanes; scalar_t__* borderInward; } ;
typedef  TYPE_6__ facet_t ;
struct TYPE_18__ {scalar_t__ integer; } ;
typedef  TYPE_7__ cvar_t ;

/* Variables and functions */
 int /*<<< orphan*/  CM_BoundsIntersect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CM_CheckFacetPlane (float*,float*,float*,float*,float*,int*) ; 
 int /*<<< orphan*/  CM_TracePointThroughPatchCollide (TYPE_4__*,struct patchCollide_s const*) ; 
 TYPE_7__* Cvar_Get (char*,char*,int /*<<< orphan*/ ) ; 
 float DotProduct (float*,float*) ; 
 int /*<<< orphan*/  Vector4Copy (float*,float*) ; 
 int /*<<< orphan*/  VectorAdd (float*,float*,float*) ; 
 int /*<<< orphan*/  VectorCopy (float*,float*) ; 
 int /*<<< orphan*/  VectorNegate (float*,float*) ; 
 int /*<<< orphan*/  VectorSubtract (float*,float*,float*) ; 
 TYPE_6__* debugFacet ; 
 struct patchCollide_s const* debugPatchCollide ; 
 scalar_t__ fabs (float) ; 

void CM_TraceThroughPatchCollide( traceWork_t *tw, const struct patchCollide_s *pc ) {
	int i, j, hit, hitnum;
	float offset, enterFrac, leaveFrac, t;
	patchPlane_t *planes;
	facet_t	*facet;
	float plane[4] = {0, 0, 0, 0}, bestplane[4] = {0, 0, 0, 0};
	vec3_t startp, endp;
#ifndef BSPC
	static cvar_t *cv;
#endif //BSPC

	if ( !CM_BoundsIntersect( tw->bounds[0], tw->bounds[1],
				pc->bounds[0], pc->bounds[1] ) ) {
		return;
	}

	if (tw->isPoint) {
		CM_TracePointThroughPatchCollide( tw, pc );
		return;
	}

	facet = pc->facets;
	for ( i = 0 ; i < pc->numFacets ; i++, facet++ ) {
		enterFrac = -1.0;
		leaveFrac = 1.0;
		hitnum = -1;
		//
		planes = &pc->planes[ facet->surfacePlane ];
		VectorCopy(planes->plane, plane);
		plane[3] = planes->plane[3];
		if ( tw->sphere.use ) {
			// adjust the plane distance appropriately for radius
			plane[3] += tw->sphere.radius;

			// find the closest point on the capsule to the plane
			t = DotProduct( plane, tw->sphere.offset );
			if ( t > 0.0f ) {
				VectorSubtract( tw->start, tw->sphere.offset, startp );
				VectorSubtract( tw->end, tw->sphere.offset, endp );
			}
			else {
				VectorAdd( tw->start, tw->sphere.offset, startp );
				VectorAdd( tw->end, tw->sphere.offset, endp );
			}
		}
		else {
			offset = DotProduct( tw->offsets[ planes->signbits ], plane);
			plane[3] -= offset;
			VectorCopy( tw->start, startp );
			VectorCopy( tw->end, endp );
		}

		if (!CM_CheckFacetPlane(plane, startp, endp, &enterFrac, &leaveFrac, &hit)) {
			continue;
		}
		if (hit) {
			Vector4Copy(plane, bestplane);
		}

		for ( j = 0; j < facet->numBorders; j++ ) {
			planes = &pc->planes[ facet->borderPlanes[j] ];
			if (facet->borderInward[j]) {
				VectorNegate(planes->plane, plane);
				plane[3] = -planes->plane[3];
			}
			else {
				VectorCopy(planes->plane, plane);
				plane[3] = planes->plane[3];
			}
			if ( tw->sphere.use ) {
				// adjust the plane distance appropriately for radius
				plane[3] += tw->sphere.radius;

				// find the closest point on the capsule to the plane
				t = DotProduct( plane, tw->sphere.offset );
				if ( t > 0.0f ) {
					VectorSubtract( tw->start, tw->sphere.offset, startp );
					VectorSubtract( tw->end, tw->sphere.offset, endp );
				}
				else {
					VectorAdd( tw->start, tw->sphere.offset, startp );
					VectorAdd( tw->end, tw->sphere.offset, endp );
				}
			}
			else {
				// NOTE: this works even though the plane might be flipped because the bbox is centered
				offset = DotProduct( tw->offsets[ planes->signbits ], plane);
				plane[3] += fabs(offset);
				VectorCopy( tw->start, startp );
				VectorCopy( tw->end, endp );
			}

			if (!CM_CheckFacetPlane(plane, startp, endp, &enterFrac, &leaveFrac, &hit)) {
				break;
			}
			if (hit) {
				hitnum = j;
				Vector4Copy(plane, bestplane);
			}
		}
		if (j < facet->numBorders) continue;
		//never clip against the back side
		if (hitnum == facet->numBorders - 1) continue;

		if (enterFrac < leaveFrac && enterFrac >= 0) {
			if (enterFrac < tw->trace.fraction) {
				if (enterFrac < 0) {
					enterFrac = 0;
				}
#ifndef BSPC
				if (!cv) {
					cv = Cvar_Get( "r_debugSurfaceUpdate", "1", 0 );
				}
				if (cv && cv->integer) {
					debugPatchCollide = pc;
					debugFacet = facet;
				}
#endif //BSPC

				tw->trace.fraction = enterFrac;
				VectorCopy( bestplane, tw->trace.plane.normal );
				tw->trace.plane.dist = bestplane[3];
			}
		}
	}
}