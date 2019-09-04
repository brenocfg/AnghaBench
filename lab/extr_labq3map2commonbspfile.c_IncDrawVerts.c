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
typedef  int /*<<< orphan*/  drawVert_t ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 int MAX_MAP_DRAW_VERTS ; 
 scalar_t__ drawVerts ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int numDrawVerts ; 
 int numDrawVertsBuffer ; 
 scalar_t__ realloc (scalar_t__,int) ; 
 scalar_t__ safe_malloc_info (int,char*) ; 

void IncDrawVerts(){
	numDrawVerts++;

	if ( drawVerts == 0 ) {
		numDrawVertsBuffer = MAX_MAP_DRAW_VERTS / 37;

		drawVerts = safe_malloc_info( sizeof( drawVert_t ) * numDrawVertsBuffer, "IncDrawVerts" );

	}
	else if ( numDrawVerts > numDrawVertsBuffer ) {
		numDrawVertsBuffer *= 3; // multiply by 1.5
		numDrawVertsBuffer /= 2;

		if ( numDrawVertsBuffer > MAX_MAP_DRAW_VERTS ) {
			numDrawVertsBuffer = MAX_MAP_DRAW_VERTS;
		}

		drawVerts = realloc( drawVerts, sizeof( drawVert_t ) * numDrawVertsBuffer );

		if ( !drawVerts ) {
			Error( "realloc() failed (IncDrawVerts)" );
		}
	}

	memset( drawVerts + ( numDrawVerts - 1 ), 0, sizeof( drawVert_t ) );
}