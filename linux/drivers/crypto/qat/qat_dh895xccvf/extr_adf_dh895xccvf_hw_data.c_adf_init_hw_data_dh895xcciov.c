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
struct adf_hw_device_data {int num_logical_accel; TYPE_1__* dev_class; int /*<<< orphan*/  min_iov_compat_ver; int /*<<< orphan*/  enable_vf2pf_comms; void* enable_ints; int /*<<< orphan*/  get_sku; int /*<<< orphan*/  get_vintmsk_offset; int /*<<< orphan*/  get_pf2vf_offset; int /*<<< orphan*/  get_misc_bar_id; int /*<<< orphan*/  get_etr_bar_id; int /*<<< orphan*/  get_num_aes; int /*<<< orphan*/  get_num_accels; int /*<<< orphan*/  get_ae_mask; int /*<<< orphan*/  get_accel_mask; int /*<<< orphan*/  disable_iov; void* exit_arb; void* init_arb; int /*<<< orphan*/  send_admin_init; void* exit_admin_comms; void* init_admin_comms; void* enable_error_correction; int /*<<< orphan*/  free_irq; int /*<<< orphan*/  alloc_irq; int /*<<< orphan*/  tx_rings_mask; int /*<<< orphan*/  tx_rx_gap; int /*<<< orphan*/  num_engines; int /*<<< orphan*/  num_accel; int /*<<< orphan*/  num_banks; } ;
struct TYPE_2__ {int /*<<< orphan*/  instances; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADF_DH895XCCIOV_ETR_MAX_BANKS ; 
 int /*<<< orphan*/  ADF_DH895XCCIOV_MAX_ACCELENGINES ; 
 int /*<<< orphan*/  ADF_DH895XCCIOV_MAX_ACCELERATORS ; 
 int /*<<< orphan*/  ADF_DH895XCCIOV_RX_RINGS_OFFSET ; 
 int /*<<< orphan*/  ADF_DH895XCCIOV_TX_RINGS_MASK ; 
 int /*<<< orphan*/  ADF_PFVF_COMPATIBILITY_VERSION ; 
 int /*<<< orphan*/  adf_devmgr_update_class_index (struct adf_hw_device_data*) ; 
 int /*<<< orphan*/  adf_enable_vf2pf_comms ; 
 int /*<<< orphan*/  adf_vf2pf_init ; 
 int /*<<< orphan*/  adf_vf2pf_shutdown ; 
 void* adf_vf_int_noop ; 
 int /*<<< orphan*/  adf_vf_isr_resource_alloc ; 
 int /*<<< orphan*/  adf_vf_isr_resource_free ; 
 void* adf_vf_void_noop ; 
 TYPE_1__ dh895xcciov_class ; 
 int /*<<< orphan*/  get_accel_mask ; 
 int /*<<< orphan*/  get_ae_mask ; 
 int /*<<< orphan*/  get_etr_bar_id ; 
 int /*<<< orphan*/  get_misc_bar_id ; 
 int /*<<< orphan*/  get_num_accels ; 
 int /*<<< orphan*/  get_num_aes ; 
 int /*<<< orphan*/  get_pf2vf_offset ; 
 int /*<<< orphan*/  get_sku ; 
 int /*<<< orphan*/  get_vintmsk_offset ; 

void adf_init_hw_data_dh895xcciov(struct adf_hw_device_data *hw_data)
{
	hw_data->dev_class = &dh895xcciov_class;
	hw_data->num_banks = ADF_DH895XCCIOV_ETR_MAX_BANKS;
	hw_data->num_accel = ADF_DH895XCCIOV_MAX_ACCELERATORS;
	hw_data->num_logical_accel = 1;
	hw_data->num_engines = ADF_DH895XCCIOV_MAX_ACCELENGINES;
	hw_data->tx_rx_gap = ADF_DH895XCCIOV_RX_RINGS_OFFSET;
	hw_data->tx_rings_mask = ADF_DH895XCCIOV_TX_RINGS_MASK;
	hw_data->alloc_irq = adf_vf_isr_resource_alloc;
	hw_data->free_irq = adf_vf_isr_resource_free;
	hw_data->enable_error_correction = adf_vf_void_noop;
	hw_data->init_admin_comms = adf_vf_int_noop;
	hw_data->exit_admin_comms = adf_vf_void_noop;
	hw_data->send_admin_init = adf_vf2pf_init;
	hw_data->init_arb = adf_vf_int_noop;
	hw_data->exit_arb = adf_vf_void_noop;
	hw_data->disable_iov = adf_vf2pf_shutdown;
	hw_data->get_accel_mask = get_accel_mask;
	hw_data->get_ae_mask = get_ae_mask;
	hw_data->get_num_accels = get_num_accels;
	hw_data->get_num_aes = get_num_aes;
	hw_data->get_etr_bar_id = get_etr_bar_id;
	hw_data->get_misc_bar_id = get_misc_bar_id;
	hw_data->get_pf2vf_offset = get_pf2vf_offset;
	hw_data->get_vintmsk_offset = get_vintmsk_offset;
	hw_data->get_sku = get_sku;
	hw_data->enable_ints = adf_vf_void_noop;
	hw_data->enable_vf2pf_comms = adf_enable_vf2pf_comms;
	hw_data->min_iov_compat_ver = ADF_PFVF_COMPATIBILITY_VERSION;
	hw_data->dev_class->instances++;
	adf_devmgr_update_class_index(hw_data);
}