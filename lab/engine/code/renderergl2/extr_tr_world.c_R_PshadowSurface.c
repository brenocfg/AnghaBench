#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int pshadowBits; } ;
typedef  TYPE_4__ srfBspSurface_t ;
struct TYPE_17__ {float dist; int /*<<< orphan*/  normal; } ;
struct TYPE_14__ {float* lightOrigin; float lightRadius; TYPE_9__ cullPlane; int /*<<< orphan*/  viewRadius; int /*<<< orphan*/  viewOrigin; } ;
typedef  TYPE_5__ pshadow_t ;
struct TYPE_10__ {float dist; int /*<<< orphan*/  normal; } ;
struct TYPE_12__ {int type; float** bounds; float* localOrigin; float radius; TYPE_1__ plane; } ;
struct TYPE_15__ {int* data; TYPE_3__ cullinfo; } ;
typedef  TYPE_6__ msurface_t ;
struct TYPE_11__ {int num_pshadows; TYPE_5__* pshadows; } ;
struct TYPE_16__ {TYPE_2__ refdef; } ;

/* Variables and functions */
 int BoxOnPlaneSide (float*,float*,TYPE_9__*) ; 
 int CULLINFO_BOX ; 
 int CULLINFO_PLANE ; 
 int CULLINFO_SPHERE ; 
 float DotProduct (float*,int /*<<< orphan*/ ) ; 
#define  SF_FACE 130 
#define  SF_GRID 129 
#define  SF_TRIANGLES 128 
 int /*<<< orphan*/  SpheresIntersect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*,float) ; 
 TYPE_7__ tr ; 

__attribute__((used)) static int R_PshadowSurface( msurface_t *surf, int pshadowBits ) {
	float       d;
	int         i;
	pshadow_t    *ps;
	
	if ( surf->cullinfo.type & CULLINFO_PLANE )
	{
		for ( i = 0 ; i < tr.refdef.num_pshadows ; i++ ) {
			if ( ! ( pshadowBits & ( 1 << i ) ) ) {
				continue;
			}
			ps = &tr.refdef.pshadows[i];
			d = DotProduct( ps->lightOrigin, surf->cullinfo.plane.normal ) - surf->cullinfo.plane.dist;
			if ( d < -ps->lightRadius || d > ps->lightRadius ) {
				// pshadow doesn't reach the plane
				pshadowBits &= ~( 1 << i );
			}
		}
	}
	
	if ( surf->cullinfo.type & CULLINFO_BOX )
	{
		for ( i = 0 ; i < tr.refdef.num_pshadows ; i++ ) {
			if ( ! ( pshadowBits & ( 1 << i ) ) ) {
				continue;
			}
			ps = &tr.refdef.pshadows[i];
			if ( ps->lightOrigin[0] - ps->lightRadius > surf->cullinfo.bounds[1][0]
				|| ps->lightOrigin[0] + ps->lightRadius < surf->cullinfo.bounds[0][0]
				|| ps->lightOrigin[1] - ps->lightRadius > surf->cullinfo.bounds[1][1]
				|| ps->lightOrigin[1] + ps->lightRadius < surf->cullinfo.bounds[0][1]
				|| ps->lightOrigin[2] - ps->lightRadius > surf->cullinfo.bounds[1][2]
				|| ps->lightOrigin[2] + ps->lightRadius < surf->cullinfo.bounds[0][2] 
				|| BoxOnPlaneSide(surf->cullinfo.bounds[0], surf->cullinfo.bounds[1], &ps->cullPlane) == 2 ) {
				// pshadow doesn't reach the bounds
				pshadowBits &= ~( 1 << i );
			}
		}
	}

	if ( surf->cullinfo.type & CULLINFO_SPHERE )
	{
		for ( i = 0 ; i < tr.refdef.num_pshadows ; i++ ) {
			if ( ! ( pshadowBits & ( 1 << i ) ) ) {
				continue;
			}
			ps = &tr.refdef.pshadows[i];
			if (!SpheresIntersect(ps->viewOrigin, ps->viewRadius, surf->cullinfo.localOrigin, surf->cullinfo.radius)
				|| DotProduct( surf->cullinfo.localOrigin, ps->cullPlane.normal ) - ps->cullPlane.dist < -surf->cullinfo.radius)
			{
				// pshadow doesn't reach the bounds
				pshadowBits &= ~( 1 << i );
			}
		}
	}

	switch(*surf->data)
	{
		case SF_FACE:
		case SF_GRID:
		case SF_TRIANGLES:
			((srfBspSurface_t *)surf->data)->pshadowBits = pshadowBits;
			break;

		default:
			pshadowBits = 0;
			break;
	}

	if ( pshadowBits ) {
		//tr.pc.c_dlightSurfaces++;
	}

	return pshadowBits;
}