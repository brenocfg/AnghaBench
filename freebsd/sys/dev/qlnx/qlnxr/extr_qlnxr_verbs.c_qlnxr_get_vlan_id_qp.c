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
union ib_gid {int* raw; } ;
typedef  int u16 ;
struct TYPE_3__ {union ib_gid dgid; } ;
struct TYPE_4__ {TYPE_1__ grh; } ;
struct ib_qp_attr {int vlan_id; TYPE_2__ ah_attr; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;

/* Variables and functions */
 int EVL_VLID_MASK ; 
 int IB_QP_VID ; 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static inline bool
qlnxr_get_vlan_id_qp(qlnx_host_t *ha, struct ib_qp_attr *attr, int attr_mask,
       u16 *vlan_id)
{
	bool ret = false;

	QL_DPRINT12(ha, "enter \n");

	*vlan_id = 0;

#if __FreeBSD_version >= 1100000
	u16 tmp_vlan_id;

#if __FreeBSD_version >= 1102000
	union ib_gid *dgid;

	dgid = &attr->ah_attr.grh.dgid;
	tmp_vlan_id = (dgid->raw[11] << 8) | dgid->raw[12];

	if (!(tmp_vlan_id & ~EVL_VLID_MASK)) {
		*vlan_id = tmp_vlan_id;
		ret = true;
	}
#else
	tmp_vlan_id = attr->vlan_id;

	if ((attr_mask & IB_QP_VID) && (!(tmp_vlan_id & ~EVL_VLID_MASK))) {
		*vlan_id = tmp_vlan_id;
		ret = true;
	}

#endif /* #if __FreeBSD_version > 1102000 */

#else
	ret = true;

#endif /* #if __FreeBSD_version >= 1100000 */

	QL_DPRINT12(ha, "exit vlan_id = 0x%x ret = %d \n", *vlan_id, ret);

	return (ret);
}