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
typedef  int* vec3_t ;
struct TYPE_6__ {double fraction; int* endpos; int /*<<< orphan*/  planenum; scalar_t__ startsolid; } ;
typedef  TYPE_1__ aas_trace_t ;
struct TYPE_7__ {int /*<<< orphan*/  normal; } ;
typedef  TYPE_2__ aas_plane_t ;
struct TYPE_8__ {scalar_t__ phys_maxsteepness; } ;

/* Variables and functions */
 TYPE_2__* AAS_PlaneFromNum (int /*<<< orphan*/ ) ; 
 TYPE_1__ AAS_TraceClientBBox (int*,int*,int,int) ; 
 scalar_t__ DotProduct (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  VectorCopy (int*,int*) ; 
 TYPE_3__ aassettings ; 
 int qfalse ; 
 int qtrue ; 

int AAS_OnGround(vec3_t origin, int presencetype, int passent)
{
	aas_trace_t trace;
	vec3_t end, up = {0, 0, 1};
	aas_plane_t *plane;

	VectorCopy(origin, end);
	end[2] -= 10;

	trace = AAS_TraceClientBBox(origin, end, presencetype, passent);

	//if in solid
	if (trace.startsolid) return qfalse;
	//if nothing hit at all
	if (trace.fraction >= 1.0) return qfalse;
	//if too far from the hit plane
	if (origin[2] - trace.endpos[2] > 10) return qfalse;
	//check if the plane isn't too steep
	plane = AAS_PlaneFromNum(trace.planenum);
	if (DotProduct(plane->normal, up) < aassettings.phys_maxsteepness) return qfalse;
	//the bot is on the ground
	return qtrue;
}