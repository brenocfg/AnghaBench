#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__* drawSurfReferences; scalar_t__ opaque; TYPE_5__* brushlist; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; int /*<<< orphan*/  area; int /*<<< orphan*/  cluster; } ;
typedef  TYPE_2__ node_t ;
struct TYPE_11__ {int /*<<< orphan*/  outputNum; struct TYPE_11__* nextRef; } ;
typedef  TYPE_3__ drawSurfRef_t ;
struct TYPE_12__ {size_t firstBSPLeafBrush; size_t numBSPLeafBrushes; size_t firstBSPLeafSurface; size_t numBSPLeafSurfaces; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; int /*<<< orphan*/  area; int /*<<< orphan*/  cluster; } ;
typedef  TYPE_4__ bspLeaf_t ;
struct TYPE_13__ {TYPE_1__* original; struct TYPE_13__* next; } ;
typedef  TYPE_5__ brush_t ;
struct TYPE_9__ {int /*<<< orphan*/  outputNum; } ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 size_t MAX_MAP_LEAFBRUSHES ; 
 size_t MAX_MAP_LEAFFACES ; 
 size_t MAX_MAP_LEAFS ; 
 int /*<<< orphan*/  SYS_WRN ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*,TYPE_5__*) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bspLeafBrushes ; 
 int /*<<< orphan*/ * bspLeafSurfaces ; 
 TYPE_4__* bspLeafs ; 
 size_t numBSPLeafBrushes ; 
 size_t numBSPLeafSurfaces ; 
 size_t numBSPLeafs ; 

void EmitLeaf( node_t *node ){
	bspLeaf_t       *leaf_p;
	brush_t         *b;
	drawSurfRef_t   *dsr;


	/* check limits */
	if ( numBSPLeafs >= MAX_MAP_LEAFS ) {
		Error( "MAX_MAP_LEAFS" );
	}

	leaf_p = &bspLeafs[numBSPLeafs];
	numBSPLeafs++;

	leaf_p->cluster = node->cluster;
	leaf_p->area = node->area;

	/* emit bounding box */
	VectorCopy( node->mins, leaf_p->mins );
	VectorCopy( node->maxs, leaf_p->maxs );

	/* emit leaf brushes */
	leaf_p->firstBSPLeafBrush = numBSPLeafBrushes;
	for ( b = node->brushlist; b; b = b->next )
	{
		/* something is corrupting brushes */
		if ( (size_t) b < 256 ) {
			Sys_FPrintf( SYS_WRN, "WARNING: Node brush list corrupted (0x%08X)\n", b );
			break;
		}
		//%	if( b->guard != 0xDEADBEEF )
		//%		Sys_Printf( "Brush %6d: 0x%08X Guard: 0x%08X Next: 0x%08X Original: 0x%08X Sides: %d\n", b->brushNum, b, b, b->next, b->original, b->numsides );

		if ( numBSPLeafBrushes >= MAX_MAP_LEAFBRUSHES ) {
			Error( "MAX_MAP_LEAFBRUSHES" );
		}
		bspLeafBrushes[ numBSPLeafBrushes ] = b->original->outputNum;
		numBSPLeafBrushes++;
	}

	leaf_p->numBSPLeafBrushes = numBSPLeafBrushes - leaf_p->firstBSPLeafBrush;

	/* emit leaf surfaces */
	if ( node->opaque ) {
		return;
	}

	/* add the drawSurfRef_t drawsurfs */
	leaf_p->firstBSPLeafSurface = numBSPLeafSurfaces;
	for ( dsr = node->drawSurfReferences; dsr; dsr = dsr->nextRef )
	{
		if ( numBSPLeafSurfaces >= MAX_MAP_LEAFFACES ) {
			Error( "MAX_MAP_LEAFFACES" );
		}
		bspLeafSurfaces[ numBSPLeafSurfaces ] = dsr->outputNum;
		numBSPLeafSurfaces++;
	}

	leaf_p->numBSPLeafSurfaces = numBSPLeafSurfaces - leaf_p->firstBSPLeafSurface;
}