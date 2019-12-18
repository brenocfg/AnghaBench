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
struct TYPE_2__ {scalar_t__* now; } ;
struct worker {scalar_t__ err_limit_time; int err_limit_count; TYPE_1__ env; } ;

/* Variables and functions */
 scalar_t__ ERROR_RATELIMIT ; 

__attribute__((used)) static int
worker_err_ratelimit(struct worker* worker, int err)
{
	if(worker->err_limit_time == *worker->env.now) {
		/* see if limit is exceeded for this second */
		if(worker->err_limit_count++ > ERROR_RATELIMIT)
			return -1;
	} else {
		/* new second, new limits */
		worker->err_limit_time = *worker->env.now;
		worker->err_limit_count = 1;
	}
	return err;
}