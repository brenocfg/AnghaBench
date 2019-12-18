#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_9__ {int /*<<< orphan*/  type; int /*<<< orphan*/  signbits; int /*<<< orphan*/  normal; int /*<<< orphan*/  dist; } ;
struct TYPE_11__ {int /*<<< orphan*/  surfaceFlags; int /*<<< orphan*/  startsolid; TYPE_2__ plane; int /*<<< orphan*/  fraction; int /*<<< orphan*/  entityNum; int /*<<< orphan*/  endpos; int /*<<< orphan*/  contents; int /*<<< orphan*/  allsolid; } ;
typedef  TYPE_4__ trace_t ;
struct TYPE_10__ {int /*<<< orphan*/  flags; } ;
struct TYPE_8__ {int /*<<< orphan*/  type; int /*<<< orphan*/  signbits; int /*<<< orphan*/  normal; int /*<<< orphan*/  dist; } ;
struct TYPE_12__ {TYPE_3__ surface; int /*<<< orphan*/  startsolid; scalar_t__ sidenum; TYPE_1__ plane; scalar_t__ exp_dist; int /*<<< orphan*/  fraction; int /*<<< orphan*/  ent; int /*<<< orphan*/  endpos; int /*<<< orphan*/  contents; int /*<<< orphan*/  allsolid; } ;
typedef  TYPE_5__ bsp_trace_t ;

/* Variables and functions */
 int /*<<< orphan*/  CM_BoxTrace (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  capsule_collision ; 
 int /*<<< orphan*/  worldmodel ; 

void BotImport_Trace(bsp_trace_t *bsptrace, vec3_t start, vec3_t mins, vec3_t maxs, vec3_t end, int passent, int contentmask)
{
	trace_t result;

	CM_BoxTrace(&result, start, end, mins, maxs, worldmodel, contentmask, capsule_collision);

	bsptrace->allsolid = result.allsolid;
	bsptrace->contents = result.contents;
	VectorCopy(result.endpos, bsptrace->endpos);
	bsptrace->ent = result.entityNum;
	bsptrace->fraction = result.fraction;
	bsptrace->exp_dist = 0;
	bsptrace->plane.dist = result.plane.dist;
	VectorCopy(result.plane.normal, bsptrace->plane.normal);
	bsptrace->plane.signbits = result.plane.signbits;
	bsptrace->plane.type = result.plane.type;
	bsptrace->sidenum = 0;
	bsptrace->startsolid = result.startsolid;
	bsptrace->surface.flags = result.surfaceFlags;
}