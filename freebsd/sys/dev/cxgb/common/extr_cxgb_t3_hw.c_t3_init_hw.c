#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_22__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_10__ ;

/* Type definitions */
typedef  int u32 ;
struct vpd_params {int uclk; int /*<<< orphan*/  mem_timing; scalar_t__ mclk; } ;
struct TYPE_25__ {int /*<<< orphan*/  max_pkt_size; } ;
struct TYPE_26__ {int /*<<< orphan*/  nroutes; int /*<<< orphan*/  nfilters; int /*<<< orphan*/  nservers; } ;
struct TYPE_28__ {scalar_t__ rev; int nports; TYPE_10__ sge; int /*<<< orphan*/  chan_map; int /*<<< orphan*/  tp; TYPE_1__ mc5; struct vpd_params vpd; } ;
struct TYPE_29__ {TYPE_2__ params; int /*<<< orphan*/  mc5; int /*<<< orphan*/  cm; int /*<<< orphan*/  pmtx; int /*<<< orphan*/  pmrx; } ;
typedef  TYPE_3__ adapter_t ;
struct TYPE_27__ {int /*<<< orphan*/  mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_CIM_BOOT_CFG ; 
 int /*<<< orphan*/  A_CIM_HOST_ACC_DATA ; 
 int /*<<< orphan*/  A_PCIX_CFG ; 
 int /*<<< orphan*/  A_PL_RST ; 
 int /*<<< orphan*/  A_PM1_RX_CFG ; 
 int /*<<< orphan*/  A_PM1_RX_MODE ; 
 int /*<<< orphan*/  A_PM1_TX_MODE ; 
 int /*<<< orphan*/  A_T3DBG_GPIO_ACT_LOW ; 
 int /*<<< orphan*/  A_ULPTX_CONFIG ; 
 int /*<<< orphan*/  CH_ERR (TYPE_3__*,char*) ; 
 int EIO ; 
 int FW_FLASH_BOOT_ADDR ; 
 int F_CFG_CQE_SOP_MASK ; 
 int F_CLIDECEN ; 
 int /*<<< orphan*/  F_CQ ; 
 int F_DMASTOPEN ; 
 int F_FATALPERREN ; 
 unsigned int MAX_RX_COALESCING_LEN ; 
 scalar_t__ T3_REV_C ; 
 int V_BOOTADDR (int) ; 
 TYPE_22__* adap2pinfo (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int calc_gpio_intr (TYPE_3__*) ; 
 scalar_t__ calibrate_xgm (TYPE_3__*) ; 
 int /*<<< orphan*/  calibrate_xgm_t3b (TYPE_3__*) ; 
 int /*<<< orphan*/  chan_init_hw (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ clear_sge_ctxt (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_pcie (TYPE_3__*) ; 
 scalar_t__ is_pcie (TYPE_3__*) ; 
 scalar_t__ mc7_init (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  partition_mem (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t3_mac_init (int /*<<< orphan*/ *) ; 
 scalar_t__ t3_mc5_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ t3_read_reg (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_set_reg_field (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  t3_sge_init (TYPE_3__*,TYPE_10__*) ; 
 int /*<<< orphan*/  t3_tp_set_coalescing_size (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  t3_tp_set_max_rxsize (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_write_reg (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ tp_init (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ulp_config (TYPE_3__*,int /*<<< orphan*/ *) ; 

int t3_init_hw(adapter_t *adapter, u32 fw_params)
{
	int err = -EIO, attempts, i;
	const struct vpd_params *vpd = &adapter->params.vpd;

	if (adapter->params.rev > 0)
		calibrate_xgm_t3b(adapter);
	else if (calibrate_xgm(adapter))
		goto out_err;

	if (adapter->params.nports > 2)
		t3_mac_init(&adap2pinfo(adapter, 0)->mac);

	if (vpd->mclk) {
		partition_mem(adapter, &adapter->params.tp);

		if (mc7_init(&adapter->pmrx, vpd->mclk, vpd->mem_timing) ||
		    mc7_init(&adapter->pmtx, vpd->mclk, vpd->mem_timing) ||
		    mc7_init(&adapter->cm, vpd->mclk, vpd->mem_timing) ||
		    t3_mc5_init(&adapter->mc5, adapter->params.mc5.nservers,
			        adapter->params.mc5.nfilters,
			       	adapter->params.mc5.nroutes))
			goto out_err;

		for (i = 0; i < 32; i++)
			if (clear_sge_ctxt(adapter, i, F_CQ))
				goto out_err;
	}

	if (tp_init(adapter, &adapter->params.tp))
		goto out_err;

	t3_tp_set_coalescing_size(adapter,
				  min(adapter->params.sge.max_pkt_size,
				      MAX_RX_COALESCING_LEN), 1);
	t3_tp_set_max_rxsize(adapter,
			     min(adapter->params.sge.max_pkt_size, 16384U));
	ulp_config(adapter, &adapter->params.tp);
	if (is_pcie(adapter))
		config_pcie(adapter);
	else
		t3_set_reg_field(adapter, A_PCIX_CFG, 0,
				 F_DMASTOPEN | F_CLIDECEN);

	if (adapter->params.rev == T3_REV_C)
		t3_set_reg_field(adapter, A_ULPTX_CONFIG, 0,
				 F_CFG_CQE_SOP_MASK);

	t3_write_reg(adapter, A_PM1_RX_CFG, 0xffffffff);
	t3_write_reg(adapter, A_PM1_RX_MODE, 0);
	t3_write_reg(adapter, A_PM1_TX_MODE, 0);
	chan_init_hw(adapter, adapter->params.chan_map);
	t3_sge_init(adapter, &adapter->params.sge);
	t3_set_reg_field(adapter, A_PL_RST, 0, F_FATALPERREN);

	t3_write_reg(adapter, A_T3DBG_GPIO_ACT_LOW, calc_gpio_intr(adapter));

	t3_write_reg(adapter, A_CIM_HOST_ACC_DATA, vpd->uclk | fw_params);
	t3_write_reg(adapter, A_CIM_BOOT_CFG,
		     V_BOOTADDR(FW_FLASH_BOOT_ADDR >> 2));
	(void) t3_read_reg(adapter, A_CIM_BOOT_CFG);    /* flush */

	attempts = 100;
	do {                          /* wait for uP to initialize */
		msleep(20);
	} while (t3_read_reg(adapter, A_CIM_HOST_ACC_DATA) && --attempts);
	if (!attempts) {
		CH_ERR(adapter, "uP initialization timed out\n");
		goto out_err;
	}

	err = 0;
 out_err:
	return err;
}