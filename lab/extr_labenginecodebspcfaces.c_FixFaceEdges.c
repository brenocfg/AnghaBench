#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec_t ;
typedef  int /*<<< orphan*/  vec3_t ;
typedef  int /*<<< orphan*/  node_t ;
struct TYPE_5__ {int numpoints; int* vertexnums; int badstartvert; scalar_t__* split; scalar_t__ merged; } ;
typedef  TYPE_1__ face_t ;
struct TYPE_6__ {int /*<<< orphan*/  point; } ;

/* Variables and functions */
 int /*<<< orphan*/  FaceFromSuperverts (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  FindEdgeVerts (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_SUPERVERTS ; 
 int /*<<< orphan*/  TestEdge (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorNormalize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_badstartverts ; 
 int /*<<< orphan*/  c_facecollapse ; 
 TYPE_2__* dvertexes ; 
 int /*<<< orphan*/  edge_dir ; 
 int /*<<< orphan*/  edge_start ; 
 int numsuperverts ; 

void FixFaceEdges (node_t *node, face_t *f)
{
	int		p1, p2;
	int		i;
	vec3_t	e2;
	vec_t	len;
	int		count[MAX_SUPERVERTS], start[MAX_SUPERVERTS];
	int		base;

	if (f->merged || f->split[0] || f->split[1])
		return;

	numsuperverts = 0;

	for (i=0 ; i<f->numpoints ; i++)
	{
		p1 = f->vertexnums[i];
		p2 = f->vertexnums[(i+1)%f->numpoints];

		VectorCopy (dvertexes[p1].point, edge_start);
		VectorCopy (dvertexes[p2].point, e2);

		FindEdgeVerts (edge_start, e2);

		VectorSubtract (e2, edge_start, edge_dir);
		len = VectorNormalize(edge_dir);

		start[i] = numsuperverts;
		TestEdge (0, len, p1, p2, 0);

		count[i] = numsuperverts - start[i];
	}

	if (numsuperverts < 3)
	{	// entire face collapsed
		f->numpoints = 0;
		c_facecollapse++;
		return;
	}

	// we want to pick a vertex that doesn't have tjunctions
	// on either side, which can cause artifacts on trifans,
	// especially underwater
	for (i=0 ; i<f->numpoints ; i++)
	{
		if (count[i] == 1 && count[(i+f->numpoints-1)%f->numpoints] == 1)
			break;
	}
	if (i == f->numpoints)
	{
		f->badstartvert = true;
		c_badstartverts++;
		base = 0;
	}
	else
	{	// rotate the vertex order
		base = start[i];
	}

	// this may fragment the face if > MAXEDGES
	FaceFromSuperverts (node, f, base);
}