#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* prev; struct TYPE_4__* next; } ;
typedef  TYPE_1__ th_triangle_t ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_LoadAASFile (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Error (char*,char*) ; 
 int /*<<< orphan*/  Log_Print (char*,...) ; 
 TYPE_1__* TH_AASToTriangleMesh () ; 
 int /*<<< orphan*/  TH_FreeMaxTH () ; 
 int /*<<< orphan*/  TH_InitMaxTH () ; 
 int /*<<< orphan*/  TH_TetrahedralDecomposition (TYPE_1__*) ; 

void TH_AASToTetrahedrons(char *filename)
{
	th_triangle_t *triangles, *tri, *lasttri;
	int cnt;

	if (!AAS_LoadAASFile(filename, 0, 0))
		Error("couldn't load %s\n", filename);

	//
	TH_InitMaxTH();
	//create a triangle mesh from the solid faces in the AAS file
	triangles = TH_AASToTriangleMesh();
	//
	cnt = 0;
	lasttri = NULL;
	for (tri = triangles; tri; tri = tri->next)
	{
		cnt++;
		if (tri->prev != lasttri) Log_Print("BAH\n");
		lasttri = tri;
	} //end for
	Log_Print("%6d triangles\n", cnt);
	//create a tetrahedral decomposition of the world bounded by triangles
	TH_TetrahedralDecomposition(triangles);
	//
	TH_FreeMaxTH();
}