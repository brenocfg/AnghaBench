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
typedef  int* vec3_t ;

/* Variables and functions */
 scalar_t__ AAS_AreaReachability (int) ; 
 int AAS_PointAreaNum (int*) ; 
 int AAS_TraceAreas (int*,int*,int*,int**,int) ; 
 int /*<<< orphan*/  VectorCopy (int*,int*) ; 
 float VectorLength (int*) ; 
 int /*<<< orphan*/  VectorSubtract (int*,int*,int*) ; 

int BotFuzzyPointReachabilityArea(vec3_t origin)
{
	int firstareanum, j, x, y, z;
	int areas[10], numareas, areanum, bestareanum;
	float dist, bestdist;
	vec3_t points[10], v, end;

	firstareanum = 0;
	areanum = AAS_PointAreaNum(origin);
	if (areanum)
	{
		firstareanum = areanum;
		if (AAS_AreaReachability(areanum)) return areanum;
	} //end if
	VectorCopy(origin, end);
	end[2] += 4;
	numareas = AAS_TraceAreas(origin, end, areas, points, 10);
	for (j = 0; j < numareas; j++)
	{
		if (AAS_AreaReachability(areas[j])) return areas[j];
	} //end for
	bestdist = 999999;
	bestareanum = 0;
	for (z = 1; z >= -1; z -= 1)
	{
		for (x = 1; x >= -1; x -= 1)
		{
			for (y = 1; y >= -1; y -= 1)
			{
				VectorCopy(origin, end);
				end[0] += x * 8;
				end[1] += y * 8;
				end[2] += z * 12;
				numareas = AAS_TraceAreas(origin, end, areas, points, 10);
				for (j = 0; j < numareas; j++)
				{
					if (AAS_AreaReachability(areas[j]))
					{
						VectorSubtract(points[j], origin, v);
						dist = VectorLength(v);
						if (dist < bestdist)
						{
							bestareanum = areas[j];
							bestdist = dist;
						} //end if
					} //end if
					if (!firstareanum) firstareanum = areas[j];
				} //end for
			} //end for
		} //end for
		if (bestareanum) return bestareanum;
	} //end for
	return firstareanum;
}