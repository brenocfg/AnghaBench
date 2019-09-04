#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int numVerts; int numIndexes; TYPE_4__* st; scalar_t__* indexes; } ;
typedef  TYPE_3__ mdvSurface_t ;
struct TYPE_12__ {int /*<<< orphan*/ * st; } ;
typedef  TYPE_4__ mdvSt_t ;
struct TYPE_14__ {TYPE_2__* currentEntity; } ;
struct TYPE_13__ {int numIndexes; int numVertexes; int /*<<< orphan*/ ** texCoords; scalar_t__* indexes; int /*<<< orphan*/  vao; } ;
struct TYPE_9__ {scalar_t__ oldframe; scalar_t__ frame; float backlerp; } ;
struct TYPE_10__ {TYPE_1__ e; } ;

/* Variables and functions */
 int /*<<< orphan*/  LerpMeshVertexes (TYPE_3__*,float) ; 
 int /*<<< orphan*/  RB_CHECKOVERFLOW (int,int) ; 
 int /*<<< orphan*/  RB_CheckVao (int /*<<< orphan*/ ) ; 
 TYPE_6__ backEnd ; 
 TYPE_5__ tess ; 

__attribute__((used)) static void RB_SurfaceMesh(mdvSurface_t *surface) {
	int				j;
	float			backlerp;
	mdvSt_t			*texCoords;
	int				Bob, Doug;
	int				numVerts;

	if (  backEnd.currentEntity->e.oldframe == backEnd.currentEntity->e.frame ) {
		backlerp = 0;
	} else  {
		backlerp = backEnd.currentEntity->e.backlerp;
	}

	RB_CheckVao(tess.vao);

	RB_CHECKOVERFLOW( surface->numVerts, surface->numIndexes );

	LerpMeshVertexes (surface, backlerp);

	Bob = tess.numIndexes;
	Doug = tess.numVertexes;
	for (j = 0 ; j < surface->numIndexes ; j++) {
		tess.indexes[Bob + j] = Doug + surface->indexes[j];
	}
	tess.numIndexes += surface->numIndexes;

	texCoords = surface->st;

	numVerts = surface->numVerts;
	for ( j = 0; j < numVerts; j++ ) {
		tess.texCoords[Doug + j][0] = texCoords[j].st[0];
		tess.texCoords[Doug + j][1] = texCoords[j].st[1];
		// FIXME: fill in lightmapST for completeness?
	}

	tess.numVertexes += surface->numVerts;

}