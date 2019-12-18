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
typedef  int uint32_t ;
struct query_params {int /*<<< orphan*/  cpi; } ;
struct TYPE_3__ {int def_port; int def_mcast_pri_port; int def_mcast_not_port; int life_state; int flags; int /*<<< orphan*/  mcast_top; int /*<<< orphan*/  enforce_cap; int /*<<< orphan*/  lids_per_port; int /*<<< orphan*/  lin_top; int /*<<< orphan*/  mcast_cap; int /*<<< orphan*/  rand_cap; int /*<<< orphan*/  lin_cap; } ;
struct TYPE_4__ {TYPE_1__ switch_info; int /*<<< orphan*/  lid; } ;
typedef  TYPE_2__ ib_switch_info_record_t ;

/* Variables and functions */
 int UMAD_SA_CAP_MASK2_IS_MCAST_TOP_SUP ; 
 int cl_ntoh16 (int /*<<< orphan*/ ) ; 
 int ib_class_cap_mask2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

__attribute__((used)) static void dump_switch_info_record(void *data, struct query_params *p)
{
	ib_switch_info_record_t *p_sir = data;
	uint32_t sa_cap_mask2 = ib_class_cap_mask2(&p->cpi);

	printf("SwitchInfoRecord dump:\n"
		"\t\tRID\n"
		"\t\tLID.....................................%u\n"
		"\t\tSwitchInfo dump:\n"
		"\t\tLinearFDBCap............................0x%X\n"
		"\t\tRandomFDBCap............................0x%X\n"
		"\t\tMulticastFDBCap.........................0x%X\n"
		"\t\tLinearFDBTop............................0x%X\n"
		"\t\tDefaultPort.............................%u\n"
		"\t\tDefaultMulticastPrimaryPort.............%u\n"
		"\t\tDefaultMulticastNotPrimaryPort..........%u\n"
		"\t\tLifeTimeValue/PortStateChange/OpSL2VL...0x%X\n"
		"\t\tLIDsPerPort.............................0x%X\n"
		"\t\tPartitionEnforcementCap.................0x%X\n"
		"\t\tflags...................................0x%X\n",
		cl_ntoh16(p_sir->lid),
		cl_ntoh16(p_sir->switch_info.lin_cap),
		cl_ntoh16(p_sir->switch_info.rand_cap),
		cl_ntoh16(p_sir->switch_info.mcast_cap),
		cl_ntoh16(p_sir->switch_info.lin_top),
		p_sir->switch_info.def_port,
		p_sir->switch_info.def_mcast_pri_port,
		p_sir->switch_info.def_mcast_not_port,
		p_sir->switch_info.life_state,
		cl_ntoh16(p_sir->switch_info.lids_per_port),
		cl_ntoh16(p_sir->switch_info.enforce_cap),
		p_sir->switch_info.flags);
	if (sa_cap_mask2 & UMAD_SA_CAP_MASK2_IS_MCAST_TOP_SUP)
		printf("\t\tMulticastFDBTop.........................0x%X\n",
		       cl_ntoh16(p_sir->switch_info.mcast_top));
}