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
union ib_gid {int* raw; } ;
typedef  int u16 ;
struct TYPE_2__ {union ib_gid dgid; } ;
struct ib_ah_attr {TYPE_1__ grh; } ;

/* Variables and functions */

__attribute__((used)) static inline bool
qlnxr_get_vlan_id_gsi(struct ib_ah_attr *ah_attr, u16 *vlan_id)
{
	u16 tmp_vlan_id;
	union ib_gid *dgid = &ah_attr->grh.dgid;

	tmp_vlan_id = (dgid->raw[11] << 8) | dgid->raw[12];
	if (tmp_vlan_id < 0x1000) {
		*vlan_id = tmp_vlan_id;
		return true;
	} else {
		*vlan_id = 0;
		return false;
	}
}