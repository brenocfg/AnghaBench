#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sysctl_oid_list {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * mbx_comp_msecs; } ;
struct TYPE_5__ {TYPE_1__ hw; int /*<<< orphan*/  pci_dev; } ;
typedef  TYPE_2__ qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_QUAD (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qlnx_add_hw_mbx_cmpl_stats_sysctls(qla_host_t *ha)
{
        struct sysctl_ctx_list  *ctx;
        struct sysctl_oid_list  *node_children;

        ctx = device_get_sysctl_ctx(ha->pci_dev);
        node_children = SYSCTL_CHILDREN(device_get_sysctl_tree(ha->pci_dev));

	SYSCTL_ADD_QUAD(ctx, node_children,
		OID_AUTO, "mbx_completion_time_lt_200ms",
		CTLFLAG_RD, &ha->hw.mbx_comp_msecs[0],
		"mbx_completion_time_lt_200ms");

	SYSCTL_ADD_QUAD(ctx, node_children,
		OID_AUTO, "mbx_completion_time_200ms_400ms",
		CTLFLAG_RD, &ha->hw.mbx_comp_msecs[1],
		"mbx_completion_time_200ms_400ms");

	SYSCTL_ADD_QUAD(ctx, node_children,
		OID_AUTO, "mbx_completion_time_400ms_600ms",
		CTLFLAG_RD, &ha->hw.mbx_comp_msecs[2],
		"mbx_completion_time_400ms_600ms");

	SYSCTL_ADD_QUAD(ctx, node_children,
		OID_AUTO, "mbx_completion_time_600ms_800ms",
		CTLFLAG_RD, &ha->hw.mbx_comp_msecs[3],
		"mbx_completion_time_600ms_800ms");

	SYSCTL_ADD_QUAD(ctx, node_children,
		OID_AUTO, "mbx_completion_time_800ms_1000ms",
		CTLFLAG_RD, &ha->hw.mbx_comp_msecs[4],
		"mbx_completion_time_800ms_1000ms");

	SYSCTL_ADD_QUAD(ctx, node_children,
		OID_AUTO, "mbx_completion_time_1000ms_1200ms",
		CTLFLAG_RD, &ha->hw.mbx_comp_msecs[5],
		"mbx_completion_time_1000ms_1200ms");

	SYSCTL_ADD_QUAD(ctx, node_children,
		OID_AUTO, "mbx_completion_time_1200ms_1400ms",
		CTLFLAG_RD, &ha->hw.mbx_comp_msecs[6],
		"mbx_completion_time_1200ms_1400ms");

	SYSCTL_ADD_QUAD(ctx, node_children,
		OID_AUTO, "mbx_completion_time_1400ms_1600ms",
		CTLFLAG_RD, &ha->hw.mbx_comp_msecs[7],
		"mbx_completion_time_1400ms_1600ms");

	SYSCTL_ADD_QUAD(ctx, node_children,
		OID_AUTO, "mbx_completion_time_1600ms_1800ms",
		CTLFLAG_RD, &ha->hw.mbx_comp_msecs[8],
		"mbx_completion_time_1600ms_1800ms");

	SYSCTL_ADD_QUAD(ctx, node_children,
		OID_AUTO, "mbx_completion_time_1800ms_2000ms",
		CTLFLAG_RD, &ha->hw.mbx_comp_msecs[9],
		"mbx_completion_time_1800ms_2000ms");

	SYSCTL_ADD_QUAD(ctx, node_children,
		OID_AUTO, "mbx_completion_time_2000ms_2200ms",
		CTLFLAG_RD, &ha->hw.mbx_comp_msecs[10],
		"mbx_completion_time_2000ms_2200ms");

	SYSCTL_ADD_QUAD(ctx, node_children,
		OID_AUTO, "mbx_completion_time_2200ms_2400ms",
		CTLFLAG_RD, &ha->hw.mbx_comp_msecs[11],
		"mbx_completion_time_2200ms_2400ms");

	SYSCTL_ADD_QUAD(ctx, node_children,
		OID_AUTO, "mbx_completion_time_2400ms_2600ms",
		CTLFLAG_RD, &ha->hw.mbx_comp_msecs[12],
		"mbx_completion_time_2400ms_2600ms");

	SYSCTL_ADD_QUAD(ctx, node_children,
		OID_AUTO, "mbx_completion_time_2600ms_2800ms",
		CTLFLAG_RD, &ha->hw.mbx_comp_msecs[13],
		"mbx_completion_time_2600ms_2800ms");

	SYSCTL_ADD_QUAD(ctx, node_children,
		OID_AUTO, "mbx_completion_time_2800ms_3000ms",
		CTLFLAG_RD, &ha->hw.mbx_comp_msecs[14],
		"mbx_completion_time_2800ms_3000ms");

	SYSCTL_ADD_QUAD(ctx, node_children,
		OID_AUTO, "mbx_completion_time_3000ms_4000ms",
		CTLFLAG_RD, &ha->hw.mbx_comp_msecs[15],
		"mbx_completion_time_3000ms_4000ms");

	SYSCTL_ADD_QUAD(ctx, node_children,
		OID_AUTO, "mbx_completion_time_4000ms_5000ms",
		CTLFLAG_RD, &ha->hw.mbx_comp_msecs[16],
		"mbx_completion_time_4000ms_5000ms");

	SYSCTL_ADD_QUAD(ctx, node_children,
		OID_AUTO, "mbx_completion_host_mbx_cntrl_timeout",
		CTLFLAG_RD, &ha->hw.mbx_comp_msecs[17],
		"mbx_completion_host_mbx_cntrl_timeout");

	SYSCTL_ADD_QUAD(ctx, node_children,
		OID_AUTO, "mbx_completion_fw_mbx_cntrl_timeout",
		CTLFLAG_RD, &ha->hw.mbx_comp_msecs[18],
		"mbx_completion_fw_mbx_cntrl_timeout");
	return;
}