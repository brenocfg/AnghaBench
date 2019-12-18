#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {float dist; int /*<<< orphan*/  normal; } ;
struct TYPE_11__ {int dlightBits; TYPE_2__ plane; } ;
typedef  TYPE_4__ srfSurfaceFace_t ;
struct TYPE_12__ {float radius; int /*<<< orphan*/  origin; } ;
typedef  TYPE_5__ dlight_t ;
struct TYPE_10__ {int /*<<< orphan*/  c_dlightSurfacesCulled; } ;
struct TYPE_8__ {int num_dlights; TYPE_5__* dlights; } ;
struct TYPE_13__ {TYPE_3__ pc; TYPE_1__ refdef; } ;

/* Variables and functions */
 float DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__ tr ; 

__attribute__((used)) static int R_DlightFace( srfSurfaceFace_t *face, int dlightBits ) {
	float		d;
	int			i;
	dlight_t	*dl;

	for ( i = 0 ; i < tr.refdef.num_dlights ; i++ ) {
		if ( ! ( dlightBits & ( 1 << i ) ) ) {
			continue;
		}
		dl = &tr.refdef.dlights[i];
		d = DotProduct( dl->origin, face->plane.normal ) - face->plane.dist;
		if ( d < -dl->radius || d > dl->radius ) {
			// dlight doesn't reach the plane
			dlightBits &= ~( 1 << i );
		}
	}

	if ( !dlightBits ) {
		tr.pc.c_dlightSurfacesCulled++;
	}

	face->dlightBits = dlightBits;
	return dlightBits;
}