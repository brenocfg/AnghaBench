#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {float fraction; } ;
typedef  TYPE_1__ trace_t ;
struct TYPE_5__ {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTENTS_SOLID ; 
 int /*<<< orphan*/  ENTITYNUM_NONE ; 
 scalar_t__ SS_GAME ; 
 int /*<<< orphan*/  SV_Trace (TYPE_1__*,float const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,float const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfalse ; 
 TYPE_2__ sv ; 

float dmlab_raycast(const float start[3], const float end[3]) {
	if ( sv.state != SS_GAME ) {
		return 0.0f;
	}
	trace_t results;
	SV_Trace(&results, start, NULL, NULL, end, ENTITYNUM_NONE, CONTENTS_SOLID, qfalse);
	return results.fraction;
}