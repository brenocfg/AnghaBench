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
typedef  scalar_t__ s64 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ opal_xive_get_queue_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

int xive_native_get_queue_state(u32 vp_id, u32 prio, u32 *qtoggle, u32 *qindex)
{
	__be32 opal_qtoggle;
	__be32 opal_qindex;
	s64 rc;

	rc = opal_xive_get_queue_state(vp_id, prio, &opal_qtoggle,
				       &opal_qindex);
	if (rc) {
		pr_err("OPAL failed to get queue state for VCPU %d/%d : %lld\n",
		       vp_id, prio, rc);
		return -EIO;
	}

	if (qtoggle)
		*qtoggle = be32_to_cpu(opal_qtoggle);
	if (qindex)
		*qindex = be32_to_cpu(opal_qindex);

	return 0;
}