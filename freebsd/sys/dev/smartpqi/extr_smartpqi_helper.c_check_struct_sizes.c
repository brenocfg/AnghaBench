#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sense_header_scsi {int dummy; } ;
struct pqi_registers {int dummy; } ;
struct pqi_pref_settings {int dummy; } ;
struct pqi_io_response {int dummy; } ;
struct pqi_dev_adminq_cap {int dummy; } ;
struct pqi_cap {int dummy; } ;
struct ioa_registers {int dummy; } ;
struct init_base_struct {int dummy; } ;
struct bmic_host_wellness_time {int dummy; } ;
struct bmic_host_wellness_driver_version {int dummy; } ;
struct admin_q_param {int dummy; } ;
typedef  int /*<<< orphan*/  reportlun_header_t ;
typedef  int /*<<< orphan*/  reportlun_ext_entry_t ;
typedef  int /*<<< orphan*/  reportlun_data_ext_t ;
typedef  int /*<<< orphan*/  raidmap_data_t ;
typedef  int /*<<< orphan*/  raid_path_error_info_elem_t ;
typedef  int /*<<< orphan*/  pqisrc_raid_req_t ;
typedef  int /*<<< orphan*/  pqisrc_raid_map_t ;
typedef  int /*<<< orphan*/  pqi_tmf_req_t ;
typedef  int /*<<< orphan*/  pqi_iu_layer_desc_t ;
typedef  int /*<<< orphan*/  pqi_dev_cap_t ;
typedef  int /*<<< orphan*/  pqi_aio_req_t ;
typedef  int /*<<< orphan*/  op_q_params ;
typedef  int /*<<< orphan*/  iu_header_t ;
typedef  int /*<<< orphan*/  gen_adm_resp_iu_t ;
typedef  int /*<<< orphan*/  gen_adm_req_iu_t ;
typedef  int /*<<< orphan*/  bmic_ident_physdev_t ;
typedef  int /*<<< orphan*/  bmic_ident_ctrl_t ;
typedef  int /*<<< orphan*/  aio_path_error_info_elem_t ;
typedef  int /*<<< orphan*/  SCSI3Addr_struct ;
typedef  int /*<<< orphan*/  RequestBlock_struct ;
typedef  int /*<<< orphan*/  PhysDevAddr_struct ;
typedef  int /*<<< orphan*/  MoreErrInfo_struct ;
typedef  int /*<<< orphan*/  LogDevAddr_struct ;
typedef  int /*<<< orphan*/  LUNAddr_struct ;
typedef  int /*<<< orphan*/  IOCTL_Command_struct ;
typedef  int /*<<< orphan*/  ErrorInfo_struct ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 

void check_struct_sizes()
{   
    
    ASSERT(sizeof(SCSI3Addr_struct)== 2);
    ASSERT(sizeof(PhysDevAddr_struct) == 8);
    ASSERT(sizeof(LogDevAddr_struct)== 8);
    ASSERT(sizeof(LUNAddr_struct)==8);
    ASSERT(sizeof(RequestBlock_struct) == 20);
    ASSERT(sizeof(MoreErrInfo_struct)== 8);
    ASSERT(sizeof(ErrorInfo_struct)== 48);
    ASSERT(sizeof(IOCTL_Command_struct)== 86);
    ASSERT(sizeof(struct bmic_host_wellness_driver_version)== 42);
    ASSERT(sizeof(struct bmic_host_wellness_time)== 20);
    ASSERT(sizeof(struct pqi_dev_adminq_cap)== 8);
    ASSERT(sizeof(struct admin_q_param)== 4);
    ASSERT(sizeof(struct pqi_registers)== 256);
    ASSERT(sizeof(struct ioa_registers)== 4128);
    ASSERT(sizeof(struct pqi_pref_settings)==4);
    ASSERT(sizeof(struct pqi_cap)== 20);
    ASSERT(sizeof(iu_header_t)== 4);
    ASSERT(sizeof(gen_adm_req_iu_t)== 64);
    ASSERT(sizeof(gen_adm_resp_iu_t)== 64);
    ASSERT(sizeof(op_q_params) == 9);
    ASSERT(sizeof(raid_path_error_info_elem_t)== 276);
    ASSERT(sizeof(aio_path_error_info_elem_t)== 276);
    ASSERT(sizeof(struct init_base_struct)== 24);
    ASSERT(sizeof(pqi_iu_layer_desc_t)== 16);
    ASSERT(sizeof(pqi_dev_cap_t)== 576);
    ASSERT(sizeof(pqi_aio_req_t)== 128);
    ASSERT(sizeof(pqisrc_raid_req_t)== 128);
    ASSERT(sizeof(pqi_tmf_req_t)== 32);
    ASSERT(sizeof(struct pqi_io_response)== 16);
    ASSERT(sizeof(struct sense_header_scsi)== 8);
    ASSERT(sizeof(reportlun_header_t)==8);
    ASSERT(sizeof(reportlun_ext_entry_t)== 24);
    ASSERT(sizeof(reportlun_data_ext_t)== 32);
    ASSERT(sizeof(raidmap_data_t)==8);
    ASSERT(sizeof(pqisrc_raid_map_t)== 8256);
    ASSERT(sizeof(bmic_ident_ctrl_t)== 325);
    ASSERT(sizeof(bmic_ident_physdev_t)==2048);
  
}