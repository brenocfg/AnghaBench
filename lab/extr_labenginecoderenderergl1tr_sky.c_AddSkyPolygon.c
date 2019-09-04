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
 int /*<<< orphan*/  VectorAdd (float*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ fabs (scalar_t__) ; 
 float** sky_maxs ; 
 float** sky_mins ; 
 int /*<<< orphan*/  vec3_origin ; 

__attribute__((used)) static void AddSkyPolygon (int nump, vec3_t vecs) 
{
	int		i,j;
	vec3_t	v, av;
	float	s, t, dv;
	int		axis;
	float	*vp;
	// s = [0]/[2], t = [1]/[2]
	static int	vec_to_st[6][3] =
	{
		{-2,3,1},
		{2,3,-1},

		{1,3,2},
		{-1,3,-2},

		{-2,-1,3},
		{-2,1,-3}

	//	{-1,2,3},
	//	{1,2,-3}
	};

	// decide which face it maps to
	VectorCopy (vec3_origin, v);
	for (i=0, vp=vecs ; i<nump ; i++, vp+=3)
	{
		VectorAdd (vp, v, v);
	}
	av[0] = fabs(v[0]);
	av[1] = fabs(v[1]);
	av[2] = fabs(v[2]);
	if (av[0] > av[1] && av[0] > av[2])
	{
		if (v[0] < 0)
			axis = 1;
		else
			axis = 0;
	}
	else if (av[1] > av[2] && av[1] > av[0])
	{
		if (v[1] < 0)
			axis = 3;
		else
			axis = 2;
	}
	else
	{
		if (v[2] < 0)
			axis = 5;
		else
			axis = 4;
	}

	// project new texture coords
	for (i=0 ; i<nump ; i++, vecs+=3)
	{
		j = vec_to_st[axis][2];
		if (j > 0)
			dv = vecs[j - 1];
		else
			dv = -vecs[-j - 1];
		if (dv < 0.001)
			continue;	// don't divide by zero
		j = vec_to_st[axis][0];
		if (j < 0)
			s = -vecs[-j -1] / dv;
		else
			s = vecs[j-1] / dv;
		j = vec_to_st[axis][1];
		if (j < 0)
			t = -vecs[-j -1] / dv;
		else
			t = vecs[j-1] / dv;

		if (s < sky_mins[0][axis])
			sky_mins[0][axis] = s;
		if (t < sky_mins[1][axis])
			sky_mins[1][axis] = t;
		if (s > sky_maxs[0][axis])
			sky_maxs[0][axis] = s;
		if (t > sky_maxs[1][axis])
			sky_maxs[1][axis] = t;
	}
}