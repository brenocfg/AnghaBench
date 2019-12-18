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
struct TYPE_8__ {scalar_t__ type; scalar_t__ numVerts; } ;
typedef  TYPE_1__ mapDrawSurface_t ;
struct TYPE_9__ {int firstDrawSurf; } ;
typedef  TYPE_2__ entity_t ;

/* Variables and functions */
 int /*<<< orphan*/  ClearSurface (TYPE_1__*) ; 
 scalar_t__ SURFACE_BAD ; 
 scalar_t__ SURFACE_FLARE ; 
 scalar_t__ SURFACE_SHADER ; 
 int /*<<< orphan*/  SYS_VRB ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__* mapDrawSurfs ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 int numMapDrawSurfs ; 

void TidyEntitySurfaces( entity_t *e ){
	int i, j, deleted;
	mapDrawSurface_t    *out, *in;


	/* note it */
	Sys_FPrintf( SYS_VRB, "--- TidyEntitySurfaces ---\n" );

	/* walk the surface list */
	deleted = 0;
	for ( i = e->firstDrawSurf, j = e->firstDrawSurf; j < numMapDrawSurfs; i++, j++ )
	{
		/* get out surface */
		out = &mapDrawSurfs[ i ];

		/* walk the surface list again until a proper surface is found */
		for ( ; j < numMapDrawSurfs; j++ )
		{
			/* get in surface */
			in = &mapDrawSurfs[ j ];

			/* this surface ok? */
			if ( in->type == SURFACE_FLARE || in->type == SURFACE_SHADER ||
				 ( in->type != SURFACE_BAD && in->numVerts > 0 ) ) {
				break;
			}

			/* nuke it */
			ClearSurface( in );
			deleted++;
		}

		/* copy if necessary */
		if ( i != j ) {
			memcpy( out, in, sizeof( mapDrawSurface_t ) );
		}
	}

	/* set the new number of drawsurfs */
	numMapDrawSurfs = i;

	/* emit some stats */
	Sys_FPrintf( SYS_VRB, "%9d empty or malformed surfaces deleted\n", deleted );
}