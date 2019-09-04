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
struct TYPE_2__ {scalar_t__ numtetrahedrons; int /*<<< orphan*/ * tetrahedrons; scalar_t__ numtriangles; int /*<<< orphan*/ * triangles; scalar_t__ numedges; int /*<<< orphan*/ * edges; scalar_t__ numplanes; int /*<<< orphan*/ * planes; scalar_t__ numvertexes; int /*<<< orphan*/ * vertexes; } ;

/* Variables and functions */
 int /*<<< orphan*/  FreeMemory (int /*<<< orphan*/ *) ; 
 TYPE_1__ thworld ; 

void TH_FreeMaxTH(void)
{
	if (thworld.vertexes) FreeMemory(thworld.vertexes);
	thworld.vertexes = NULL;
	thworld.numvertexes = 0;
	if (thworld.planes) FreeMemory(thworld.planes);
	thworld.planes = NULL;
	thworld.numplanes = 0;
	if (thworld.edges) FreeMemory(thworld.edges);
	thworld.edges = NULL;
	thworld.numedges = 0;
	if (thworld.triangles) FreeMemory(thworld.triangles);
	thworld.triangles = NULL;
	thworld.numtriangles = 0;
	if (thworld.tetrahedrons) FreeMemory(thworld.tetrahedrons);
	thworld.tetrahedrons = NULL;
	thworld.numtetrahedrons = 0;
}