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
typedef  union ib_gid {int dummy; } ib_gid ;
typedef  int u16 ;
struct ib_gid_attr {scalar_t__ gid_type; int /*<<< orphan*/  ndev; } ;
struct find_gid_index_context {scalar_t__ gid_type; int vlan_id; } ;

/* Variables and functions */
 int rdma_vlan_dev_vlan_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool find_gid_index(const union ib_gid *gid,
			   const struct ib_gid_attr *gid_attr,
			   void *context)
{
	u16 vlan_diff;
	struct find_gid_index_context *ctx =
		(struct find_gid_index_context *)context;

	if (ctx->gid_type != gid_attr->gid_type)
		return false;

	/*
	 * The following will verify:
	 * 1. VLAN ID matching for VLAN tagged requests.
	 * 2. prio-tagged/untagged to prio-tagged/untagged matching.
	 *
	 * This XOR is valid, since 0x0 < vlan_id < 0x0FFF.
	 */
	vlan_diff = rdma_vlan_dev_vlan_id(gid_attr->ndev) ^ ctx->vlan_id;

	return (vlan_diff == 0x0000 || vlan_diff == 0xFFFF);
}