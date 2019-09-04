#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_3__ {int areanum; struct TYPE_3__* next; } ;
typedef  TYPE_1__ aas_lreachability_t ;

/* Variables and functions */
 TYPE_1__** areareachability ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean AAS_ReachabilityExists(int area1num, int area2num)
{
	aas_lreachability_t *r;

	for (r = areareachability[area1num]; r; r = r->next)
	{
		if (r->areanum == area2num) return qtrue;
	} //end for
	return qfalse;
}