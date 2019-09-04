#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int* vec3_t ;
struct TYPE_6__ {int fraction; int* endpos; int /*<<< orphan*/  startsolid; } ;
typedef  TYPE_2__ aas_trace_t ;
struct TYPE_7__ {int numareas; TYPE_1__* areas; } ;
struct TYPE_5__ {int* center; } ;

/* Variables and functions */
 int AAS_AreaGroundFaceArea (int) ; 
 scalar_t__ AAS_AreaReachability (int) ; 
 scalar_t__ AAS_AreaSwim (int) ; 
 int AAS_AreaTravelTimeToGoalArea (int,int*,int,int) ; 
 int AAS_PointAreaNum (int*) ; 
 TYPE_2__ AAS_TraceClientBBox (int*,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Log_Write (char*,int,int,int,int) ; 
 int /*<<< orphan*/  PRESENCE_CROUCH ; 
 int /*<<< orphan*/  VectorCopy (int*,int*) ; 
 TYPE_3__ aasworld ; 
 int qfalse ; 
 int qtrue ; 
 int random () ; 

int AAS_RandomGoalArea(int areanum, int travelflags, int *goalareanum, vec3_t goalorigin)
{
	int i, n, t;
	vec3_t start, end;
	aas_trace_t trace;

	//if the area has no reachabilities
	if (!AAS_AreaReachability(areanum)) return qfalse;
	//
	n = aasworld.numareas * random();
	for (i = 0; i < aasworld.numareas; i++)
	{
		if (n <= 0) n = 1;
		if (n >= aasworld.numareas) n = 1;
		if (AAS_AreaReachability(n))
		{
			t = AAS_AreaTravelTimeToGoalArea(areanum, aasworld.areas[areanum].center, n, travelflags);
			//if the goal is reachable
			if (t > 0)
			{
				if (AAS_AreaSwim(n))
				{
					*goalareanum = n;
					VectorCopy(aasworld.areas[n].center, goalorigin);
					//botimport.Print(PRT_MESSAGE, "found random goal area %d\n", *goalareanum);
					return qtrue;
				} //end if
				VectorCopy(aasworld.areas[n].center, start);
				if (!AAS_PointAreaNum(start))
					Log_Write("area %d center %f %f %f in solid?", n, start[0], start[1], start[2]);
				VectorCopy(start, end);
				end[2] -= 300;
				trace = AAS_TraceClientBBox(start, end, PRESENCE_CROUCH, -1);
				if (!trace.startsolid && trace.fraction < 1 && AAS_PointAreaNum(trace.endpos) == n)
				{
					if (AAS_AreaGroundFaceArea(n) > 300)
					{
						*goalareanum = n;
						VectorCopy(trace.endpos, goalorigin);
						//botimport.Print(PRT_MESSAGE, "found random goal area %d\n", *goalareanum);
						return qtrue;
					} //end if
				} //end if
			} //end if
		} //end if
		n++;
	} //end for
	return qfalse;
}