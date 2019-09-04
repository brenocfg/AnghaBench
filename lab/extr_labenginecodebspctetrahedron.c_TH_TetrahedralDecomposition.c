#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ back; scalar_t__ front; } ;
typedef  TYPE_1__ th_triangle_t ;
struct TYPE_7__ {int numtetrahedrons; int numtriangles; TYPE_1__* triangles; } ;

/* Variables and functions */
 int /*<<< orphan*/  Log_Print (char*,int) ; 
 int /*<<< orphan*/  TH_CreateTetrahedron (int*) ; 
 int /*<<< orphan*/  TH_FindTetrahedron1 (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  TH_FindTetrahedron2 (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  qprintf (char*,int) ; 
 TYPE_2__ thworld ; 

void TH_TetrahedralDecomposition(th_triangle_t *triangles)
{
	int i, thtriangles[4], numtriangles;
	th_triangle_t *donetriangles, *tri;

	donetriangles = NULL;

	/*
	numtriangles = 0;
	qprintf("%6d triangles", numtriangles);
	for (tri = triangles; tri; tri = triangles)
	{
		qprintf("\r%6d", numtriangles++);
		if (!TH_FindTetrahedron1(tri, thtriangles))
		{
//			if (!TH_FindTetrahedron2(tri, thtriangles))
			{
//				Error("triangle without tetrahedron");
				TH_RemoveTriangleFromList(&triangles, tri);
				continue;
			} //end if
		} //end if
		//create a tetrahedron from the triangles
		TH_CreateTetrahedron(thtriangles);
		//
		for (i = 0; i < 4; i++)
		{
			if (thworld.triangles[abs(thtriangles[i])].front &&
				thworld.triangles[abs(thtriangles[i])].back)
			{
				TH_RemoveTriangleFromList(&triangles, &thworld.triangles[abs(thtriangles[i])]);
				TH_AddTriangleToList(&donetriangles, &thworld.triangles[abs(thtriangles[i])]);
				TH_FreeTriangleEdges(&thworld.triangles[abs(thtriangles[i])]);
			} //end if
			else
			{
				TH_AddTriangleToList(&triangles, &thworld.triangles[abs(thtriangles[i])]);
			} //end else
		} //end for
	} //end for*/
	qprintf("%6d tetrahedrons", thworld.numtetrahedrons);
	do
	{
		do
		{
			numtriangles = 0;
			for (i = 1; i < thworld.numtriangles; i++)
			{
				tri = &thworld.triangles[i];
				if (tri->front && tri->back) continue;
				//qprintf("\r%6d", numtriangles++);
				if (!TH_FindTetrahedron1(tri, thtriangles))
				{
//					if (!TH_FindTetrahedron2(tri, thtriangles))
					{
						continue;
					} //end if
				} //end if
				numtriangles++;
				//create a tetrahedron from the triangles
				TH_CreateTetrahedron(thtriangles);
				qprintf("\r%6d", thworld.numtetrahedrons);
			} //end for
		} while(numtriangles);
 		for (i = 1; i < thworld.numtriangles; i++)
		{
			tri = &thworld.triangles[i];
			if (tri->front && tri->back) continue;
			//qprintf("\r%6d", numtriangles++);
//			if (!TH_FindTetrahedron1(tri, thtriangles))
			{
				if (!TH_FindTetrahedron2(tri, thtriangles))
				{
					continue;
				} //end if
			} //end if
			numtriangles++;
			//create a tetrahedron from the triangles
			TH_CreateTetrahedron(thtriangles);
			qprintf("\r%6d", thworld.numtetrahedrons);
		} //end for
	} while(numtriangles);
	//
	numtriangles = 0;
	for (i = 1; i < thworld.numtriangles; i++)
	{
		tri = &thworld.triangles[i];
		if (!tri->front && !tri->back) numtriangles++;
	} //end for
	Log_Print("\r%6d triangles with front only\n", numtriangles);
	Log_Print("\r%6d tetrahedrons\n", thworld.numtetrahedrons-1);
}