#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct thread {int dummy; } ;
struct ifnet {int dummy; } ;
struct cdev {scalar_t__ si_drv1; } ;
struct TYPE_22__ {int /*<<< orphan*/ * buffer; int /*<<< orphan*/  cmd; int /*<<< orphan*/ * size; } ;
typedef  TYPE_2__ qlnx_trace_t ;
typedef  int /*<<< orphan*/  qlnx_storm_stats_dump_t ;
typedef  int /*<<< orphan*/  qlnx_reg_rd_wr_t ;
typedef  int /*<<< orphan*/  qlnx_perm_mac_addr_t ;
typedef  int /*<<< orphan*/  qlnx_pcicfg_rd_wr_t ;
typedef  int /*<<< orphan*/  qlnx_nvram_t ;
typedef  int /*<<< orphan*/  qlnx_lldp_sys_tlvs_t ;
typedef  int /*<<< orphan*/  qlnx_idle_chk_t ;
struct TYPE_21__ {int num_hwfns; } ;
struct TYPE_23__ {TYPE_1__ cdev; struct ifnet* ifp; } ;
typedef  TYPE_3__ qlnx_host_t ;
typedef  int /*<<< orphan*/  qlnx_grcdump_t ;
typedef  int /*<<< orphan*/  qlnx_get_regs_t ;
typedef  int /*<<< orphan*/  qlnx_drvinfo_t ;
typedef  int /*<<< orphan*/  qlnx_dev_setting_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
#define  QLNX_DEV_SETTING 142 
#define  QLNX_DRV_INFO 141 
#define  QLNX_GET_REGS 140 
#define  QLNX_GRC_DUMP 139 
#define  QLNX_GRC_DUMP_SIZE 138 
#define  QLNX_IDLE_CHK 137 
#define  QLNX_IDLE_CHK_SIZE 136 
#define  QLNX_MAC_ADDR 135 
#define  QLNX_NVRAM 134 
#define  QLNX_RD_WR_PCICFG 133 
#define  QLNX_RD_WR_REG 132 
#define  QLNX_SET_LLDP_TLVS 131 
#define  QLNX_STORM_STATS 130 
#define  QLNX_TRACE 129 
#define  QLNX_TRACE_SIZE 128 
 int qlnx_dev_settings (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int qlnx_drv_info (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int qlnx_get_grc_dump (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlnx_get_grc_dump_size (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int qlnx_get_idle_chk (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlnx_get_idle_chk_size (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int qlnx_get_regs (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int qlnx_get_trace (TYPE_3__*,int,TYPE_2__*) ; 
 int /*<<< orphan*/  qlnx_get_trace_size (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  qlnx_mac_addr (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int qlnx_nvram (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int qlnx_rd_wr_pci_config (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int qlnx_reg_rd_wr (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int qlnx_set_lldp_tlvx (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlnx_storm_stats (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
qlnx_eioctl(struct cdev *dev, u_long cmd, caddr_t data, int fflag,
	struct thread *td)
{
	qlnx_host_t	*ha;
	int		rval = 0;
	struct ifnet	*ifp;
	qlnx_trace_t	*trace;
	int		i;

	if ((ha = (qlnx_host_t *)dev->si_drv1) == NULL)
		return ENXIO;

	ifp = ha->ifp;

	switch (cmd) {

	case QLNX_GRC_DUMP_SIZE:
		qlnx_get_grc_dump_size(ha, (qlnx_grcdump_t *)data);
		break;

	case QLNX_GRC_DUMP:
		rval = qlnx_get_grc_dump(ha, (qlnx_grcdump_t *)data);
		break;

	case QLNX_IDLE_CHK_SIZE:
		qlnx_get_idle_chk_size(ha, (qlnx_idle_chk_t *)data);
		break;

	case QLNX_IDLE_CHK:
		rval = qlnx_get_idle_chk(ha, (qlnx_idle_chk_t *)data);
		break;

	case QLNX_DRV_INFO:
		rval = qlnx_drv_info(ha, (qlnx_drvinfo_t *)data);
		break;

	case QLNX_DEV_SETTING:
		rval = qlnx_dev_settings(ha, (qlnx_dev_setting_t *)data);
		break;

	case QLNX_GET_REGS:
		rval = qlnx_get_regs(ha, (qlnx_get_regs_t *)data);
		break;

	case QLNX_NVRAM:
		rval = qlnx_nvram(ha, (qlnx_nvram_t *)data);
		break;

	case QLNX_RD_WR_REG:
		rval = qlnx_reg_rd_wr(ha, (qlnx_reg_rd_wr_t *)data);
		break;

	case QLNX_RD_WR_PCICFG:
		rval = qlnx_rd_wr_pci_config(ha, (qlnx_pcicfg_rd_wr_t *)data);
		break;

	case QLNX_MAC_ADDR:
		qlnx_mac_addr(ha, (qlnx_perm_mac_addr_t *)data);
		break;

	case QLNX_STORM_STATS:
		qlnx_storm_stats(ha, (qlnx_storm_stats_dump_t *)data);
		break;

	case QLNX_TRACE_SIZE:
		qlnx_get_trace_size(ha, (qlnx_trace_t *)data);
		break;

	case QLNX_TRACE:
		trace = (qlnx_trace_t *)data;

		for (i = 0; i < ha->cdev.num_hwfns; i++) {

			if (trace->size[i] && trace->cmd && trace->buffer[i])
				rval = qlnx_get_trace(ha, i, trace);

			if (rval)
				break;
		}
		break;

#ifdef QLNX_USER_LLDP
	case QLNX_SET_LLDP_TLVS:
		rval = qlnx_set_lldp_tlvx(ha, (qlnx_lldp_sys_tlvs_t *)data);
		break;
#endif /* #ifdef QLNX_USER_LLDP */

	default:
		rval = EINVAL;
		break;
	}

	return (rval);
}