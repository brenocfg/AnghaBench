#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int numVerts; TYPE_1__* verts; } ;
typedef  TYPE_2__ srfPoly_t ;
struct TYPE_7__ {int numVertexes; int** color; int* indexes; int numIndexes; int /*<<< orphan*/ ** texCoords; int /*<<< orphan*/ * xyz; int /*<<< orphan*/  vao; } ;
struct TYPE_5__ {scalar_t__* modulate; int /*<<< orphan*/ * st; int /*<<< orphan*/  xyz; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_CHECKOVERFLOW (int,int) ; 
 int /*<<< orphan*/  RB_CheckVao (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ tess ; 

__attribute__((used)) static void RB_SurfacePolychain( srfPoly_t *p ) {
	int		i;
	int		numv;

	RB_CheckVao(tess.vao);

	RB_CHECKOVERFLOW( p->numVerts, 3*(p->numVerts - 2) );

	// fan triangles into the tess array
	numv = tess.numVertexes;
	for ( i = 0; i < p->numVerts; i++ ) {
		VectorCopy( p->verts[i].xyz, tess.xyz[numv] );
		tess.texCoords[numv][0] = p->verts[i].st[0];
		tess.texCoords[numv][1] = p->verts[i].st[1];
		tess.color[numv][0] = (int)p->verts[i].modulate[0] * 257;
		tess.color[numv][1] = (int)p->verts[i].modulate[1] * 257;
		tess.color[numv][2] = (int)p->verts[i].modulate[2] * 257;
		tess.color[numv][3] = (int)p->verts[i].modulate[3] * 257;

		numv++;
	}

	// generate fan indexes into the tess array
	for ( i = 0; i < p->numVerts-2; i++ ) {
		tess.indexes[tess.numIndexes + 0] = tess.numVertexes;
		tess.indexes[tess.numIndexes + 1] = tess.numVertexes + i + 1;
		tess.indexes[tess.numIndexes + 2] = tess.numVertexes + i + 2;
		tess.numIndexes += 3;
	}

	tess.numVertexes = numv;
}