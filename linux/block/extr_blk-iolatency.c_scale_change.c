#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned long max_depth; } ;
struct TYPE_6__ {int /*<<< orphan*/  wait; } ;
struct iolatency_grp {TYPE_2__ rq_depth; TYPE_1__ rq_wait; TYPE_5__* blkiolat; } ;
struct TYPE_9__ {TYPE_3__* q; } ;
struct TYPE_10__ {TYPE_4__ rqos; } ;
struct TYPE_8__ {unsigned long nr_requests; } ;

/* Variables and functions */
 scalar_t__ blkcg_unuse_delay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lat_to_blkg (struct iolatency_grp*) ; 
 unsigned long max (unsigned long,unsigned long) ; 
 unsigned long min (unsigned long,unsigned long) ; 
 unsigned long scale_amount (unsigned long,int) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void scale_change(struct iolatency_grp *iolat, bool up)
{
	unsigned long qd = iolat->blkiolat->rqos.q->nr_requests;
	unsigned long scale = scale_amount(qd, up);
	unsigned long old = iolat->rq_depth.max_depth;

	if (old > qd)
		old = qd;

	if (up) {
		if (old == 1 && blkcg_unuse_delay(lat_to_blkg(iolat)))
			return;

		if (old < qd) {
			old += scale;
			old = min(old, qd);
			iolat->rq_depth.max_depth = old;
			wake_up_all(&iolat->rq_wait.wait);
		}
	} else {
		old >>= 1;
		iolat->rq_depth.max_depth = max(old, 1UL);
	}
}