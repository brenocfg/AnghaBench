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
struct ecore_iwarp_cm_info {int /*<<< orphan*/  ird; int /*<<< orphan*/  ord; int /*<<< orphan*/  private_data_len; int /*<<< orphan*/  vlan; int /*<<< orphan*/  local_port; int /*<<< orphan*/  remote_port; int /*<<< orphan*/ * local_ip; int /*<<< orphan*/ * remote_ip; int /*<<< orphan*/  ip_version; } ;
struct ecore_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ECORE_MSG_RDMA ; 

__attribute__((used)) static void
ecore_iwarp_print_cm_info(struct ecore_hwfn *p_hwfn,
			  struct ecore_iwarp_cm_info *cm_info)
{
	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "ip_version = %d\n",
		   cm_info->ip_version);
	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "remote_ip %x.%x.%x.%x\n",
		   cm_info->remote_ip[0],
		   cm_info->remote_ip[1],
		   cm_info->remote_ip[2],
		   cm_info->remote_ip[3]);
	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "local_ip %x.%x.%x.%x\n",
		   cm_info->local_ip[0],
		   cm_info->local_ip[1],
		   cm_info->local_ip[2],
		   cm_info->local_ip[3]);
	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "remote_port = %x\n",
		   cm_info->remote_port);
	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "local_port = %x\n",
		   cm_info->local_port);
	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "vlan = %x\n",
		   cm_info->vlan);
	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "private_data_len = %x\n",
		   cm_info->private_data_len);
	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "ord = %d\n",
		   cm_info->ord);
	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "ird = %d\n",
		   cm_info->ird);
}