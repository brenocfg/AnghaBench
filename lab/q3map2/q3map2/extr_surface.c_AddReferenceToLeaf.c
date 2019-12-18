#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ planenum; void* sky; scalar_t__ skybox; TYPE_4__* drawSurfReferences; scalar_t__ opaque; } ;
typedef  TYPE_2__ node_t ;
struct TYPE_10__ {TYPE_1__* shaderInfo; void* skybox; } ;
typedef  TYPE_3__ mapDrawSurface_t ;
struct TYPE_11__ {scalar_t__ outputNum; struct TYPE_11__* nextRef; } ;
typedef  TYPE_4__ drawSurfRef_t ;
struct TYPE_8__ {int compileFlags; } ;

/* Variables and functions */
 int C_SKY ; 
 scalar_t__ PLANENUM_LEAF ; 
 scalar_t__ numBSPDrawSurfaces ; 
 void* qtrue ; 
 TYPE_4__* safe_malloc (int) ; 

int AddReferenceToLeaf( mapDrawSurface_t *ds, node_t *node ){
	drawSurfRef_t   *dsr;


	/* dummy check */
	if ( node->planenum != PLANENUM_LEAF || node->opaque ) {
		return 0;
	}

	/* try to find an existing reference */
	for ( dsr = node->drawSurfReferences; dsr; dsr = dsr->nextRef )
	{
		if ( dsr->outputNum == numBSPDrawSurfaces ) {
			return 0;
		}
	}

	/* add a new reference */
	dsr = safe_malloc( sizeof( *dsr ) );
	dsr->outputNum = numBSPDrawSurfaces;
	dsr->nextRef = node->drawSurfReferences;
	node->drawSurfReferences = dsr;

	/* ydnar: sky/skybox surfaces */
	if ( node->skybox ) {
		ds->skybox = qtrue;
	}
	if ( ds->shaderInfo->compileFlags & C_SKY ) {
		node->sky = qtrue;
	}

	/* return */
	return 1;
}