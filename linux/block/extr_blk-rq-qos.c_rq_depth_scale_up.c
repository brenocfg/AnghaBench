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
struct rq_depth {scalar_t__ scaled_max; int /*<<< orphan*/  scale_step; } ;

/* Variables and functions */
 scalar_t__ rq_depth_calc_max_depth (struct rq_depth*) ; 

bool rq_depth_scale_up(struct rq_depth *rqd)
{
	/*
	 * Hit max in previous round, stop here
	 */
	if (rqd->scaled_max)
		return false;

	rqd->scale_step--;

	rqd->scaled_max = rq_depth_calc_max_depth(rqd);
	return true;
}