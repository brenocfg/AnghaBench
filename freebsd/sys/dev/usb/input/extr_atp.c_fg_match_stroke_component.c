#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct TYPE_5__ {int loc; int cum_pressure; int max_cum_pressure; int delta_mickeys; } ;
typedef  TYPE_1__ fg_stroke_component_t ;
struct TYPE_6__ {int loc; int cum; } ;
typedef  TYPE_2__ fg_pspan ;
typedef  int boolean_t ;
typedef  scalar_t__ atp_stroke_type ;

/* Variables and functions */
 scalar_t__ ATP_STROKE_TOUCH ; 
 scalar_t__ FG_MAX_DELTA_MICKEYS ; 
 int abs (int) ; 

__attribute__((used)) static boolean_t
fg_match_stroke_component(fg_stroke_component_t *component,
    const fg_pspan *pspan, atp_stroke_type stroke_type)
{
	int   delta_mickeys;
	u_int min_pressure;

	delta_mickeys = pspan->loc - component->loc;

	if (abs(delta_mickeys) > (int)FG_MAX_DELTA_MICKEYS)
		return (false); /* the finger span is too far out; no match */

	component->loc = pspan->loc;

	/*
	 * A sudden and significant increase in a pspan's cumulative
	 * pressure indicates the incidence of a new finger
	 * contact. This usually revises the pspan's
	 * centre-of-gravity, and hence the location of any/all
	 * matching stroke component(s). But such a change should
	 * *not* be interpreted as a movement.
	 */
	if (pspan->cum > ((3 * component->cum_pressure) >> 1))
		delta_mickeys = 0;

	component->cum_pressure = pspan->cum;
	if (pspan->cum > component->max_cum_pressure)
		component->max_cum_pressure = pspan->cum;

	/*
	 * Disregard the component's movement if its cumulative
	 * pressure drops below a fraction of the maximum; this
	 * fraction is determined based on the stroke's type.
	 */
	if (stroke_type == ATP_STROKE_TOUCH)
		min_pressure = (3 * component->max_cum_pressure) >> 2;
	else
		min_pressure = component->max_cum_pressure >> 2;
	if (component->cum_pressure < min_pressure)
		delta_mickeys = 0;

	component->delta_mickeys = delta_mickeys;
	return (true);
}