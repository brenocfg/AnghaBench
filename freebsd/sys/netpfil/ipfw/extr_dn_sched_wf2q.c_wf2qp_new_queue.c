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
struct wf2qp_queue {int inv_w; scalar_t__ F; scalar_t__ S; } ;
struct TYPE_8__ {int /*<<< orphan*/ * head; } ;
struct TYPE_9__ {int /*<<< orphan*/  subtype; } ;
struct TYPE_10__ {TYPE_4__ oid; } ;
struct dn_queue {TYPE_3__ mq; int /*<<< orphan*/  _si; TYPE_2__* fs; TYPE_5__ ni; } ;
struct TYPE_6__ {int* par; } ;
struct TYPE_7__ {TYPE_1__ fs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DN_SCHED_WF2QP ; 
 int ONE_FP ; 
 int /*<<< orphan*/  wf2qp_enqueue (int /*<<< orphan*/ ,struct dn_queue*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
wf2qp_new_queue(struct dn_queue *_q)
{
	struct wf2qp_queue *q = (struct wf2qp_queue *)_q;

	_q->ni.oid.subtype = DN_SCHED_WF2QP;
	q->F = 0;	/* not strictly necessary */
	q->S = q->F + 1;    /* mark timestamp as invalid. */
        q->inv_w = ONE_FP / _q->fs->fs.par[0];
	if (_q->mq.head != NULL) {
		wf2qp_enqueue(_q->_si, _q, _q->mq.head);
	}
	return 0;
}