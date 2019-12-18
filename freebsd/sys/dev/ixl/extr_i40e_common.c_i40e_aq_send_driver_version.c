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
typedef  int u16 ;
struct i40e_hw {int dummy; } ;
struct i40e_driver_version {int* driver_string; int /*<<< orphan*/  subbuild_version; int /*<<< orphan*/  build_version; int /*<<< orphan*/  minor_version; int /*<<< orphan*/  major_version; } ;
struct i40e_asq_cmd_details {int dummy; } ;
struct i40e_aqc_driver_version {int /*<<< orphan*/  driver_subbuild_ver; int /*<<< orphan*/  driver_build_ver; int /*<<< orphan*/  driver_minor_ver; int /*<<< orphan*/  driver_major_ver; } ;
struct TYPE_2__ {int /*<<< orphan*/  raw; } ;
struct i40e_aq_desc {int /*<<< orphan*/  flags; TYPE_1__ params; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_TO_LE16 (int) ; 
 int I40E_AQ_FLAG_BUF ; 
 int I40E_AQ_FLAG_RD ; 
 int I40E_ERR_PARAM ; 
 int /*<<< orphan*/  i40e_aqc_opc_driver_version ; 
 int i40e_asq_send_command (struct i40e_hw*,struct i40e_aq_desc*,int*,int,struct i40e_asq_cmd_details*) ; 
 int /*<<< orphan*/  i40e_fill_default_direct_cmd_desc (struct i40e_aq_desc*,int /*<<< orphan*/ ) ; 

enum i40e_status_code i40e_aq_send_driver_version(struct i40e_hw *hw,
				struct i40e_driver_version *dv,
				struct i40e_asq_cmd_details *cmd_details)
{
	struct i40e_aq_desc desc;
	struct i40e_aqc_driver_version *cmd =
		(struct i40e_aqc_driver_version *)&desc.params.raw;
	enum i40e_status_code status;
	u16 len;

	if (dv == NULL)
		return I40E_ERR_PARAM;

	i40e_fill_default_direct_cmd_desc(&desc, i40e_aqc_opc_driver_version);

	desc.flags |= CPU_TO_LE16(I40E_AQ_FLAG_BUF | I40E_AQ_FLAG_RD);
	cmd->driver_major_ver = dv->major_version;
	cmd->driver_minor_ver = dv->minor_version;
	cmd->driver_build_ver = dv->build_version;
	cmd->driver_subbuild_ver = dv->subbuild_version;

	len = 0;
	while (len < sizeof(dv->driver_string) &&
	       (dv->driver_string[len] < 0x80) &&
	       dv->driver_string[len])
		len++;
	status = i40e_asq_send_command(hw, &desc, dv->driver_string,
				       len, cmd_details);

	return status;
}