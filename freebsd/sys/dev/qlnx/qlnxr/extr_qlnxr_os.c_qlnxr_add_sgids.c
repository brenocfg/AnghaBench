#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  union ib_gid {int dummy; } ib_gid ;
typedef  int /*<<< orphan*/  u16 ;
struct qlnxr_dev {TYPE_1__* ha; } ;
struct TYPE_2__ {int /*<<< orphan*/  primary_mac; int /*<<< orphan*/  ifp; } ;
typedef  TYPE_1__ qlnx_host_t ;

/* Variables and functions */
 int is_vlan_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlnxr_add_ip_based_gid (struct qlnxr_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlnxr_add_sgid (struct qlnxr_dev*,union ib_gid*) ; 
 int /*<<< orphan*/  qlnxr_build_sgid_mac (union ib_gid*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlan_dev_vlan_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qlnxr_add_sgids(struct qlnxr_dev *dev)
{
	qlnx_host_t *ha = dev->ha;
	u16 vlan_id;
	bool is_vlan;
	union ib_gid vgid;

	qlnxr_add_ip_based_gid(dev, ha->ifp);
	/* MAC/VLAN base GIDs */
	is_vlan = is_vlan_dev(ha->ifp);
       	vlan_id = (is_vlan) ? vlan_dev_vlan_id(ha->ifp) : 0;
	qlnxr_build_sgid_mac(&vgid, ha->primary_mac, is_vlan, vlan_id);
	qlnxr_add_sgid(dev, &vgid);
}