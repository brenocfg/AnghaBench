#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int* faceoptimizeindex; size_t numfaces; int edgeindexsize; int* edgeindex; TYPE_2__* faces; } ;
typedef  TYPE_1__ optimized_t ;
struct TYPE_10__ {int numedges; int firstedge; } ;
typedef  TYPE_2__ aas_face_t ;
struct TYPE_11__ {int* edgeindex; TYPE_2__* faces; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_KeepFace (TYPE_2__*) ; 
 int AAS_OptimizeEdge (TYPE_1__*,int) ; 
 int /*<<< orphan*/  Com_Memcpy (TYPE_2__*,TYPE_2__*,int) ; 
 TYPE_3__ aasworld ; 
 size_t abs (int) ; 

int AAS_OptimizeFace(optimized_t *optimized, int facenum)
{
	int i, edgenum, optedgenum, optfacenum;
	aas_face_t *face, *optface;

	face = &aasworld.faces[abs(facenum)];
	if (!AAS_KeepFace(face)) return 0;

	optfacenum = optimized->faceoptimizeindex[abs(facenum)];
	if (optfacenum)
	{
		//keep the face side sign
		if (facenum > 0) return optfacenum;
		else return -optfacenum;
	} //end if

	optface = &optimized->faces[optimized->numfaces];
	Com_Memcpy(optface, face, sizeof(aas_face_t));

	optface->numedges = 0;
	optface->firstedge = optimized->edgeindexsize;
	for (i = 0; i < face->numedges; i++)
	{
		edgenum = aasworld.edgeindex[face->firstedge + i];
		optedgenum = AAS_OptimizeEdge(optimized, edgenum);
		if (optedgenum)
		{
			optimized->edgeindex[optface->firstedge + optface->numedges] = optedgenum;
			optface->numedges++;
			optimized->edgeindexsize++;
		} //end if
	} //end for
	optimized->faceoptimizeindex[abs(facenum)] = optimized->numfaces;
	optfacenum = optimized->numfaces;
	optimized->numfaces++;
	//keep the face side sign
	if (facenum > 0) return optfacenum;
	else return -optfacenum;
}