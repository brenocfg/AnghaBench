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
typedef  size_t u16 ;
struct t4_cqe {scalar_t__ bits_type_ts; } ;
struct t4_cq {int cidx; size_t size; scalar_t__ bits_type_ts; int error; struct t4_cqe* queue; int /*<<< orphan*/  cqid; } ;

/* Variables and functions */
 int ENODATA ; 
 int EOVERFLOW ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ t4_valid_cqe (struct t4_cq*,struct t4_cqe*) ; 
 int /*<<< orphan*/  udma_from_device_barrier () ; 

__attribute__((used)) static inline int t4_next_hw_cqe(struct t4_cq *cq, struct t4_cqe **cqe)
{
	int ret;
	u16 prev_cidx;

	if (cq->cidx == 0)
		prev_cidx = cq->size - 1;
	else
		prev_cidx = cq->cidx - 1;

	if (cq->queue[prev_cidx].bits_type_ts != cq->bits_type_ts) {
		ret = -EOVERFLOW;
		syslog(LOG_NOTICE, "cxgb4 cq overflow cqid %u\n", cq->cqid);
		cq->error = 1;
		assert(0);
	} else if (t4_valid_cqe(cq, &cq->queue[cq->cidx])) {
		udma_from_device_barrier();
		*cqe = &cq->queue[cq->cidx];
		ret = 0;
	} else
		ret = -ENODATA;
	return ret;
}