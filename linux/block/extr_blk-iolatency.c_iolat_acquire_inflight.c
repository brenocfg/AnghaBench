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
struct rq_wait {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  max_depth; } ;
struct iolatency_grp {TYPE_1__ rq_depth; } ;

/* Variables and functions */
 int rq_wait_inc_below (struct rq_wait*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool iolat_acquire_inflight(struct rq_wait *rqw, void *private_data)
{
	struct iolatency_grp *iolat = private_data;
	return rq_wait_inc_below(rqw, iolat->rq_depth.max_depth);
}