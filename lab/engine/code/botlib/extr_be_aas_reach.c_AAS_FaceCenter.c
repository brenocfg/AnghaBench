#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_4__ {int numedges; int firstedge; } ;
typedef  TYPE_1__ aas_face_t ;
struct TYPE_5__ {size_t* v; } ;
typedef  TYPE_2__ aas_edge_t ;
struct TYPE_6__ {int /*<<< orphan*/ * vertexes; int /*<<< orphan*/ * edgeindex; TYPE_2__* edges; TYPE_1__* faces; } ;

/* Variables and functions */
 int /*<<< orphan*/  VectorAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorScale (int /*<<< orphan*/ ,float,int /*<<< orphan*/ ) ; 
 TYPE_3__ aasworld ; 
 size_t abs (int /*<<< orphan*/ ) ; 

void AAS_FaceCenter(int facenum, vec3_t center)
{
	int i;
	float scale;
	aas_face_t *face;
	aas_edge_t *edge;

	face = &aasworld.faces[facenum];

	VectorClear(center);
	for (i = 0; i < face->numedges; i++)
	{
		edge = &aasworld.edges[abs(aasworld.edgeindex[face->firstedge + i])];
		VectorAdd(center, aasworld.vertexes[edge->v[0]], center);
		VectorAdd(center, aasworld.vertexes[edge->v[1]], center);
	} //end for
	scale = 0.5 / face->numedges;
	VectorScale(center, scale, center);
}