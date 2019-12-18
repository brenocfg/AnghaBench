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
typedef  int u16 ;
struct qlnxr_dev {TYPE_1__* ha; } ;
struct ifnet {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  primary_mac; int /*<<< orphan*/  ifp; } ;

/* Variables and functions */
#define  NETDEV_DOWN 129 
#define  NETDEV_UP 128 
 int /*<<< orphan*/  QL_DPRINT12 (TYPE_1__*,char*) ; 
 int is_vlan_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlnxr_add_sgid (struct qlnxr_dev*,union ib_gid*) ; 
 int /*<<< orphan*/  qlnxr_build_sgid_mac (union ib_gid*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  qlnxr_del_sgid (struct qlnxr_dev*,union ib_gid*) ; 
 int vlan_dev_vlan_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qlnxr_addr_event (struct qlnxr_dev *dev,
				unsigned long event,
				struct ifnet *ifp,
				union ib_gid *gid)
{
	bool is_vlan = false;
	union ib_gid vgid;
	u16 vlan_id = 0xffff;

	QL_DPRINT12(dev->ha, "Link event occured\n");
	is_vlan = is_vlan_dev(dev->ha->ifp);
	vlan_id = (is_vlan) ? vlan_dev_vlan_id(dev->ha->ifp) : 0;

	switch (event) {
	case NETDEV_UP :
		qlnxr_add_sgid(dev, gid);
		if (is_vlan) {
			qlnxr_build_sgid_mac(&vgid, dev->ha->primary_mac, is_vlan, vlan_id);
			qlnxr_add_sgid(dev, &vgid);
		}
		break;
	case NETDEV_DOWN :
		qlnxr_del_sgid(dev, gid);
		if (is_vlan) {
			qlnxr_build_sgid_mac(&vgid, dev->ha->primary_mac, is_vlan, vlan_id);
			qlnxr_del_sgid(dev, &vgid);
		}
		break;
	default :
		break;
	}
	return 1;
}