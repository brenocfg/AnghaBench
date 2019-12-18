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
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  tmp ;
struct i40e_link_status {int phy_type; int link_speed; int an_info; int fec_info; int loopback; int pacing; void* lse_enable; void* crc_enable; int /*<<< orphan*/  max_frame_size; int /*<<< orphan*/  ext_info; int /*<<< orphan*/  link_info; } ;
struct TYPE_10__ {int phy_types; void* get_link_info; int /*<<< orphan*/  media_type; struct i40e_link_status link_info_old; struct i40e_link_status link_info; } ;
struct TYPE_9__ {int fw_maj_ver; int fw_min_ver; scalar_t__ api_maj_ver; int api_min_ver; } ;
struct TYPE_8__ {scalar_t__ type; } ;
struct TYPE_7__ {int /*<<< orphan*/  current_mode; } ;
struct i40e_hw {TYPE_5__ phy; TYPE_4__ aq; TYPE_3__ mac; TYPE_2__ fc; } ;
struct i40e_asq_cmd_details {int dummy; } ;
struct i40e_aqc_get_link_status {int command_flags; int an_info; int config; int loopback; scalar_t__ link_type_ext; struct i40e_link_status* link_type; int /*<<< orphan*/  max_frame_size; int /*<<< orphan*/  ext_info; int /*<<< orphan*/  link_info; scalar_t__ link_speed; scalar_t__ phy_type; } ;
struct TYPE_6__ {int /*<<< orphan*/  raw; } ;
struct i40e_aq_desc {TYPE_1__ params; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;
typedef  enum i40e_aq_phy_type { ____Placeholder_i40e_aq_phy_type } i40e_aq_phy_type ;
typedef  enum i40e_aq_link_speed { ____Placeholder_i40e_aq_link_speed } i40e_aq_link_speed ;
typedef  struct i40e_link_status __le32 ;

/* Variables and functions */
 int CPU_TO_LE16 (int /*<<< orphan*/ ) ; 
 void* FALSE ; 
 int I40E_AQ_CONFIG_CRC_ENA ; 
 int I40E_AQ_CONFIG_FEC_KR_ENA ; 
 int I40E_AQ_CONFIG_FEC_RS_ENA ; 
 int I40E_AQ_CONFIG_PACING_MASK ; 
 int I40E_AQ_LINK_PAUSE_RX ; 
 int I40E_AQ_LINK_PAUSE_TX ; 
 int I40E_AQ_LOOPBACK_MASK ; 
 int /*<<< orphan*/  I40E_AQ_LSE_DISABLE ; 
 int /*<<< orphan*/  I40E_AQ_LSE_ENABLE ; 
 int /*<<< orphan*/  I40E_AQ_LSE_IS_ENABLED ; 
 int /*<<< orphan*/  I40E_FC_FULL ; 
 int /*<<< orphan*/  I40E_FC_NONE ; 
 int /*<<< orphan*/  I40E_FC_RX_PAUSE ; 
 int /*<<< orphan*/  I40E_FC_TX_PAUSE ; 
 scalar_t__ I40E_FW_API_VERSION_MAJOR ; 
 scalar_t__ I40E_MAC_XL710 ; 
 int /*<<< orphan*/  I40E_NONDMA_TO_NONDMA ; 
 int I40E_PHY_TYPE_10GBASE_SFPP_CU ; 
 int I40E_SUCCESS ; 
 int /*<<< orphan*/  LE16_TO_CPU (int /*<<< orphan*/ ) ; 
 int LE32_TO_CPU (struct i40e_link_status) ; 
 void* TRUE ; 
 int /*<<< orphan*/  i40e_aqc_opc_get_link_status ; 
 int i40e_asq_send_command (struct i40e_hw*,struct i40e_aq_desc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct i40e_asq_cmd_details*) ; 
 int /*<<< orphan*/  i40e_fill_default_direct_cmd_desc (struct i40e_aq_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_get_media_type (struct i40e_hw*) ; 
 int /*<<< orphan*/  i40e_memcpy (struct i40e_link_status*,struct i40e_link_status*,int,int /*<<< orphan*/ ) ; 

enum i40e_status_code i40e_aq_get_link_info(struct i40e_hw *hw,
				bool enable_lse, struct i40e_link_status *link,
				struct i40e_asq_cmd_details *cmd_details)
{
	struct i40e_aq_desc desc;
	struct i40e_aqc_get_link_status *resp =
		(struct i40e_aqc_get_link_status *)&desc.params.raw;
	struct i40e_link_status *hw_link_info = &hw->phy.link_info;
	enum i40e_status_code status;
	bool tx_pause, rx_pause;
	u16 command_flags;

	i40e_fill_default_direct_cmd_desc(&desc, i40e_aqc_opc_get_link_status);

	if (enable_lse)
		command_flags = I40E_AQ_LSE_ENABLE;
	else
		command_flags = I40E_AQ_LSE_DISABLE;
	resp->command_flags = CPU_TO_LE16(command_flags);

	status = i40e_asq_send_command(hw, &desc, NULL, 0, cmd_details);

	if (status != I40E_SUCCESS)
		goto aq_get_link_info_exit;

	/* save off old link status information */
	i40e_memcpy(&hw->phy.link_info_old, hw_link_info,
		    sizeof(*hw_link_info), I40E_NONDMA_TO_NONDMA);

	/* update link status */
	hw_link_info->phy_type = (enum i40e_aq_phy_type)resp->phy_type;
	hw->phy.media_type = i40e_get_media_type(hw);
	hw_link_info->link_speed = (enum i40e_aq_link_speed)resp->link_speed;
	hw_link_info->link_info = resp->link_info;
	hw_link_info->an_info = resp->an_info;
	hw_link_info->fec_info = resp->config & (I40E_AQ_CONFIG_FEC_KR_ENA |
						 I40E_AQ_CONFIG_FEC_RS_ENA);
	hw_link_info->ext_info = resp->ext_info;
	hw_link_info->loopback = resp->loopback & I40E_AQ_LOOPBACK_MASK;
	hw_link_info->max_frame_size = LE16_TO_CPU(resp->max_frame_size);
	hw_link_info->pacing = resp->config & I40E_AQ_CONFIG_PACING_MASK;

	/* update fc info */
	tx_pause = !!(resp->an_info & I40E_AQ_LINK_PAUSE_TX);
	rx_pause = !!(resp->an_info & I40E_AQ_LINK_PAUSE_RX);
	if (tx_pause & rx_pause)
		hw->fc.current_mode = I40E_FC_FULL;
	else if (tx_pause)
		hw->fc.current_mode = I40E_FC_TX_PAUSE;
	else if (rx_pause)
		hw->fc.current_mode = I40E_FC_RX_PAUSE;
	else
		hw->fc.current_mode = I40E_FC_NONE;

	if (resp->config & I40E_AQ_CONFIG_CRC_ENA)
		hw_link_info->crc_enable = TRUE;
	else
		hw_link_info->crc_enable = FALSE;

	if (resp->command_flags & CPU_TO_LE16(I40E_AQ_LSE_IS_ENABLED))
		hw_link_info->lse_enable = TRUE;
	else
		hw_link_info->lse_enable = FALSE;

	if ((hw->mac.type == I40E_MAC_XL710) &&
	    (hw->aq.fw_maj_ver < 4 || (hw->aq.fw_maj_ver == 4 &&
	     hw->aq.fw_min_ver < 40)) && hw_link_info->phy_type == 0xE)
		hw_link_info->phy_type = I40E_PHY_TYPE_10GBASE_SFPP_CU;

	if (hw->aq.api_maj_ver == I40E_FW_API_VERSION_MAJOR &&
	    hw->aq.api_min_ver >= 7) {
		__le32 tmp;

		i40e_memcpy(&tmp, resp->link_type, sizeof(tmp),
			    I40E_NONDMA_TO_NONDMA);
		hw->phy.phy_types = LE32_TO_CPU(tmp);
		hw->phy.phy_types |= ((u64)resp->link_type_ext << 32);
	}

	/* save link status information */
	if (link)
		i40e_memcpy(link, hw_link_info, sizeof(*hw_link_info),
			    I40E_NONDMA_TO_NONDMA);

	/* flag cleared so helper functions don't call AQ again */
	hw->phy.get_link_info = FALSE;

aq_get_link_info_exit:
	return status;
}