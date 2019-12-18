#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  float* vec3_t ;
typedef  int /*<<< orphan*/  trace_t ;
struct TYPE_8__ {int* absmin; int* absmax; } ;
struct TYPE_11__ {int count; TYPE_3__* client; TYPE_1__ r; } ;
typedef  TYPE_4__ gentity_t ;
struct TYPE_9__ {int /*<<< orphan*/  origin; } ;
struct TYPE_10__ {TYPE_2__ ps; } ;

/* Variables and functions */
 int /*<<< orphan*/  TeleportPlayer (TYPE_4__*,float*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,float*) ; 
 scalar_t__ fabs (float) ; 
 int /*<<< orphan*/  tv (double,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Touch_DoorTriggerSpectator( gentity_t *ent, gentity_t *other, trace_t *trace ) {
	int axis;
	float doorMin, doorMax;
	vec3_t origin;

	axis = ent->count;
	// the constants below relate to constants in Think_SpawnNewDoorTrigger()
	doorMin = ent->r.absmin[axis] + 100;
	doorMax = ent->r.absmax[axis] - 100;

	VectorCopy(other->client->ps.origin, origin);

	if (origin[axis] < doorMin || origin[axis] > doorMax) return;

	if (fabs(origin[axis] - doorMax) < fabs(origin[axis] - doorMin)) {
		origin[axis] = doorMin - 10;
	} else {
		origin[axis] = doorMax + 10;
	}

	TeleportPlayer(other, origin, tv(10000000.0, 0, 0));
}