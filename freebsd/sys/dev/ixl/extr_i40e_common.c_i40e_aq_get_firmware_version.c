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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct i40e_hw {int dummy; } ;
struct i40e_asq_cmd_details {int dummy; } ;
struct i40e_aqc_get_version {int /*<<< orphan*/  api_minor; int /*<<< orphan*/  api_major; int /*<<< orphan*/  fw_build; int /*<<< orphan*/  fw_minor; int /*<<< orphan*/  fw_major; } ;
struct TYPE_2__ {int /*<<< orphan*/  raw; } ;
struct i40e_aq_desc {TYPE_1__ params; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 int I40E_SUCCESS ; 
 int LE16_TO_CPU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LE32_TO_CPU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_aqc_opc_get_version ; 
 int i40e_asq_send_command (struct i40e_hw*,struct i40e_aq_desc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct i40e_asq_cmd_details*) ; 
 int /*<<< orphan*/  i40e_fill_default_direct_cmd_desc (struct i40e_aq_desc*,int /*<<< orphan*/ ) ; 

enum i40e_status_code i40e_aq_get_firmware_version(struct i40e_hw *hw,
				u16 *fw_major_version, u16 *fw_minor_version,
				u32 *fw_build,
				u16 *api_major_version, u16 *api_minor_version,
				struct i40e_asq_cmd_details *cmd_details)
{
	struct i40e_aq_desc desc;
	struct i40e_aqc_get_version *resp =
		(struct i40e_aqc_get_version *)&desc.params.raw;
	enum i40e_status_code status;

	i40e_fill_default_direct_cmd_desc(&desc, i40e_aqc_opc_get_version);

	status = i40e_asq_send_command(hw, &desc, NULL, 0, cmd_details);

	if (status == I40E_SUCCESS) {
		if (fw_major_version != NULL)
			*fw_major_version = LE16_TO_CPU(resp->fw_major);
		if (fw_minor_version != NULL)
			*fw_minor_version = LE16_TO_CPU(resp->fw_minor);
		if (fw_build != NULL)
			*fw_build = LE32_TO_CPU(resp->fw_build);
		if (api_major_version != NULL)
			*api_major_version = LE16_TO_CPU(resp->api_major);
		if (api_minor_version != NULL)
			*api_minor_version = LE16_TO_CPU(resp->api_minor);

		/* A workaround to fix the API version in SW */
		if (api_major_version && api_minor_version &&
		    fw_major_version && fw_minor_version &&
		    ((*api_major_version == 1) && (*api_minor_version == 1)) &&
		    (((*fw_major_version == 4) && (*fw_minor_version >= 2)) ||
		     (*fw_major_version > 4)))
			*api_minor_version = 2;
	}

	return status;
}