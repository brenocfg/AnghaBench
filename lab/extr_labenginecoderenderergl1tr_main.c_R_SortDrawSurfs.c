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
struct TYPE_10__ {scalar_t__ sort; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ shader_t ;
struct TYPE_11__ {int /*<<< orphan*/  sort; } ;
typedef  TYPE_2__ drawSurf_t ;
struct TYPE_13__ {scalar_t__ integer; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* Error ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_DROP ; 
 int /*<<< orphan*/  R_AddDrawSurfCmd (TYPE_2__*,int) ; 
 int /*<<< orphan*/  R_DecomposeSort (int /*<<< orphan*/ ,int*,TYPE_1__**,int*,int*) ; 
 scalar_t__ R_MirrorViewBySurface (TYPE_2__*,int) ; 
 int /*<<< orphan*/  R_RadixSort (TYPE_2__*,int) ; 
 scalar_t__ SS_BAD ; 
 scalar_t__ SS_PORTAL ; 
 TYPE_4__* r_portalOnly ; 
 TYPE_3__ ri ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void R_SortDrawSurfs( drawSurf_t *drawSurfs, int numDrawSurfs ) {
	shader_t		*shader;
	int				fogNum;
	int				entityNum;
	int				dlighted;
	int				i;

	// it is possible for some views to not have any surfaces
	if ( numDrawSurfs < 1 ) {
		// we still need to add it for hyperspace cases
		R_AddDrawSurfCmd( drawSurfs, numDrawSurfs );
		return;
	}

	// sort the drawsurfs by sort type, then orientation, then shader
	R_RadixSort( drawSurfs, numDrawSurfs );

	// check for any pass through drawing, which
	// may cause another view to be rendered first
	for ( i = 0 ; i < numDrawSurfs ; i++ ) {
		R_DecomposeSort( (drawSurfs+i)->sort, &entityNum, &shader, &fogNum, &dlighted );

		if ( shader->sort > SS_PORTAL ) {
			break;
		}

		// no shader should ever have this sort type
		if ( shader->sort == SS_BAD ) {
			ri.Error (ERR_DROP, "Shader '%s'with sort == SS_BAD", shader->name );
		}

		// if the mirror was completely clipped away, we may need to check another surface
		if ( R_MirrorViewBySurface( (drawSurfs+i), entityNum) ) {
			// this is a debug option to see exactly what is being mirrored
			if ( r_portalOnly->integer ) {
				return;
			}
			break;		// only one mirror view at a time
		}
	}

	R_AddDrawSurfCmd( drawSurfs, numDrawSurfs );
}