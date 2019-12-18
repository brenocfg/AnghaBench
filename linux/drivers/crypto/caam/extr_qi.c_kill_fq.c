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
typedef  int /*<<< orphan*/  u32 ;
struct qman_fq {scalar_t__ state; int flags; int fqid; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int QMAN_FQ_STATE_BLOCKOOS ; 
 int QMAN_FQ_STATE_NE ; 
 int QMAN_FQ_STATE_ORL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int empty_retired_fq (struct device*,struct qman_fq*) ; 
 int /*<<< orphan*/  kfree (struct qman_fq*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  qman_destroy_fq (struct qman_fq*) ; 
 scalar_t__ qman_fq_state_retired ; 
 int qman_oos_fq (struct qman_fq*) ; 
 int qman_retire_fq (struct qman_fq*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kill_fq(struct device *qidev, struct qman_fq *fq)
{
	u32 flags;
	int ret;

	ret = qman_retire_fq(fq, &flags);
	if (ret < 0) {
		dev_err(qidev, "qman_retire_fq failed: %d\n", ret);
		return ret;
	}

	if (!ret)
		goto empty_fq;

	/* Async FQ retirement condition */
	if (ret == 1) {
		/* Retry till FQ gets in retired state */
		do {
			msleep(20);
		} while (fq->state != qman_fq_state_retired);

		WARN_ON(fq->flags & QMAN_FQ_STATE_BLOCKOOS);
		WARN_ON(fq->flags & QMAN_FQ_STATE_ORL);
	}

empty_fq:
	if (fq->flags & QMAN_FQ_STATE_NE) {
		ret = empty_retired_fq(qidev, fq);
		if (ret) {
			dev_err(qidev, "empty_retired_fq fail for FQ: %u\n",
				fq->fqid);
			return ret;
		}
	}

	ret = qman_oos_fq(fq);
	if (ret)
		dev_err(qidev, "OOS of FQID: %u failed\n", fq->fqid);

	qman_destroy_fq(fq);
	kfree(fq);

	return ret;
}