#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_13__ {int retain_tsend_io_length; void* ignore_send_frame; void* sglc_misreported; void* fw_version_too_low; void* override_fcfi; void* use_dif_sec_xri; void* use_dif_quarantine; void* disable_dump_loc; void* disable_ar_tgt_dif; void* use_unregistered_rpi; int /*<<< orphan*/  unregistered_index; int /*<<< orphan*/  unregistered_rid; void* fwrev; } ;
struct TYPE_10__ {int /*<<< orphan*/ * count_method; scalar_t__* fw_name; } ;
struct TYPE_11__ {TYPE_1__ config; } ;
struct ocs_hw_s {char* hw_war_version; TYPE_6__ workaround; int /*<<< orphan*/  os; TYPE_2__ sli; int /*<<< orphan*/ * num_qentries; } ;
typedef  TYPE_2__ sli4_t ;
typedef  size_t sli4_qtype_e ;
struct TYPE_12__ {int workaround; int /*<<< orphan*/  value; } ;
typedef  TYPE_3__ hw_workaround_t ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (TYPE_3__*) ; 
 void* FALSE ; 
#define  HW_WORKAROUND_DISABLE_AR_TGT_DIF 142 
#define  HW_WORKAROUND_DISABLE_SET_DUMP_LOC 141 
#define  HW_WORKAROUND_FW_VERSION_TOO_LOW 140 
#define  HW_WORKAROUND_IGNORE_SEND_FRAME_CAPABLE 139 
#define  HW_WORKAROUND_MAX_QUEUE 138 
#define  HW_WORKAROUND_MAX_RQ 137 
#define  HW_WORKAROUND_OVERRIDE_FCFI_IN_SRB 136 
#define  HW_WORKAROUND_RETAIN_TSEND_IO_LENGTH 135 
#define  HW_WORKAROUND_RQE_COUNT_METHOD 134 
#define  HW_WORKAROUND_SGLC_MISREPORTED 133 
#define  HW_WORKAROUND_TEST 132 
#define  HW_WORKAROUND_USE_DIF_QUARANTINE 131 
#define  HW_WORKAROUND_USE_DIF_SEC_XRI 130 
#define  HW_WORKAROUND_USE_UNREGISTERD_RPI 129 
#define  HW_WORKAROUND_WQE_COUNT_METHOD 128 
 size_t SLI_QTYPE_EQ ; 
 size_t SLI_QTYPE_MAX ; 
 size_t SLI_QTYPE_RQ ; 
 size_t SLI_QTYPE_WQ ; 
 int /*<<< orphan*/  SLI_RSRC_FCOE_RPI ; 
 void* TRUE ; 
 TYPE_3__* hw_workarounds ; 
 scalar_t__ ocs_hw_workaround_match (struct ocs_hw_s*,TYPE_3__*) ; 
 int /*<<< orphan*/  ocs_log_debug (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ocs_memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 void* parse_fw_version (char*) ; 
 int /*<<< orphan*/  sli_calc_max_qentries (TYPE_2__*) ; 
 int /*<<< orphan*/  sli_resource_alloc (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
ocs_hw_workaround_setup(struct ocs_hw_s *hw)
{
	hw_workaround_t *w;
	sli4_t *sli4 = &hw->sli;
	uint32_t i;

	/* Initialize the workaround settings */
	ocs_memset(&hw->workaround, 0, sizeof(hw->workaround));

	/* If hw_war_version is non-null, then its a value that was set by a module parameter
	 * (sorry for the break in abstraction, but workarounds are ... well, workarounds)
	 */

	if (hw->hw_war_version) {
		hw->workaround.fwrev = parse_fw_version(hw->hw_war_version);
	} else {
		hw->workaround.fwrev = parse_fw_version((char*) sli4->config.fw_name[0]);
	}

	/* Walk the workaround list, if a match is found, then handle it */
	for (i = 0, w = hw_workarounds; i < ARRAY_SIZE(hw_workarounds); i++, w++) {
		if (ocs_hw_workaround_match(hw, w)) {
			switch(w->workaround) {

			case HW_WORKAROUND_TEST: {
				ocs_log_debug(hw->os, "Override: test: %d\n", w->value);
				break;
			}

			case HW_WORKAROUND_RETAIN_TSEND_IO_LENGTH: {
				ocs_log_debug(hw->os, "HW Workaround: retain TSEND IO length\n");
				hw->workaround.retain_tsend_io_length = 1;
				break;
			}
			case HW_WORKAROUND_MAX_QUEUE: {
				sli4_qtype_e q;

				ocs_log_debug(hw->os, "HW Workaround: override max_qentries: %d\n", w->value);
				for (q = SLI_QTYPE_EQ; q < SLI_QTYPE_MAX; q++) {
					if (hw->num_qentries[q] > w->value) {
						hw->num_qentries[q] = w->value;
					}
				}
				break;
			}
			case HW_WORKAROUND_MAX_RQ: {
				ocs_log_debug(hw->os, "HW Workaround: override RQ max_qentries: %d\n", w->value);
				if (hw->num_qentries[SLI_QTYPE_RQ] > w->value) {
					hw->num_qentries[SLI_QTYPE_RQ] = w->value;
				}
				break;
			}
			case HW_WORKAROUND_WQE_COUNT_METHOD: {
				ocs_log_debug(hw->os, "HW Workaround: set WQE count method=%d\n", w->value);
				sli4->config.count_method[SLI_QTYPE_WQ] = w->value;
				sli_calc_max_qentries(sli4);
				break;
			}
			case HW_WORKAROUND_RQE_COUNT_METHOD: {
				ocs_log_debug(hw->os, "HW Workaround: set RQE count method=%d\n", w->value);
				sli4->config.count_method[SLI_QTYPE_RQ] = w->value;
				sli_calc_max_qentries(sli4);
				break;
			}
			case HW_WORKAROUND_USE_UNREGISTERD_RPI:
				ocs_log_debug(hw->os, "HW Workaround: use unreg'd RPI if rnode->indicator == 0xFFFF\n");
				hw->workaround.use_unregistered_rpi = TRUE;
				/*
				 * Allocate an RPI that is never registered, to be used in the case where
				 * a node has been unregistered, and its indicator (RPI) value is set to 0xFFFF
				 */
				if (sli_resource_alloc(&hw->sli, SLI_RSRC_FCOE_RPI, &hw->workaround.unregistered_rid,
					&hw->workaround.unregistered_index)) {
					ocs_log_err(hw->os, "sli_resource_alloc unregistered RPI failed\n");
					hw->workaround.use_unregistered_rpi = FALSE;
				}
				break;
			case HW_WORKAROUND_DISABLE_AR_TGT_DIF:
				ocs_log_debug(hw->os, "HW Workaround: disable AR on T10-PI TSEND\n");
				hw->workaround.disable_ar_tgt_dif = TRUE;
				break;
			case HW_WORKAROUND_DISABLE_SET_DUMP_LOC:
				ocs_log_debug(hw->os, "HW Workaround: disable set_dump_loc\n");
				hw->workaround.disable_dump_loc = TRUE;
				break;
			case HW_WORKAROUND_USE_DIF_QUARANTINE:
				ocs_log_debug(hw->os, "HW Workaround: use DIF quarantine\n");
				hw->workaround.use_dif_quarantine = TRUE;
				break;
			case HW_WORKAROUND_USE_DIF_SEC_XRI:
				ocs_log_debug(hw->os, "HW Workaround: use DIF secondary xri\n");
				hw->workaround.use_dif_sec_xri = TRUE;
				break;
			case HW_WORKAROUND_OVERRIDE_FCFI_IN_SRB:
				ocs_log_debug(hw->os, "HW Workaround: override FCFI in SRB\n");
				hw->workaround.override_fcfi = TRUE;
				break;

			case HW_WORKAROUND_FW_VERSION_TOO_LOW:
				ocs_log_debug(hw->os, "HW Workaround: fw version is below the minimum for this driver\n");
				hw->workaround.fw_version_too_low = TRUE;
				break;
			case HW_WORKAROUND_SGLC_MISREPORTED:
				ocs_log_debug(hw->os, "HW Workaround: SGLC misreported - chaining is enabled\n");
				hw->workaround.sglc_misreported = TRUE;
				break;
			case HW_WORKAROUND_IGNORE_SEND_FRAME_CAPABLE:
				ocs_log_debug(hw->os, "HW Workaround: not SEND_FRAME capable - disabled\n");
				hw->workaround.ignore_send_frame = TRUE;
				break;
			} /* switch(w->workaround) */
		}
	}
}