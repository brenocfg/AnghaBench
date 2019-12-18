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

/* Variables and functions */
 int* bspDrawIndexes ; 
 scalar_t__ numBSPBrushSides ; 
 int numBSPDrawIndexes ; 
 scalar_t__ numBSPLeafBrushes ; 
 scalar_t__ numBSPLeafSurfaces ; 
 int numBSPLeafs ; 
 scalar_t__ numBSPModels ; 
 scalar_t__ numBSPNodes ; 

void BeginBSPFile( void ){
	/* these values may actually be initialized if the file existed when loaded, so clear them explicitly */
	numBSPModels = 0;
	numBSPNodes = 0;
	numBSPBrushSides = 0;
	numBSPLeafSurfaces = 0;
	numBSPLeafBrushes = 0;

	/* leave leaf 0 as an error, because leafs are referenced as negative number nodes */
	numBSPLeafs = 1;


	/* ydnar: gs mods: set the first 6 drawindexes to 0 1 2 2 1 3 for triangles and quads */
	numBSPDrawIndexes = 6;
	bspDrawIndexes[ 0 ] = 0;
	bspDrawIndexes[ 1 ] = 1;
	bspDrawIndexes[ 2 ] = 2;
	bspDrawIndexes[ 3 ] = 0;
	bspDrawIndexes[ 4 ] = 2;
	bspDrawIndexes[ 5 ] = 3;
}