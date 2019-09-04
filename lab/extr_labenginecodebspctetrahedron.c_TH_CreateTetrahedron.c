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
struct TYPE_5__ {int* triangles; scalar_t__ volume; } ;
typedef  TYPE_2__ th_tetrahedron_t ;
struct TYPE_6__ {int numtetrahedrons; TYPE_1__* triangles; TYPE_2__* tetrahedrons; } ;
struct TYPE_4__ {int front; int back; } ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 int MAX_TH_TETRAHEDRONS ; 
 size_t abs (int) ; 
 TYPE_3__ thworld ; 

int TH_CreateTetrahedron(int triangles[4])
{
	th_tetrahedron_t *tetrahedron;
	int i;

	if (thworld.numtetrahedrons == 0) thworld.numtetrahedrons = 1;
	if (thworld.numtetrahedrons >= MAX_TH_TETRAHEDRONS)
		Error("MAX_TH_TETRAHEDRONS");
	tetrahedron = &thworld.tetrahedrons[thworld.numtetrahedrons++];
	for (i = 0; i < 4; i++)
	{
		tetrahedron->triangles[i] = triangles[i];
		if (thworld.triangles[abs(triangles[i])].front)
		{
			thworld.triangles[abs(triangles[i])].back = thworld.numtetrahedrons-1;
		} //end if
		else
		{
			thworld.triangles[abs(triangles[i])].front = thworld.numtetrahedrons-1;
		} //end else
	} //end for
	tetrahedron->volume = 0;
	return thworld.numtetrahedrons-1;
}