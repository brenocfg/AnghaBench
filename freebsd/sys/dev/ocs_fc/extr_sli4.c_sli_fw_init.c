#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_10__ {int /*<<< orphan*/  virt; } ;
struct TYPE_11__ {int if_type; int /*<<< orphan*/  os; TYPE_1__ bmbx; } ;
typedef  TYPE_2__ sli4_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_BMBX_DELAY_US ; 
 int /*<<< orphan*/  SLI4_BMBX_SIZE ; 
 int /*<<< orphan*/  SLI4_FW_READY_TIMEOUT_MSEC ; 
#define  SLI4_IF_TYPE_BE3_SKH_PF 130 
#define  SLI4_IF_TYPE_BE3_SKH_VF 129 
#define  SLI4_IF_TYPE_LANCER_FC_ETH 128 
 int /*<<< orphan*/  SLI4_SLIPORT_CONTROL_BIG_ENDIAN ; 
 int /*<<< orphan*/  SLI4_SLIPORT_CONTROL_LITTLE_ENDIAN ; 
 int /*<<< orphan*/  ocs_log_crit (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sli_bmbx_command (TYPE_2__*) ; 
 int /*<<< orphan*/  sli_bmbx_wait (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sli_cmd_fw_initialize (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sli_common_function_reset (TYPE_2__*) ; 
 int /*<<< orphan*/  sli_sliport_control (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sli_wait_for_fw_ready (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t
sli_fw_init(sli4_t *sli4)
{
	uint32_t ready;
	uint32_t endian;

	/*
	 * Is firmware ready for operation?
	 */
	ready = sli_wait_for_fw_ready(sli4, SLI4_FW_READY_TIMEOUT_MSEC);
	if (!ready) {
		ocs_log_crit(sli4->os, "FW status is NOT ready\n");
		return -1;
	}

	/*
	 * Reset port to a known state
	 */
	switch (sli4->if_type) {
	case SLI4_IF_TYPE_BE3_SKH_PF:
	case SLI4_IF_TYPE_BE3_SKH_VF:
		/* No SLIPORT_CONTROL register so use command sequence instead */
		if (sli_bmbx_wait(sli4, SLI4_BMBX_DELAY_US)) {
			ocs_log_crit(sli4->os, "bootstrap mailbox not ready\n");
			return -1;
		}

		if (sli_cmd_fw_initialize(sli4, sli4->bmbx.virt, SLI4_BMBX_SIZE)) {
			if (sli_bmbx_command(sli4)) {
				ocs_log_crit(sli4->os, "bootstrap mailbox write fail (FW_INIT)\n");
				return -1;
			}
		} else {
			ocs_log_crit(sli4->os, "bad FW_INIT write\n");
			return -1;
		}

		if (sli_common_function_reset(sli4)) {
			ocs_log_err(sli4->os, "bad COM_FUNC_RESET write\n");
			return -1;
		}
		break;
	case SLI4_IF_TYPE_LANCER_FC_ETH:
#if BYTE_ORDER == LITTLE_ENDIAN
		endian = SLI4_SLIPORT_CONTROL_LITTLE_ENDIAN;
#else
		endian = SLI4_SLIPORT_CONTROL_BIG_ENDIAN;
#endif

		if (sli_sliport_control(sli4, endian))
			return -1;
		break;
	default:
		ocs_log_test(sli4->os, "if_type %d not supported\n", sli4->if_type);
		return -1;
	}

	return 0;
}