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
struct adf_hw_device_data {int num_logical_accel; int /*<<< orphan*/  min_iov_compat_ver; int /*<<< orphan*/  reset_device; int /*<<< orphan*/  enable_vf2pf_comms; int /*<<< orphan*/  enable_ints; int /*<<< orphan*/  get_arb_mapping; int /*<<< orphan*/  exit_arb; int /*<<< orphan*/  init_arb; int /*<<< orphan*/  send_admin_init; int /*<<< orphan*/  disable_iov; int /*<<< orphan*/  exit_admin_comms; int /*<<< orphan*/  init_admin_comms; int /*<<< orphan*/  fw_mmp_name; int /*<<< orphan*/  fw_name; int /*<<< orphan*/  get_sku; int /*<<< orphan*/  get_sram_bar_id; int /*<<< orphan*/  get_vintmsk_offset; int /*<<< orphan*/  get_pf2vf_offset; int /*<<< orphan*/  get_misc_bar_id; int /*<<< orphan*/  get_etr_bar_id; int /*<<< orphan*/  get_num_aes; int /*<<< orphan*/  get_num_accels; int /*<<< orphan*/  get_ae_mask; int /*<<< orphan*/  get_accel_mask; int /*<<< orphan*/  enable_error_correction; int /*<<< orphan*/  free_irq; int /*<<< orphan*/  alloc_irq; int /*<<< orphan*/  tx_rings_mask; int /*<<< orphan*/  tx_rx_gap; int /*<<< orphan*/  num_engines; int /*<<< orphan*/  num_accel; int /*<<< orphan*/  num_banks; scalar_t__ instance_id; TYPE_1__* dev_class; } ;
struct TYPE_2__ {int /*<<< orphan*/  instances; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADF_DH895XCC_ETR_MAX_BANKS ; 
 int /*<<< orphan*/  ADF_DH895XCC_FW ; 
 int /*<<< orphan*/  ADF_DH895XCC_MAX_ACCELENGINES ; 
 int /*<<< orphan*/  ADF_DH895XCC_MAX_ACCELERATORS ; 
 int /*<<< orphan*/  ADF_DH895XCC_MMP ; 
 int /*<<< orphan*/  ADF_DH895XCC_RX_RINGS_OFFSET ; 
 int /*<<< orphan*/  ADF_DH895XCC_TX_RINGS_MASK ; 
 int /*<<< orphan*/  ADF_PFVF_COMPATIBILITY_VERSION ; 
 int /*<<< orphan*/  adf_disable_sriov ; 
 int /*<<< orphan*/  adf_enable_error_correction ; 
 int /*<<< orphan*/  adf_enable_ints ; 
 int /*<<< orphan*/  adf_exit_admin_comms ; 
 int /*<<< orphan*/  adf_exit_arb ; 
 int /*<<< orphan*/  adf_get_arbiter_mapping ; 
 int /*<<< orphan*/  adf_init_admin_comms ; 
 int /*<<< orphan*/  adf_init_arb ; 
 int /*<<< orphan*/  adf_isr_resource_alloc ; 
 int /*<<< orphan*/  adf_isr_resource_free ; 
 int /*<<< orphan*/  adf_pf_enable_vf2pf_comms ; 
 int /*<<< orphan*/  adf_reset_sbr ; 
 int /*<<< orphan*/  adf_send_admin_init ; 
 TYPE_1__ dh895xcc_class ; 
 int /*<<< orphan*/  get_accel_mask ; 
 int /*<<< orphan*/  get_ae_mask ; 
 int /*<<< orphan*/  get_etr_bar_id ; 
 int /*<<< orphan*/  get_misc_bar_id ; 
 int /*<<< orphan*/  get_num_accels ; 
 int /*<<< orphan*/  get_num_aes ; 
 int /*<<< orphan*/  get_pf2vf_offset ; 
 int /*<<< orphan*/  get_sku ; 
 int /*<<< orphan*/  get_sram_bar_id ; 
 int /*<<< orphan*/  get_vintmsk_offset ; 

void adf_init_hw_data_dh895xcc(struct adf_hw_device_data *hw_data)
{
	hw_data->dev_class = &dh895xcc_class;
	hw_data->instance_id = dh895xcc_class.instances++;
	hw_data->num_banks = ADF_DH895XCC_ETR_MAX_BANKS;
	hw_data->num_accel = ADF_DH895XCC_MAX_ACCELERATORS;
	hw_data->num_logical_accel = 1;
	hw_data->num_engines = ADF_DH895XCC_MAX_ACCELENGINES;
	hw_data->tx_rx_gap = ADF_DH895XCC_RX_RINGS_OFFSET;
	hw_data->tx_rings_mask = ADF_DH895XCC_TX_RINGS_MASK;
	hw_data->alloc_irq = adf_isr_resource_alloc;
	hw_data->free_irq = adf_isr_resource_free;
	hw_data->enable_error_correction = adf_enable_error_correction;
	hw_data->get_accel_mask = get_accel_mask;
	hw_data->get_ae_mask = get_ae_mask;
	hw_data->get_num_accels = get_num_accels;
	hw_data->get_num_aes = get_num_aes;
	hw_data->get_etr_bar_id = get_etr_bar_id;
	hw_data->get_misc_bar_id = get_misc_bar_id;
	hw_data->get_pf2vf_offset = get_pf2vf_offset;
	hw_data->get_vintmsk_offset = get_vintmsk_offset;
	hw_data->get_sram_bar_id = get_sram_bar_id;
	hw_data->get_sku = get_sku;
	hw_data->fw_name = ADF_DH895XCC_FW;
	hw_data->fw_mmp_name = ADF_DH895XCC_MMP;
	hw_data->init_admin_comms = adf_init_admin_comms;
	hw_data->exit_admin_comms = adf_exit_admin_comms;
	hw_data->disable_iov = adf_disable_sriov;
	hw_data->send_admin_init = adf_send_admin_init;
	hw_data->init_arb = adf_init_arb;
	hw_data->exit_arb = adf_exit_arb;
	hw_data->get_arb_mapping = adf_get_arbiter_mapping;
	hw_data->enable_ints = adf_enable_ints;
	hw_data->enable_vf2pf_comms = adf_pf_enable_vf2pf_comms;
	hw_data->reset_device = adf_reset_sbr;
	hw_data->min_iov_compat_ver = ADF_PFVF_COMPATIBILITY_VERSION;
}