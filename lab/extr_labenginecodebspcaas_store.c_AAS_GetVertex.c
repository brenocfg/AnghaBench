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
typedef  int /*<<< orphan*/  vec3_t ;
typedef  int qboolean ;
struct TYPE_4__ {int numvertexes; float** vertexes; } ;
struct TYPE_3__ {int max_vertexes; } ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*,int) ; 
 float VERTEX_EPSILON ; 
 int /*<<< orphan*/  VectorCopy (float*,float*) ; 
 TYPE_2__ aasworld ; 
 TYPE_1__ max_aas ; 
 float* vert ; 

qboolean AAS_GetVertex(vec3_t v, int *vnum)
{
	int i;
#ifndef VERTEX_HASHING
	float diff;
#endif //VERTEX_HASHING

#ifdef VERTEX_HASHING
	int h, vn;
	vec3_t vert;
	
	for (i = 0; i < 3; i++)
	{
		if ( fabs(v[i] - Q_rint(v[i])) < INTEGRAL_EPSILON)
			vert[i] = Q_rint(v[i]);
		else
			vert[i] = v[i];
	} //end for

	h = AAS_HashVec(vert);
	//if the vertex was outside the valid range
	if (h == -1)
	{
		*vnum = -1;
		return true;
	} //end if

	for (vn = aas_hashverts[h]; vn >= 0; vn = aas_vertexchain[vn])
	{
		if (fabs(aasworld.vertexes[vn][0] - vert[0]) < VERTEX_EPSILON
				&& fabs(aasworld.vertexes[vn][1] - vert[1]) < VERTEX_EPSILON
				&& fabs(aasworld.vertexes[vn][2] - vert[2]) < VERTEX_EPSILON)
		{
			*vnum = vn;
			return true;
		} //end if
	} //end for
#else //VERTEX_HASHING
	//check if the vertex is already stored
	//stupid linear search
	for (i = 0; i < aasworld.numvertexes; i++)
	{
		diff = vert[0] - aasworld.vertexes[i][0];
		if (diff < VERTEX_EPSILON && diff > -VERTEX_EPSILON)
		{
			diff = vert[1] - aasworld.vertexes[i][1];
			if (diff < VERTEX_EPSILON && diff > -VERTEX_EPSILON)
			{
				diff = vert[2] - aasworld.vertexes[i][2];
				if (diff < VERTEX_EPSILON && diff > -VERTEX_EPSILON)
				{
					*vnum = i;
					return true;
				} //end if
			} //end if
		} //end if
	} //end for
#endif //VERTEX_HASHING

	if (aasworld.numvertexes >= max_aas.max_vertexes)
	{
		Error("AAS_MAX_VERTEXES = %d", max_aas.max_vertexes);
	} //end if
	VectorCopy(vert, aasworld.vertexes[aasworld.numvertexes]);
	*vnum = aasworld.numvertexes;

#ifdef VERTEX_HASHING
	aas_vertexchain[aasworld.numvertexes] = aas_hashverts[h];
	aas_hashverts[h] = aasworld.numvertexes;
#endif //VERTEX_HASHING

	aasworld.numvertexes++;
	return false;
}