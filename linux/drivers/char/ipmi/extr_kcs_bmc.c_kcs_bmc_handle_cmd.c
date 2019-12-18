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
typedef  int u8 ;
struct kcs_bmc {int data_in_avail; int /*<<< orphan*/  error; int /*<<< orphan*/  data_in_idx; int /*<<< orphan*/  phase; } ;

/* Variables and functions */
 int /*<<< orphan*/  KCS_ABORTED_BY_COMMAND ; 
#define  KCS_CMD_GET_STATUS_ABORT 130 
#define  KCS_CMD_WRITE_END 129 
#define  KCS_CMD_WRITE_START 128 
 int /*<<< orphan*/  KCS_ILLEGAL_CONTROL_CODE ; 
 int /*<<< orphan*/  KCS_NO_ERROR ; 
 int /*<<< orphan*/  KCS_PHASE_ABORT_ERROR1 ; 
 int /*<<< orphan*/  KCS_PHASE_WRITE_DATA ; 
 int /*<<< orphan*/  KCS_PHASE_WRITE_END_CMD ; 
 int /*<<< orphan*/  KCS_PHASE_WRITE_START ; 
 int /*<<< orphan*/  KCS_ZERO_DATA ; 
 int /*<<< orphan*/  WRITE_STATE ; 
 int /*<<< orphan*/  kcs_force_abort (struct kcs_bmc*) ; 
 int read_data (struct kcs_bmc*) ; 
 int /*<<< orphan*/  set_state (struct kcs_bmc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_data (struct kcs_bmc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kcs_bmc_handle_cmd(struct kcs_bmc *kcs_bmc)
{
	u8 cmd;

	set_state(kcs_bmc, WRITE_STATE);
	write_data(kcs_bmc, KCS_ZERO_DATA);

	cmd = read_data(kcs_bmc);
	switch (cmd) {
	case KCS_CMD_WRITE_START:
		kcs_bmc->phase = KCS_PHASE_WRITE_START;
		kcs_bmc->error = KCS_NO_ERROR;
		kcs_bmc->data_in_avail = false;
		kcs_bmc->data_in_idx = 0;
		break;

	case KCS_CMD_WRITE_END:
		if (kcs_bmc->phase != KCS_PHASE_WRITE_DATA) {
			kcs_force_abort(kcs_bmc);
			break;
		}

		kcs_bmc->phase = KCS_PHASE_WRITE_END_CMD;
		break;

	case KCS_CMD_GET_STATUS_ABORT:
		if (kcs_bmc->error == KCS_NO_ERROR)
			kcs_bmc->error = KCS_ABORTED_BY_COMMAND;

		kcs_bmc->phase = KCS_PHASE_ABORT_ERROR1;
		kcs_bmc->data_in_avail = false;
		kcs_bmc->data_in_idx = 0;
		break;

	default:
		kcs_force_abort(kcs_bmc);
		kcs_bmc->error = KCS_ILLEGAL_CONTROL_CODE;
		break;
	}
}