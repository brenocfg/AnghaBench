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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int /*<<< orphan*/  num_vlan_filters; } ;
struct TYPE_4__ {TYPE_1__ resc; } ;
struct ecore_vf_iov {TYPE_2__ acquire_resp; } ;
struct ecore_hwfn {struct ecore_vf_iov* vf_iov_info; } ;

/* Variables and functions */

void ecore_vf_get_num_vlan_filters(struct ecore_hwfn *p_hwfn,
				   u8 *num_vlan_filters)
{
	struct ecore_vf_iov *p_vf;

	p_vf = p_hwfn->vf_iov_info;
	*num_vlan_filters = p_vf->acquire_resp.resc.num_vlan_filters;
}