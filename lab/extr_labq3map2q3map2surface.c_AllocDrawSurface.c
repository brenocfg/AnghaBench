#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ surfaceType_t ;
struct TYPE_5__ {int planeNum; int outputNum; size_t surfaceNum; int /*<<< orphan*/  fogNum; scalar_t__ type; } ;
typedef  TYPE_1__ mapDrawSurface_t ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*,size_t) ; 
 size_t MAX_MAP_DRAW_SURFS ; 
 scalar_t__ NUM_SURFACE_TYPES ; 
 scalar_t__ SURFACE_BAD ; 
 int /*<<< orphan*/  defaultFogNum ; 
 TYPE_1__* mapDrawSurfs ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 size_t numMapDrawSurfs ; 

mapDrawSurface_t *AllocDrawSurface( surfaceType_t type ){
	mapDrawSurface_t    *ds;


	/* ydnar: gs mods: only allocate valid types */
	if ( type <= SURFACE_BAD || type >= NUM_SURFACE_TYPES ) {
		Error( "AllocDrawSurface: Invalid surface type %d specified", type );
	}

	/* bounds check */
	if ( numMapDrawSurfs >= MAX_MAP_DRAW_SURFS ) {
		Error( "MAX_MAP_DRAW_SURFS (%d) exceeded", MAX_MAP_DRAW_SURFS );
	}
	ds = &mapDrawSurfs[ numMapDrawSurfs ];
	numMapDrawSurfs++;

	/* ydnar: do initial surface setup */
	memset( ds, 0, sizeof( mapDrawSurface_t ) );
	ds->type = type;
	ds->planeNum = -1;
	ds->fogNum = defaultFogNum;             /* ydnar 2003-02-12 */
	ds->outputNum = -1;                     /* ydnar 2002-08-13 */
	ds->surfaceNum = numMapDrawSurfs - 1;   /* ydnar 2003-02-16 */

	return ds;
}