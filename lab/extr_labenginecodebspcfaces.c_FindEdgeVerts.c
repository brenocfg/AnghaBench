#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__* vec3_t ;

/* Variables and functions */
 int HASH_SIZE ; 
 int* edge_verts ; 
 int* hashverts ; 
 scalar_t__ num_edge_verts ; 
 int* vertexchain ; 

void FindEdgeVerts (vec3_t v1, vec3_t v2)
{
	int		x1, x2, y1, y2, t;
	int		x, y;
	int		vnum;

#if 0
{
	int		i;
	num_edge_verts = numvertexes-1;
	for (i=0 ; i<numvertexes-1 ; i++)
		edge_verts[i] = i+1;
}
#endif

	x1 = (4096 + (int)(v1[0]+0.5)) >> 7;
	y1 = (4096 + (int)(v1[1]+0.5)) >> 7;
	x2 = (4096 + (int)(v2[0]+0.5)) >> 7;
	y2 = (4096 + (int)(v2[1]+0.5)) >> 7;

	if (x1 > x2)
	{
		t = x1;
		x1 = x2;
		x2 = t;
	}
	if (y1 > y2)
	{
		t = y1;
		y1 = y2;
		y2 = t;
	}
#if 0
	x1--;
	x2++;
	y1--;
	y2++;
	if (x1 < 0)
		x1 = 0;
	if (x2 >= HASH_SIZE)
		x2 = HASH_SIZE;
	if (y1 < 0)
		y1 = 0;
	if (y2 >= HASH_SIZE)
		y2 = HASH_SIZE;
#endif
	num_edge_verts = 0;
	for (x=x1 ; x <= x2 ; x++)
	{
		for (y=y1 ; y <= y2 ; y++)
		{
			for (vnum=hashverts[y*HASH_SIZE+x] ; vnum ; vnum=vertexchain[vnum])
			{
				edge_verts[num_edge_verts++] = vnum;
			}
		}
	}
}