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
struct TYPE_3__ {unsigned int vlan_pri_map; } ;
struct TYPE_4__ {TYPE_1__ tp; } ;
struct adapter {TYPE_2__ params; } ;

/* Variables and functions */
#define  F_ETHERTYPE 137 
#define  F_FCOE 136 
#define  F_FRAGMENTATION 135 
#define  F_MACMATCH 134 
#define  F_MPSHITTYPE 133 
#define  F_PORT 132 
#define  F_PROTOCOL 131 
#define  F_TOS 130 
#define  F_VLAN 129 
#define  F_VNIC_ID 128 
 int W_FT_ETHERTYPE ; 
 int W_FT_FCOE ; 
 int W_FT_FRAGMENTATION ; 
 int W_FT_MACMATCH ; 
 int W_FT_MPSHITTYPE ; 
 int W_FT_PORT ; 
 int W_FT_PROTOCOL ; 
 int W_FT_TOS ; 
 int W_FT_VLAN ; 
 int W_FT_VNIC_ID ; 

int t4_filter_field_shift(const struct adapter *adap, int filter_sel)
{
	unsigned int filter_mode = adap->params.tp.vlan_pri_map;
	unsigned int sel;
	int field_shift;

	if ((filter_mode & filter_sel) == 0)
		return -1;

	for (sel = 1, field_shift = 0; sel < filter_sel; sel <<= 1) {
		switch (filter_mode & sel) {
		case F_FCOE:
			field_shift += W_FT_FCOE;
			break;
		case F_PORT:
			field_shift += W_FT_PORT;
			break;
		case F_VNIC_ID:
			field_shift += W_FT_VNIC_ID;
			break;
		case F_VLAN:
			field_shift += W_FT_VLAN;
			break;
		case F_TOS:
			field_shift += W_FT_TOS;
			break;
		case F_PROTOCOL:
			field_shift += W_FT_PROTOCOL;
			break;
		case F_ETHERTYPE:
			field_shift += W_FT_ETHERTYPE;
			break;
		case F_MACMATCH:
			field_shift += W_FT_MACMATCH;
			break;
		case F_MPSHITTYPE:
			field_shift += W_FT_MPSHITTYPE;
			break;
		case F_FRAGMENTATION:
			field_shift += W_FT_FRAGMENTATION;
			break;
		}
	}
	return field_shift;
}