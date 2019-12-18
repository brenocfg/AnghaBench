#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* winding; struct TYPE_7__* l_next; } ;
typedef  TYPE_2__ tmp_face_t ;
struct TYPE_8__ {struct TYPE_8__* l_next; } ;
typedef  TYPE_3__ tmp_area_t ;
struct TYPE_10__ {int max_vertexes; int max_edges; int max_edgeindexsize; int max_faces; int max_faceindexsize; int max_areas; int max_areasettings; scalar_t__ max_clusters; scalar_t__ max_portalindexsize; scalar_t__ max_portals; scalar_t__ max_nodes; scalar_t__ max_reachabilitysize; int /*<<< orphan*/  max_planes; int /*<<< orphan*/  max_bboxes; } ;
struct TYPE_9__ {int /*<<< orphan*/  nodes; TYPE_3__* areas; TYPE_2__* faces; } ;
struct TYPE_6__ {scalar_t__ numpoints; } ;

/* Variables and functions */
 scalar_t__ AAS_CountTmpNodes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AAS_MAX_BBOXES ; 
 TYPE_5__ max_aas ; 
 int /*<<< orphan*/  nummapplanes ; 
 TYPE_4__ tmpaasworld ; 

void AAS_InitMaxAAS(void)
{
	int numfaces, numpoints, numareas;
	tmp_face_t *f;
	tmp_area_t *a;

	numpoints = 0;
	numfaces = 0;
	for (f = tmpaasworld.faces; f; f = f->l_next)
	{
		numfaces++;
		if (f->winding) numpoints += f->winding->numpoints;
	} //end for
	//
	numareas = 0;
	for (a = tmpaasworld.areas; a; a = a->l_next)
	{
		numareas++;
	} //end for
	max_aas.max_bboxes = AAS_MAX_BBOXES;
	max_aas.max_vertexes = numpoints + 1;
	max_aas.max_planes = nummapplanes;
	max_aas.max_edges = numpoints + 1;
	max_aas.max_edgeindexsize = (numpoints + 1) * 3;
	max_aas.max_faces = numfaces + 10;
	max_aas.max_faceindexsize = (numfaces + 10) * 2;
	max_aas.max_areas = numareas + 10;
	max_aas.max_areasettings = numareas + 10;
	max_aas.max_reachabilitysize = 0;
	max_aas.max_nodes = AAS_CountTmpNodes(tmpaasworld.nodes) + 10;
	max_aas.max_portals = 0;
	max_aas.max_portalindexsize = 0;
	max_aas.max_clusters = 0;
}