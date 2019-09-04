#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {float* normal; float* tangent; int /*<<< orphan*/  xyz; } ;
typedef  TYPE_3__ mdvVertex_t ;
struct TYPE_11__ {int numVerts; TYPE_3__* verts; } ;
typedef  TYPE_4__ mdvSurface_t ;
typedef  float int16_t ;
struct TYPE_13__ {TYPE_2__* currentEntity; } ;
struct TYPE_12__ {float** xyz; size_t numVertexes; float** normal; float** tangent; } ;
struct TYPE_8__ {int frame; int oldframe; } ;
struct TYPE_9__ {TYPE_1__ e; } ;

/* Variables and functions */
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  VectorCopy4 (float*,float*) ; 
 int /*<<< orphan*/  VectorLerp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float,float*) ; 
 TYPE_6__ backEnd ; 
 TYPE_5__ tess ; 

__attribute__((used)) static void LerpMeshVertexes(mdvSurface_t *surf, float backlerp)
{
	float *outXyz;
	int16_t *outNormal, *outTangent;
	mdvVertex_t *newVerts;
	int		vertNum;

	newVerts = surf->verts + backEnd.currentEntity->e.frame * surf->numVerts;

	outXyz =     tess.xyz[tess.numVertexes];
	outNormal =  tess.normal[tess.numVertexes];
	outTangent = tess.tangent[tess.numVertexes];

	if (backlerp == 0)
	{
		//
		// just copy the vertexes
		//

		for (vertNum=0 ; vertNum < surf->numVerts ; vertNum++)
		{
			VectorCopy(newVerts->xyz,    outXyz);
			VectorCopy4(newVerts->normal, outNormal);
			VectorCopy4(newVerts->tangent, outTangent);

			newVerts++;
			outXyz += 4;
			outNormal += 4;
			outTangent += 4;
		}
	}
	else
	{
		//
		// interpolate and copy the vertex and normal
		//

		mdvVertex_t *oldVerts;

		oldVerts = surf->verts + backEnd.currentEntity->e.oldframe * surf->numVerts;

		for (vertNum=0 ; vertNum < surf->numVerts ; vertNum++)
		{
			VectorLerp(newVerts->xyz,    oldVerts->xyz,    backlerp, outXyz);

			outNormal[0] = (int16_t)(newVerts->normal[0] * (1.0f - backlerp) + oldVerts->normal[0] * backlerp);
			outNormal[1] = (int16_t)(newVerts->normal[1] * (1.0f - backlerp) + oldVerts->normal[1] * backlerp);
			outNormal[2] = (int16_t)(newVerts->normal[2] * (1.0f - backlerp) + oldVerts->normal[2] * backlerp);
			outNormal[3] = 0;

			outTangent[0] = (int16_t)(newVerts->tangent[0] * (1.0f - backlerp) + oldVerts->tangent[0] * backlerp);
			outTangent[1] = (int16_t)(newVerts->tangent[1] * (1.0f - backlerp) + oldVerts->tangent[1] * backlerp);
			outTangent[2] = (int16_t)(newVerts->tangent[2] * (1.0f - backlerp) + oldVerts->tangent[2] * backlerp);
			outTangent[3] = newVerts->tangent[3];

			newVerts++;
			oldVerts++;
			outXyz += 4;
			outNormal += 4;
			outTangent += 4;
		}
	}

}