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
typedef  int /*<<< orphan*/  ibnd_fabric_t ;

/* Variables and functions */
 int DIFF_FLAG_CA ; 
 int DIFF_FLAG_ROUTER ; 
 int DIFF_FLAG_SWITCH ; 
 int /*<<< orphan*/  IB_NODE_CA ; 
 int /*<<< orphan*/  IB_NODE_ROUTER ; 
 int /*<<< orphan*/  IB_NODE_SWITCH ; 
 int /*<<< orphan*/  diff_common (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int diffcheck_flags ; 
 int /*<<< orphan*/  out_ca ; 
 int /*<<< orphan*/  out_ca_detail ; 
 int /*<<< orphan*/  out_ca_port ; 
 int /*<<< orphan*/  out_switch ; 
 int /*<<< orphan*/  out_switch_detail ; 
 int /*<<< orphan*/  out_switch_port ; 

int diff(ibnd_fabric_t * orig_fabric, ibnd_fabric_t * new_fabric)
{
	if (diffcheck_flags & DIFF_FLAG_SWITCH)
		diff_common(orig_fabric, new_fabric, IB_NODE_SWITCH,
			    diffcheck_flags, out_switch, out_switch_detail,
			    out_switch_port);

	if (diffcheck_flags & DIFF_FLAG_CA)
		diff_common(orig_fabric, new_fabric, IB_NODE_CA,
			    diffcheck_flags, out_ca, out_ca_detail,
			    out_ca_port);

	if (diffcheck_flags & DIFF_FLAG_ROUTER)
		diff_common(orig_fabric, new_fabric, IB_NODE_ROUTER,
			    diffcheck_flags, out_ca, out_ca_detail,
			    out_ca_port);

	return 0;
}