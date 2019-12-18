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
struct mthca_dev {int /*<<< orphan*/  doorbell_lock; scalar_t__ kar; } ;
struct mthca_cq {int cqn; int /*<<< orphan*/  cons_index; int /*<<< orphan*/ * set_ci_db; } ;

/* Variables and functions */
 scalar_t__ MTHCA_CQ_DOORBELL ; 
 int /*<<< orphan*/  MTHCA_GET_DOORBELL_LOCK (int /*<<< orphan*/ *) ; 
 int MTHCA_TAVOR_CQ_DB_INC_CI ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmiowb () ; 
 scalar_t__ mthca_is_memfree (struct mthca_dev*) ; 
 int /*<<< orphan*/  mthca_write64 (int,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline void update_cons_index(struct mthca_dev *dev, struct mthca_cq *cq,
				     int incr)
{
	if (mthca_is_memfree(dev)) {
		*cq->set_ci_db = cpu_to_be32(cq->cons_index);
		wmb();
	} else {
		mthca_write64(MTHCA_TAVOR_CQ_DB_INC_CI | cq->cqn, incr - 1,
			      dev->kar + MTHCA_CQ_DOORBELL,
			      MTHCA_GET_DOORBELL_LOCK(&dev->doorbell_lock));
		/*
		 * Make sure doorbells don't leak out of CQ spinlock
		 * and reach the HCA out of order:
		 */
		mmiowb();
	}
}