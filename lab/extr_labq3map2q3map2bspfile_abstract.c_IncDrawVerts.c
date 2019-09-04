#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  bspDrawVert_t ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 int MAX_MAP_DRAW_VERTS ; 
 int /*<<< orphan*/ * bspDrawVerts ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int numBSPDrawVerts ; 
 int numBSPDrawVertsBuffer ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * safe_malloc_info (int,char*) ; 

void IncDrawVerts(){
	numBSPDrawVerts++;

	if ( bspDrawVerts == 0 ) {
		numBSPDrawVertsBuffer = MAX_MAP_DRAW_VERTS / 37;

		bspDrawVerts = safe_malloc_info( sizeof( bspDrawVert_t ) * numBSPDrawVertsBuffer, "IncDrawVerts" );

	}
	else if ( numBSPDrawVerts > numBSPDrawVertsBuffer ) {
		bspDrawVert_t *newBspDrawVerts;

		numBSPDrawVertsBuffer *= 3; // multiply by 1.5
		numBSPDrawVertsBuffer /= 2;

		if ( numBSPDrawVertsBuffer > MAX_MAP_DRAW_VERTS ) {
			numBSPDrawVertsBuffer = MAX_MAP_DRAW_VERTS;
		}

		newBspDrawVerts = realloc( bspDrawVerts, sizeof( bspDrawVert_t ) * numBSPDrawVertsBuffer );

		if ( !newBspDrawVerts ) {
			free (bspDrawVerts);
			Error( "realloc() failed (IncDrawVerts)" );
		}

		bspDrawVerts = newBspDrawVerts;
	}

	memset( bspDrawVerts + ( numBSPDrawVerts - 1 ), 0, sizeof( bspDrawVert_t ) );
}