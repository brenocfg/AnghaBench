#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  scalar_t__ u16 ;
struct TYPE_10__ {int phy_types; } ;
struct TYPE_9__ {scalar_t__ asq_last_status; scalar_t__ api_maj_ver; scalar_t__ api_min_ver; } ;
struct TYPE_8__ {scalar_t__ type; } ;
struct i40e_hw {TYPE_5__ phy; TYPE_4__ aq; TYPE_3__ mac; } ;
struct i40e_asq_cmd_details {int dummy; } ;
struct i40e_aq_get_phy_abilities_resp {scalar_t__ phy_type_ext; int /*<<< orphan*/  phy_type; } ;
struct TYPE_6__ {int /*<<< orphan*/  param0; } ;
struct TYPE_7__ {TYPE_1__ external; } ;
struct i40e_aq_desc {TYPE_2__ params; int /*<<< orphan*/  flags; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_TO_LE16 (scalar_t__) ; 
 int /*<<< orphan*/  CPU_TO_LE32 (int /*<<< orphan*/ ) ; 
 scalar_t__ I40E_AQ_FLAG_BUF ; 
 scalar_t__ I40E_AQ_FLAG_LB ; 
 scalar_t__ I40E_AQ_LARGE_BUF ; 
 int /*<<< orphan*/  I40E_AQ_PHY_REPORT_INITIAL_VALUES ; 
 int /*<<< orphan*/  I40E_AQ_PHY_REPORT_QUALIFIED_MODULES ; 
 scalar_t__ I40E_AQ_RC_EAGAIN ; 
 scalar_t__ I40E_AQ_RC_EIO ; 
 scalar_t__ I40E_AQ_RC_OK ; 
 int I40E_ERR_PARAM ; 
 int I40E_ERR_TIMEOUT ; 
 int I40E_ERR_UNKNOWN_PHY ; 
 scalar_t__ I40E_FW_API_VERSION_MAJOR ; 
 scalar_t__ I40E_MAC_XL710 ; 
 scalar_t__ I40E_MAX_PHY_TIMEOUT ; 
 scalar_t__ I40E_MINOR_VER_GET_LINK_INFO_XL710 ; 
 int I40E_SUCCESS ; 
 int LE32_TO_CPU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int i40e_aq_get_link_info (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_aqc_opc_get_phy_abilities ; 
 int i40e_asq_send_command (struct i40e_hw*,struct i40e_aq_desc*,struct i40e_aq_get_phy_abilities_resp*,scalar_t__,struct i40e_asq_cmd_details*) ; 
 int /*<<< orphan*/  i40e_fill_default_direct_cmd_desc (struct i40e_aq_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_msec_delay (int) ; 

enum i40e_status_code i40e_aq_get_phy_capabilities(struct i40e_hw *hw,
			bool qualified_modules, bool report_init,
			struct i40e_aq_get_phy_abilities_resp *abilities,
			struct i40e_asq_cmd_details *cmd_details)
{
	struct i40e_aq_desc desc;
	enum i40e_status_code status;
	u16 max_delay = I40E_MAX_PHY_TIMEOUT, total_delay = 0;
	u16 abilities_size = sizeof(struct i40e_aq_get_phy_abilities_resp);

	if (!abilities)
		return I40E_ERR_PARAM;

	do {
		i40e_fill_default_direct_cmd_desc(&desc,
					       i40e_aqc_opc_get_phy_abilities);

		desc.flags |= CPU_TO_LE16((u16)I40E_AQ_FLAG_BUF);
		if (abilities_size > I40E_AQ_LARGE_BUF)
			desc.flags |= CPU_TO_LE16((u16)I40E_AQ_FLAG_LB);

		if (qualified_modules)
			desc.params.external.param0 |=
			CPU_TO_LE32(I40E_AQ_PHY_REPORT_QUALIFIED_MODULES);

		if (report_init)
			desc.params.external.param0 |=
			CPU_TO_LE32(I40E_AQ_PHY_REPORT_INITIAL_VALUES);

		status = i40e_asq_send_command(hw, &desc, abilities,
					       abilities_size, cmd_details);

		if (status != I40E_SUCCESS)
			break;

		if (hw->aq.asq_last_status == I40E_AQ_RC_EIO) {
			status = I40E_ERR_UNKNOWN_PHY;
			break;
		} else if (hw->aq.asq_last_status == I40E_AQ_RC_EAGAIN) {
			i40e_msec_delay(1);
			total_delay++;
			status = I40E_ERR_TIMEOUT;
		}
	} while ((hw->aq.asq_last_status != I40E_AQ_RC_OK) &&
		 (total_delay < max_delay));

	if (status != I40E_SUCCESS)
		return status;

	if (report_init) {
		if (hw->mac.type ==  I40E_MAC_XL710 &&
		    hw->aq.api_maj_ver == I40E_FW_API_VERSION_MAJOR &&
		    hw->aq.api_min_ver >= I40E_MINOR_VER_GET_LINK_INFO_XL710) {
			status = i40e_aq_get_link_info(hw, TRUE, NULL, NULL);
		} else {
			hw->phy.phy_types = LE32_TO_CPU(abilities->phy_type);
			hw->phy.phy_types |=
					((u64)abilities->phy_type_ext << 32);
		}
	}

	return status;
}