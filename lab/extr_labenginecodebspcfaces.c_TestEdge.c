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
typedef  scalar_t__ vec_t ;
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_2__ {int /*<<< orphan*/  point; } ;

/* Variables and functions */
 scalar_t__ DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Error (char*) ; 
 size_t MAX_SUPERVERTS ; 
 scalar_t__ OFF_EPSILON ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ VectorLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_degenerate ; 
 int /*<<< orphan*/  c_tjunctions ; 
 TYPE_1__* dvertexes ; 
 int /*<<< orphan*/  edge_dir ; 
 int /*<<< orphan*/  edge_start ; 
 int* edge_verts ; 
 scalar_t__ fabs (scalar_t__) ; 
 int num_edge_verts ; 
 size_t numsuperverts ; 
 int* superverts ; 

void TestEdge (vec_t start, vec_t end, int p1, int p2, int startvert)
{
	int		j, k;
	vec_t	dist;
	vec3_t	delta;
	vec3_t	exact;
	vec3_t	off;
	vec_t	error;
	vec3_t	p;

	if (p1 == p2)
	{
		c_degenerate++;
		return;		// degenerate edge
	}

	for (k=startvert ; k<num_edge_verts ; k++)
	{
		j = edge_verts[k];
		if (j==p1 || j == p2)
			continue;

		VectorCopy (dvertexes[j].point, p);

		VectorSubtract (p, edge_start, delta);
		dist = DotProduct (delta, edge_dir);
		if (dist <=start || dist >= end)
			continue;		// off an end
		VectorMA (edge_start, dist, edge_dir, exact);
		VectorSubtract (p, exact, off);
		error = VectorLength (off);

		if (fabs(error) > OFF_EPSILON)
			continue;		// not on the edge

		// break the edge
		c_tjunctions++;
		TestEdge (start, dist, p1, j, k+1);
		TestEdge (dist, end, j, p2, k+1);
		return;
	}

	// the edge p1 to p2 is now free of tjunctions
	if (numsuperverts >= MAX_SUPERVERTS)
		Error ("MAX_SUPERVERTS");
	superverts[numsuperverts] = p1;
	numsuperverts++;
}