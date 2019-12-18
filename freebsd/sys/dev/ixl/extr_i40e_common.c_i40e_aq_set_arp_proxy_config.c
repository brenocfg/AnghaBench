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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u16 ;
struct i40e_hw {int dummy; } ;
struct i40e_asq_cmd_details {int dummy; } ;
struct i40e_aqc_arp_proxy_data {int dummy; } ;
struct TYPE_3__ {void* addr_low; void* addr_high; } ;
struct TYPE_4__ {TYPE_1__ external; } ;
struct i40e_aq_desc {int /*<<< orphan*/  datalen; TYPE_2__ params; int /*<<< orphan*/  flags; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_TO_LE16 (int) ; 
 void* CPU_TO_LE32 (int /*<<< orphan*/ ) ; 
 scalar_t__ I40E_AQ_FLAG_BUF ; 
 scalar_t__ I40E_AQ_FLAG_RD ; 
 int I40E_ERR_PARAM ; 
 int /*<<< orphan*/  I40E_HI_DWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_LO_DWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_aqc_opc_set_proxy_config ; 
 int i40e_asq_send_command (struct i40e_hw*,struct i40e_aq_desc*,struct i40e_aqc_arp_proxy_data*,int,struct i40e_asq_cmd_details*) ; 
 int /*<<< orphan*/  i40e_fill_default_direct_cmd_desc (struct i40e_aq_desc*,int /*<<< orphan*/ ) ; 

enum i40e_status_code i40e_aq_set_arp_proxy_config(struct i40e_hw *hw,
				struct i40e_aqc_arp_proxy_data *proxy_config,
				struct i40e_asq_cmd_details *cmd_details)
{
	struct i40e_aq_desc desc;
	enum i40e_status_code status;

	if (!proxy_config)
		return I40E_ERR_PARAM;

	i40e_fill_default_direct_cmd_desc(&desc, i40e_aqc_opc_set_proxy_config);

	desc.flags |= CPU_TO_LE16((u16)I40E_AQ_FLAG_BUF);
	desc.flags |= CPU_TO_LE16((u16)I40E_AQ_FLAG_RD);
	desc.params.external.addr_high =
				  CPU_TO_LE32(I40E_HI_DWORD((u64)proxy_config));
	desc.params.external.addr_low =
				  CPU_TO_LE32(I40E_LO_DWORD((u64)proxy_config));
	desc.datalen = CPU_TO_LE16(sizeof(struct i40e_aqc_arp_proxy_data));

	status = i40e_asq_send_command(hw, &desc, proxy_config,
				       sizeof(struct i40e_aqc_arp_proxy_data),
				       cmd_details);

	return status;
}