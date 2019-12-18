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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct xive_q {unsigned int msk; unsigned long eoi_phys; int /*<<< orphan*/ * qpage; scalar_t__ toggle; scalar_t__ idx; } ;
typedef  int s64 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ XIVE_EQ_ALWAYS_NOTIFY ; 
 scalar_t__ __pa (int /*<<< orphan*/ *) ; 
 int plpar_int_get_queue_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*,unsigned long*) ; 
 int plpar_int_set_queue_config (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xive_spapr_configure_queue(u32 target, struct xive_q *q, u8 prio,
				   __be32 *qpage, u32 order)
{
	s64 rc = 0;
	unsigned long esn_page;
	unsigned long esn_size;
	u64 flags, qpage_phys;

	/* If there's an actual queue page, clean it */
	if (order) {
		if (WARN_ON(!qpage))
			return -EINVAL;
		qpage_phys = __pa(qpage);
	} else {
		qpage_phys = 0;
	}

	/* Initialize the rest of the fields */
	q->msk = order ? ((1u << (order - 2)) - 1) : 0;
	q->idx = 0;
	q->toggle = 0;

	rc = plpar_int_get_queue_info(0, target, prio, &esn_page, &esn_size);
	if (rc) {
		pr_err("Error %lld getting queue info CPU %d prio %d\n", rc,
		       target, prio);
		rc = -EIO;
		goto fail;
	}

	/* TODO: add support for the notification page */
	q->eoi_phys = esn_page;

	/* Default is to always notify */
	flags = XIVE_EQ_ALWAYS_NOTIFY;

	/* Configure and enable the queue in HW */
	rc = plpar_int_set_queue_config(flags, target, prio, qpage_phys, order);
	if (rc) {
		pr_err("Error %lld setting queue for CPU %d prio %d\n", rc,
		       target, prio);
		rc = -EIO;
	} else {
		q->qpage = qpage;
	}
fail:
	return rc;
}