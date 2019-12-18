#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dn_sch_inst {TYPE_2__* sched; } ;
struct TYPE_3__ {int /*<<< orphan*/  oid; } ;
struct dn_queue {int /*<<< orphan*/  fs; struct dn_sch_inst* _si; TYPE_1__ ni; } ;
struct TYPE_4__ {int /*<<< orphan*/  fs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DN_QUEUE ; 
 int /*<<< orphan*/  set_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
fifo_new_sched(struct dn_sch_inst *si)
{
	/* This scheduler instance contains the queue */
	struct dn_queue *q = (struct dn_queue *)(si + 1);

        set_oid(&q->ni.oid, DN_QUEUE, sizeof(*q));
	q->_si = si;
	q->fs = si->sched->fs;
	return 0;
}