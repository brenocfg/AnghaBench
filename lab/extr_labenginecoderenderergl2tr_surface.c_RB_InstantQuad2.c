#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec4_t ;
typedef  int /*<<< orphan*/  vec2_t ;
struct TYPE_2__ {size_t numVertexes; int* indexes; scalar_t__ firstIndex; scalar_t__ numIndexes; int /*<<< orphan*/ * texCoords; int /*<<< orphan*/ * xyz; } ;

/* Variables and functions */
 int ATTR_POSITION ; 
 int ATTR_TEXCOORD ; 
 int /*<<< orphan*/  GLimp_LogComment (char*) ; 
 int /*<<< orphan*/  RB_UpdateTessVao (int) ; 
 int /*<<< orphan*/  R_DrawElements (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  VectorCopy2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ tess ; 

void RB_InstantQuad2(vec4_t quadVerts[4], vec2_t texCoords[4])
{
	GLimp_LogComment("--- RB_InstantQuad2 ---\n");

	tess.numVertexes = 0;
	tess.numIndexes = 0;
	tess.firstIndex = 0;

	VectorCopy4(quadVerts[0], tess.xyz[tess.numVertexes]);
	VectorCopy2(texCoords[0], tess.texCoords[tess.numVertexes]);
	tess.numVertexes++;

	VectorCopy4(quadVerts[1], tess.xyz[tess.numVertexes]);
	VectorCopy2(texCoords[1], tess.texCoords[tess.numVertexes]);
	tess.numVertexes++;

	VectorCopy4(quadVerts[2], tess.xyz[tess.numVertexes]);
	VectorCopy2(texCoords[2], tess.texCoords[tess.numVertexes]);
	tess.numVertexes++;

	VectorCopy4(quadVerts[3], tess.xyz[tess.numVertexes]);
	VectorCopy2(texCoords[3], tess.texCoords[tess.numVertexes]);
	tess.numVertexes++;

	tess.indexes[tess.numIndexes++] = 0;
	tess.indexes[tess.numIndexes++] = 1;
	tess.indexes[tess.numIndexes++] = 2;
	tess.indexes[tess.numIndexes++] = 0;
	tess.indexes[tess.numIndexes++] = 2;
	tess.indexes[tess.numIndexes++] = 3;

	RB_UpdateTessVao(ATTR_POSITION | ATTR_TEXCOORD);

	R_DrawElements(tess.numIndexes, tess.firstIndex);

	tess.numIndexes = 0;
	tess.numVertexes = 0;
	tess.firstIndex = 0;
}