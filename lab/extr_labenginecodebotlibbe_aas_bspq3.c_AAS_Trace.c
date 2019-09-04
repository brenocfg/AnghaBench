#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
typedef  int /*<<< orphan*/  bsp_trace_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* Trace ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ;} ;

/* Variables and functions */
 TYPE_1__ botimport ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

bsp_trace_t AAS_Trace(vec3_t start, vec3_t mins, vec3_t maxs, vec3_t end, int passent, int contentmask)
{
	bsp_trace_t bsptrace;
	botimport.Trace(&bsptrace, start, mins, maxs, end, passent, contentmask);
	return bsptrace;
}