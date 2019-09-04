#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* v; struct TYPE_3__* hashnext; } ;
typedef  TYPE_1__ th_edge_t ;
struct TYPE_4__ {TYPE_1__* edges; TYPE_1__** edgehash; } ;

/* Variables and functions */
 int EDGEHASH_SIZE ; 
 TYPE_2__ thworld ; 

int TH_FindEdge(int v1, int v2)
{
	int hashvalue;
	th_edge_t *edge;

	hashvalue = (v1 + v2) & (EDGEHASH_SIZE-1);

	for (edge = thworld.edgehash[hashvalue]; edge; edge = edge->hashnext)
	{
		if (edge->v[0] == v1 && edge->v[1] == v2) return edge - thworld.edges;
		if (edge->v[1] == v1 && edge->v[0] == v2) return -(edge - thworld.edges);
	} //end for
	return 0;
}