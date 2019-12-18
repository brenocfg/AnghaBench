#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_7__ {int /*<<< orphan*/  normal; int /*<<< orphan*/  dist; } ;
typedef  TYPE_2__ th_plane_t ;
struct TYPE_8__ {TYPE_1__* vertexes; } ;
struct TYPE_6__ {int /*<<< orphan*/  v; } ;

/* Variables and functions */
 int /*<<< orphan*/  CrossProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorNormalize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ thworld ; 

void TH_CreateTrianglePlanes(int verts[3], th_plane_t *triplane, th_plane_t *planes)
{
	int i;
	vec3_t dir;

	for (i = 0; i < 3; i++)
	{
		VectorSubtract(thworld.vertexes[verts[(i+1)%3]].v, thworld.vertexes[verts[i]].v, dir);
		CrossProduct(dir, triplane->normal, planes[i].normal);
		VectorNormalize(planes[i].normal);
		planes[i].dist = DotProduct(thworld.vertexes[verts[i]].v, planes[i].normal);
	} //end for
}