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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct xive_q {unsigned int msk; int /*<<< orphan*/ * qpage; int /*<<< orphan*/  esc_irq; int /*<<< orphan*/  eoi_phys; scalar_t__ toggle; scalar_t__ idx; } ;
typedef  int s64 ;
typedef  int /*<<< orphan*/  __be64 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int OPAL_BUSY ; 
 int /*<<< orphan*/  OPAL_BUSY_DELAY_MS ; 
 int OPAL_XIVE_EQ_ALWAYS_NOTIFY ; 
 int OPAL_XIVE_EQ_ENABLED ; 
 int OPAL_XIVE_EQ_ESCALATE ; 
 scalar_t__ WARN_ON (int) ; 
 int __pa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int opal_xive_get_queue_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int opal_xive_set_queue_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

int xive_native_configure_queue(u32 vp_id, struct xive_q *q, u8 prio,
				__be32 *qpage, u32 order, bool can_escalate)
{
	s64 rc = 0;
	__be64 qeoi_page_be;
	__be32 esc_irq_be;
	u64 flags, qpage_phys;

	/* If there's an actual queue page, clean it */
	if (order) {
		if (WARN_ON(!qpage))
			return -EINVAL;
		qpage_phys = __pa(qpage);
	} else
		qpage_phys = 0;

	/* Initialize the rest of the fields */
	q->msk = order ? ((1u << (order - 2)) - 1) : 0;
	q->idx = 0;
	q->toggle = 0;

	rc = opal_xive_get_queue_info(vp_id, prio, NULL, NULL,
				      &qeoi_page_be,
				      &esc_irq_be,
				      NULL);
	if (rc) {
		pr_err("Error %lld getting queue info prio %d\n", rc, prio);
		rc = -EIO;
		goto fail;
	}
	q->eoi_phys = be64_to_cpu(qeoi_page_be);

	/* Default flags */
	flags = OPAL_XIVE_EQ_ALWAYS_NOTIFY | OPAL_XIVE_EQ_ENABLED;

	/* Escalation needed ? */
	if (can_escalate) {
		q->esc_irq = be32_to_cpu(esc_irq_be);
		flags |= OPAL_XIVE_EQ_ESCALATE;
	}

	/* Configure and enable the queue in HW */
	for (;;) {
		rc = opal_xive_set_queue_info(vp_id, prio, qpage_phys, order, flags);
		if (rc != OPAL_BUSY)
			break;
		msleep(OPAL_BUSY_DELAY_MS);
	}
	if (rc) {
		pr_err("Error %lld setting queue for prio %d\n", rc, prio);
		rc = -EIO;
	} else {
		/*
		 * KVM code requires all of the above to be visible before
		 * q->qpage is set due to how it manages IPI EOIs
		 */
		wmb();
		q->qpage = qpage;
	}
fail:
	return rc;
}