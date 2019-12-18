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
struct rq_depth {int max_depth; scalar_t__ scale_step; int scaled_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  rq_depth_calc_max_depth (struct rq_depth*) ; 

bool rq_depth_scale_down(struct rq_depth *rqd, bool hard_throttle)
{
	/*
	 * Stop scaling down when we've hit the limit. This also prevents
	 * ->scale_step from going to crazy values, if the device can't
	 * keep up.
	 */
	if (rqd->max_depth == 1)
		return false;

	if (rqd->scale_step < 0 && hard_throttle)
		rqd->scale_step = 0;
	else
		rqd->scale_step++;

	rqd->scaled_max = false;
	rq_depth_calc_max_depth(rqd);
	return true;
}