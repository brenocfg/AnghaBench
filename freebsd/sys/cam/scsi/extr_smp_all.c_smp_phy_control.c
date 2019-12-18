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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct smp_phy_control_request {int phy; int phy_operation; int prog_min_phys_link_rate; int prog_max_phys_link_rate; int config_bits0; int pp_timeout_value; int /*<<< orphan*/  attached_device_name; int /*<<< orphan*/  update_pp_timeout; int /*<<< orphan*/  expected_exp_chg_cnt; int /*<<< orphan*/  request_len; int /*<<< orphan*/  response_len; int /*<<< orphan*/  function; int /*<<< orphan*/  frame_type; } ;
struct ccb_smpio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DIR_BOTH ; 
 scalar_t__ SMP_CRC_LEN ; 
 int /*<<< orphan*/  SMP_FRAME_TYPE_REQUEST ; 
 int /*<<< orphan*/  SMP_FUNC_PHY_CONTROL ; 
 int SMP_PC_PROG_MAX_PL_RATE_MASK ; 
 int SMP_PC_PROG_MAX_PL_RATE_SHIFT ; 
 int SMP_PC_PROG_MIN_PL_RATE_MASK ; 
 int SMP_PC_PROG_MIN_PL_RATE_SHIFT ; 
 int /*<<< orphan*/  SMP_PC_REQUEST_LEN ; 
 int /*<<< orphan*/  SMP_PC_RESPONSE_LEN ; 
 int /*<<< orphan*/  SMP_PC_UPDATE_PP_TIMEOUT ; 
 int /*<<< orphan*/  bzero (struct smp_phy_control_request*,int) ; 
 int /*<<< orphan*/  cam_fill_smpio (struct ccb_smpio*,int /*<<< orphan*/ ,void (*) (struct cam_periph*,union ccb*),int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_u64to8b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto2b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
smp_phy_control(struct ccb_smpio *smpio, uint32_t retries,
		void (*cbfcnp)(struct cam_periph *, union ccb *),
		struct smp_phy_control_request *request, int request_len,
		uint8_t *response, int response_len, int long_response,
		uint32_t expected_exp_change_count, int phy, int phy_op,
		int update_pp_timeout_val, uint64_t attached_device_name,
		int prog_min_prl, int prog_max_prl, int slumber_partial,
		int pp_timeout_value, uint32_t timeout)
{
	cam_fill_smpio(smpio,
		       retries,
		       cbfcnp,
		       /*flags*/CAM_DIR_BOTH,
		       (uint8_t *)request,
		       request_len - SMP_CRC_LEN,
		       response,
		       response_len,
		       timeout);

	bzero(request, sizeof(*request));

	request->frame_type = SMP_FRAME_TYPE_REQUEST;
	request->function = SMP_FUNC_PHY_CONTROL;
	request->response_len = long_response ? SMP_PC_RESPONSE_LEN : 0;
	request->request_len = long_response ? SMP_PC_REQUEST_LEN : 0;
	scsi_ulto2b(expected_exp_change_count, request->expected_exp_chg_cnt);
	request->phy = phy;
	request->phy_operation = phy_op;

	if (update_pp_timeout_val != 0)
		request->update_pp_timeout |= SMP_PC_UPDATE_PP_TIMEOUT;

	scsi_u64to8b(attached_device_name, request->attached_device_name);
	request->prog_min_phys_link_rate = (prog_min_prl <<
		SMP_PC_PROG_MIN_PL_RATE_SHIFT) & SMP_PC_PROG_MIN_PL_RATE_MASK;
	request->prog_max_phys_link_rate = (prog_max_prl <<
		SMP_PC_PROG_MAX_PL_RATE_SHIFT) & SMP_PC_PROG_MAX_PL_RATE_MASK;
	request->config_bits0 = slumber_partial;
	request->pp_timeout_value = pp_timeout_value;
}