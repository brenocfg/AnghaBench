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
typedef  int u32 ;
struct ib_cq {int /*<<< orphan*/  device; } ;
typedef  enum ib_cq_notify_flags { ____Placeholder_ib_cq_notify_flags } ib_cq_notify_flags ;
struct TYPE_4__ {int cqn; } ;
struct TYPE_3__ {int /*<<< orphan*/  doorbell_lock; scalar_t__ kar; } ;

/* Variables and functions */
 int IB_CQ_SOLICITED ; 
 int IB_CQ_SOLICITED_MASK ; 
 scalar_t__ MTHCA_CQ_DOORBELL ; 
 int /*<<< orphan*/  MTHCA_GET_DOORBELL_LOCK (int /*<<< orphan*/ *) ; 
 int MTHCA_TAVOR_CQ_DB_REQ_NOT ; 
 int MTHCA_TAVOR_CQ_DB_REQ_NOT_SOL ; 
 int /*<<< orphan*/  mthca_write64 (int,int,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_2__* to_mcq (struct ib_cq*) ; 
 TYPE_1__* to_mdev (int /*<<< orphan*/ ) ; 

int mthca_tavor_arm_cq(struct ib_cq *cq, enum ib_cq_notify_flags flags)
{
	u32 dbhi = ((flags & IB_CQ_SOLICITED_MASK) == IB_CQ_SOLICITED ?
		    MTHCA_TAVOR_CQ_DB_REQ_NOT_SOL :
		    MTHCA_TAVOR_CQ_DB_REQ_NOT) |
		to_mcq(cq)->cqn;

	mthca_write64(dbhi, 0xffffffff, to_mdev(cq->device)->kar + MTHCA_CQ_DOORBELL,
		      MTHCA_GET_DOORBELL_LOCK(&to_mdev(cq->device)->doorbell_lock));

	return 0;
}