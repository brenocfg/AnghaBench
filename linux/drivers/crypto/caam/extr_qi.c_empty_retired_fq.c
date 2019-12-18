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
struct qman_portal {int dummy; } ;
struct qman_fq {int flags; int /*<<< orphan*/  fqid; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int QMAN_FQ_STATE_NE ; 
 int QMAN_VOLATILE_FLAG_FINISH ; 
 int QMAN_VOLATILE_FLAG_WAIT_INT ; 
 int QM_VDQCR_NUMFRAMES_TILLEMPTY ; 
 int QM_VDQCR_PRECEDENCE_VDQCR ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct qman_portal* qman_get_affine_portal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qman_p_poll_dqrr (struct qman_portal*,int) ; 
 int qman_volatile_dequeue (struct qman_fq*,int,int) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static int empty_retired_fq(struct device *qidev, struct qman_fq *fq)
{
	int ret;

	ret = qman_volatile_dequeue(fq, QMAN_VOLATILE_FLAG_WAIT_INT |
				    QMAN_VOLATILE_FLAG_FINISH,
				    QM_VDQCR_PRECEDENCE_VDQCR |
				    QM_VDQCR_NUMFRAMES_TILLEMPTY);
	if (ret) {
		dev_err(qidev, "Volatile dequeue fail for FQ: %u\n", fq->fqid);
		return ret;
	}

	do {
		struct qman_portal *p;

		p = qman_get_affine_portal(smp_processor_id());
		qman_p_poll_dqrr(p, 16);
	} while (fq->flags & QMAN_FQ_STATE_NE);

	return 0;
}