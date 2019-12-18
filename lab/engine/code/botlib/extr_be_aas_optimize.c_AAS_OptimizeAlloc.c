#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int numedges; int numfaces; int numareas; int* vertexoptimizeindex; int* edgeoptimizeindex; int* faceoptimizeindex; int /*<<< orphan*/ * areas; scalar_t__ faceindexsize; int /*<<< orphan*/ * faceindex; int /*<<< orphan*/ * faces; scalar_t__ edgeindexsize; int /*<<< orphan*/ * edgeindex; int /*<<< orphan*/ * edges; scalar_t__ numvertexes; int /*<<< orphan*/ * vertexes; } ;
typedef  TYPE_1__ optimized_t ;
typedef  int /*<<< orphan*/  aas_vertex_t ;
typedef  int /*<<< orphan*/  aas_faceindex_t ;
typedef  int /*<<< orphan*/  aas_face_t ;
typedef  int /*<<< orphan*/  aas_edgeindex_t ;
typedef  int /*<<< orphan*/  aas_edge_t ;
typedef  int /*<<< orphan*/  aas_area_t ;
struct TYPE_5__ {int numvertexes; int numedges; int edgeindexsize; int numfaces; int faceindexsize; int numareas; } ;

/* Variables and functions */
 scalar_t__ GetClearedMemory (int) ; 
 TYPE_2__ aasworld ; 

void AAS_OptimizeAlloc(optimized_t *optimized)
{
	optimized->vertexes = (aas_vertex_t *) GetClearedMemory(aasworld.numvertexes * sizeof(aas_vertex_t));
	optimized->numvertexes = 0;
	optimized->edges = (aas_edge_t *) GetClearedMemory(aasworld.numedges * sizeof(aas_edge_t));
	optimized->numedges = 1; //edge zero is a dummy
	optimized->edgeindex = (aas_edgeindex_t *) GetClearedMemory(aasworld.edgeindexsize * sizeof(aas_edgeindex_t));
	optimized->edgeindexsize = 0;
	optimized->faces = (aas_face_t *) GetClearedMemory(aasworld.numfaces * sizeof(aas_face_t));
	optimized->numfaces = 1; //face zero is a dummy
	optimized->faceindex = (aas_faceindex_t *) GetClearedMemory(aasworld.faceindexsize * sizeof(aas_faceindex_t));
	optimized->faceindexsize = 0;
	optimized->areas = (aas_area_t *) GetClearedMemory(aasworld.numareas * sizeof(aas_area_t));
	optimized->numareas = aasworld.numareas;
	//
	optimized->vertexoptimizeindex = (int *) GetClearedMemory(aasworld.numvertexes * sizeof(int));
	optimized->edgeoptimizeindex = (int *) GetClearedMemory(aasworld.numedges * sizeof(int));
	optimized->faceoptimizeindex = (int *) GetClearedMemory(aasworld.numfaces * sizeof(int));
}