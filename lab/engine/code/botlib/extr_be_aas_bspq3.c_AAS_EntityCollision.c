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
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_7__ {scalar_t__ fraction; } ;
typedef  TYPE_1__ bsp_trace_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* EntityTrace ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 TYPE_3__ botimport ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

qboolean AAS_EntityCollision(int entnum,
					vec3_t start, vec3_t boxmins, vec3_t boxmaxs, vec3_t end,
								int contentmask, bsp_trace_t *trace)
{
	bsp_trace_t enttrace;

	botimport.EntityTrace(&enttrace, start, boxmins, boxmaxs, end, entnum, contentmask);
	if (enttrace.fraction < trace->fraction)
	{
		Com_Memcpy(trace, &enttrace, sizeof(bsp_trace_t));
		return qtrue;
	} //end if
	return qfalse;
}