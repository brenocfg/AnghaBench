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
struct t4_cq {scalar_t__ sw_in_use; scalar_t__ size; int error; scalar_t__ sw_pidx; int /*<<< orphan*/  cqid; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_NOTICE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void t4_swcq_produce(struct t4_cq *cq)
{
	cq->sw_in_use++;
	if (cq->sw_in_use == cq->size) {
		syslog(LOG_NOTICE, "cxgb4 sw cq overflow cqid %u\n", cq->cqid);
		cq->error = 1;
		assert(0);
	}
	if (++cq->sw_pidx == cq->size)
		cq->sw_pidx = 0;
}