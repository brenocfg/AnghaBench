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
struct TYPE_5__ {size_t* v; int /*<<< orphan*/  usercount; } ;
typedef  TYPE_2__ th_edge_t ;
struct TYPE_6__ {TYPE_1__* vertexes; TYPE_2__* edges; } ;
struct TYPE_4__ {int /*<<< orphan*/  usercount; } ;

/* Variables and functions */
 size_t abs (int) ; 
 TYPE_3__ thworld ; 

void TH_RemoveEdgeUser(int edgenum)
{
	th_edge_t *edge;

	edge = &thworld.edges[abs(edgenum)];
	//decrease edge user count
	edge->usercount--;
	//decrease vertex user count as well
	thworld.vertexes[edge->v[0]].usercount--;
	thworld.vertexes[edge->v[1]].usercount--;
}