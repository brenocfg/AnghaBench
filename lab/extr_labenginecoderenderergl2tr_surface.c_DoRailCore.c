#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_8__ {TYPE_2__* currentEntity; } ;
struct TYPE_7__ {int numVertexes; int** texCoords; float** color; int* indexes; int /*<<< orphan*/  numIndexes; int /*<<< orphan*/ * xyz; int /*<<< orphan*/  vao; } ;
struct TYPE_5__ {float* shaderRGBA; } ;
struct TYPE_6__ {TYPE_1__ e; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_CHECKOVERFLOW (int,int) ; 
 int /*<<< orphan*/  RB_CheckVao (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/  const,float,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 TYPE_4__ backEnd ; 
 TYPE_3__ tess ; 

__attribute__((used)) static void DoRailCore( const vec3_t start, const vec3_t end, const vec3_t up, float len, float spanWidth )
{
	float		spanWidth2;
	int			vbase;
	float		t = len / 256.0f;

	RB_CheckVao(tess.vao);

	RB_CHECKOVERFLOW( 4, 6 );

	vbase = tess.numVertexes;

	spanWidth2 = -spanWidth;

	// FIXME: use quad stamp?
	VectorMA( start, spanWidth, up, tess.xyz[tess.numVertexes] );
	tess.texCoords[tess.numVertexes][0] = 0;
	tess.texCoords[tess.numVertexes][1] = 0;
	tess.color[tess.numVertexes][0] = backEnd.currentEntity->e.shaderRGBA[0] * 0.25f * 257.0f;
	tess.color[tess.numVertexes][1] = backEnd.currentEntity->e.shaderRGBA[1] * 0.25f * 257.0f;
	tess.color[tess.numVertexes][2] = backEnd.currentEntity->e.shaderRGBA[2] * 0.25f * 257.0f;
	tess.numVertexes++;

	VectorMA( start, spanWidth2, up, tess.xyz[tess.numVertexes] );
	tess.texCoords[tess.numVertexes][0] = 0;
	tess.texCoords[tess.numVertexes][1] = 1;
	tess.color[tess.numVertexes][0] = backEnd.currentEntity->e.shaderRGBA[0] * 257;
	tess.color[tess.numVertexes][1] = backEnd.currentEntity->e.shaderRGBA[1] * 257;
	tess.color[tess.numVertexes][2] = backEnd.currentEntity->e.shaderRGBA[2] * 257;
	tess.numVertexes++;

	VectorMA( end, spanWidth, up, tess.xyz[tess.numVertexes] );

	tess.texCoords[tess.numVertexes][0] = t;
	tess.texCoords[tess.numVertexes][1] = 0;
	tess.color[tess.numVertexes][0] = backEnd.currentEntity->e.shaderRGBA[0] * 257;
	tess.color[tess.numVertexes][1] = backEnd.currentEntity->e.shaderRGBA[1] * 257;
	tess.color[tess.numVertexes][2] = backEnd.currentEntity->e.shaderRGBA[2] * 257;
	tess.numVertexes++;

	VectorMA( end, spanWidth2, up, tess.xyz[tess.numVertexes] );
	tess.texCoords[tess.numVertexes][0] = t;
	tess.texCoords[tess.numVertexes][1] = 1;
	tess.color[tess.numVertexes][0] = backEnd.currentEntity->e.shaderRGBA[0] * 257;
	tess.color[tess.numVertexes][1] = backEnd.currentEntity->e.shaderRGBA[1] * 257;
	tess.color[tess.numVertexes][2] = backEnd.currentEntity->e.shaderRGBA[2] * 257;
	tess.numVertexes++;

	tess.indexes[tess.numIndexes++] = vbase;
	tess.indexes[tess.numIndexes++] = vbase + 1;
	tess.indexes[tess.numIndexes++] = vbase + 2;

	tess.indexes[tess.numIndexes++] = vbase + 2;
	tess.indexes[tess.numIndexes++] = vbase + 1;
	tess.indexes[tess.numIndexes++] = vbase + 3;
}