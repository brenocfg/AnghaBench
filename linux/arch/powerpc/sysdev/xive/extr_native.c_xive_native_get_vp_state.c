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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ s64 ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ opal_xive_get_vp_state (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,scalar_t__) ; 

int xive_native_get_vp_state(u32 vp_id, u64 *out_state)
{
	__be64 state;
	s64 rc;

	rc = opal_xive_get_vp_state(vp_id, &state);
	if (rc) {
		pr_err("OPAL failed to get vp state for VCPU %d : %lld\n",
		       vp_id, rc);
		return -EIO;
	}

	if (out_state)
		*out_state = be64_to_cpu(state);
	return 0;
}