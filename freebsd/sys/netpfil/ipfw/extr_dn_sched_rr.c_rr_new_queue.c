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
typedef  unsigned long long uint64_t ;
struct rr_si {int dummy; } ;
struct rr_queue {unsigned long long quantum; unsigned long long credit; scalar_t__ status; } ;
struct TYPE_10__ {int /*<<< orphan*/ * head; } ;
struct TYPE_6__ {int /*<<< orphan*/  subtype; } ;
struct TYPE_7__ {TYPE_1__ oid; } ;
struct dn_queue {scalar_t__ _si; TYPE_5__ mq; TYPE_4__* fs; TYPE_2__ ni; } ;
struct TYPE_8__ {unsigned long long* par; } ;
struct TYPE_9__ {TYPE_3__ fs; } ;

/* Variables and functions */
 int /*<<< orphan*/  D (char*) ; 
 int /*<<< orphan*/  DN_SCHED_RR ; 
 int /*<<< orphan*/  ND (char*,unsigned long long) ; 
 int /*<<< orphan*/  rr_append (struct rr_queue*,struct rr_si*) ; 

__attribute__((used)) static int
rr_new_queue(struct dn_queue *_q)
{
	struct rr_queue *q = (struct rr_queue *)_q;
	uint64_t quantum;

	_q->ni.oid.subtype = DN_SCHED_RR;

	quantum = (uint64_t)_q->fs->fs.par[0] * _q->fs->fs.par[1];
	if (quantum >= (1ULL<< 32)) {
		D("quantum too large, truncating to 4G - 1");
		quantum = (1ULL<< 32) - 1;
	}
	q->quantum = quantum;
	ND("called, q->quantum %d", q->quantum);
	q->credit = q->quantum;
	q->status = 0;

	if (_q->mq.head != NULL) {
		/* Queue NOT empty, insert in the queue list */
		rr_append(q, (struct rr_si *)(_q->_si + 1));
	}
	return 0;
}