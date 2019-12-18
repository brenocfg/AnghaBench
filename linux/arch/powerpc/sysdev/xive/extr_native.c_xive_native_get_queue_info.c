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
typedef  void* u64 ;
typedef  void* u32 ;
typedef  scalar_t__ s64 ;
typedef  int /*<<< orphan*/  __be64 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EIO ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 void* be64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ opal_xive_get_queue_info (void*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,void*,void*,scalar_t__) ; 

int xive_native_get_queue_info(u32 vp_id, u32 prio,
			       u64 *out_qpage,
			       u64 *out_qsize,
			       u64 *out_qeoi_page,
			       u32 *out_escalate_irq,
			       u64 *out_qflags)
{
	__be64 qpage;
	__be64 qsize;
	__be64 qeoi_page;
	__be32 escalate_irq;
	__be64 qflags;
	s64 rc;

	rc = opal_xive_get_queue_info(vp_id, prio, &qpage, &qsize,
				      &qeoi_page, &escalate_irq, &qflags);
	if (rc) {
		pr_err("OPAL failed to get queue info for VCPU %d/%d : %lld\n",
		       vp_id, prio, rc);
		return -EIO;
	}

	if (out_qpage)
		*out_qpage = be64_to_cpu(qpage);
	if (out_qsize)
		*out_qsize = be32_to_cpu(qsize);
	if (out_qeoi_page)
		*out_qeoi_page = be64_to_cpu(qeoi_page);
	if (out_escalate_irq)
		*out_escalate_irq = be32_to_cpu(escalate_irq);
	if (out_qflags)
		*out_qflags = be64_to_cpu(qflags);

	return 0;
}