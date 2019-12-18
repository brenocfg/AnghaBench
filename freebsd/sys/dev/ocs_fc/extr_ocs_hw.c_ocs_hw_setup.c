#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_13__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  sli4_port_type_e ;
typedef  int /*<<< orphan*/  prop_buf ;
typedef  int /*<<< orphan*/  ocs_os_handle_t ;
struct TYPE_15__ {scalar_t__ n_eq; scalar_t__ n_cq; scalar_t__ n_rq; scalar_t__ n_wq; scalar_t__ n_mq; int /*<<< orphan*/  queue_topology; int /*<<< orphan*/  dif_mode; void* i_only_aab; int /*<<< orphan*/  auto_xfer_rdy_xri_cnt; int /*<<< orphan*/  n_io; int /*<<< orphan*/  rq_default_buffer_size; int /*<<< orphan*/  auto_xfer_rdy_app_tag_value; int /*<<< orphan*/  auto_xfer_rdy_app_tag_valid; int /*<<< orphan*/  auto_xfer_rdy_ref_tag_is_lba; int /*<<< orphan*/  auto_xfer_rdy_blk_size_chip; scalar_t__ dif_seed; int /*<<< orphan*/  speed; } ;
struct TYPE_16__ {scalar_t__ use_dif_sec_xri; scalar_t__ override_fcfi; } ;
struct TYPE_17__ {int first_domain_idx; int ulp_start; int ulp_max; int /*<<< orphan*/  os; TYPE_1__ config; TYPE_9__* qtop; int /*<<< orphan*/  sli; int /*<<< orphan*/  sec_hio_wait_list; TYPE_2__ workaround; int /*<<< orphan*/ * num_qentries; struct TYPE_17__* fcf_index_fcfi; struct TYPE_17__* domains; int /*<<< orphan*/  io_alloc_failed_count; int /*<<< orphan*/  io_abort_lock; int /*<<< orphan*/  io_lock; scalar_t__ cmd_head_count; int /*<<< orphan*/  cmd_pending; int /*<<< orphan*/  cmd_head; int /*<<< orphan*/  cmd_lock; void* hw_setup_called; } ;
typedef  TYPE_3__ ocs_hw_t ;
typedef  int /*<<< orphan*/  ocs_hw_rtn_e ;
struct TYPE_18__ {scalar_t__* entry_counts; } ;
struct TYPE_14__ {int /*<<< orphan*/  queue_topology_string; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FC_LINK_SPEED_AUTO_16_8_4 ; 
 scalar_t__ OCE_HW_MAX_NUM_MRQ_PAIRS ; 
 int /*<<< orphan*/  OCS_HW_AUTO_XFER_RDY_APP_TAG_VALID_DEFAULT ; 
 int /*<<< orphan*/  OCS_HW_AUTO_XFER_RDY_APP_TAG_VALUE_DEFAULT ; 
 int /*<<< orphan*/  OCS_HW_AUTO_XFER_RDY_BLK_SIZE_DEFAULT ; 
 int /*<<< orphan*/  OCS_HW_AUTO_XFER_RDY_REF_TAG_IS_LBA_DEFAULT ; 
 int /*<<< orphan*/  OCS_HW_DIF_MODE_SEPARATE ; 
 scalar_t__ OCS_HW_MAX_NUM_CQ ; 
 scalar_t__ OCS_HW_MAX_NUM_EQ ; 
 scalar_t__ OCS_HW_MAX_NUM_MQ ; 
 scalar_t__ OCS_HW_MAX_NUM_WQ ; 
 int /*<<< orphan*/  OCS_HW_RQ_SIZE_PAYLOAD ; 
 int /*<<< orphan*/  OCS_HW_RTN_ERROR ; 
 int /*<<< orphan*/  OCS_HW_RTN_SUCCESS ; 
 size_t QTOP_CQ ; 
 size_t QTOP_EQ ; 
 size_t QTOP_MQ ; 
 size_t QTOP_RQ ; 
 size_t QTOP_WQ ; 
 int /*<<< orphan*/  SLI4_CB_FIP ; 
 int /*<<< orphan*/  SLI4_CB_LINK ; 
 scalar_t__ SLI4_IF_TYPE_LANCER_FC_ETH ; 
 int /*<<< orphan*/  SLI_RSRC_FCOE_XRI ; 
 void* TRUE ; 
 TYPE_13__ hw_global ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  ocs_atomic_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_command_ctx_t ; 
 scalar_t__ ocs_get_property (char*,char*,int) ; 
 int /*<<< orphan*/  ocs_hw_adjust_wqs (TYPE_3__*) ; 
 int /*<<< orphan*/  ocs_hw_cb_fip ; 
 int /*<<< orphan*/  ocs_hw_cb_link ; 
 int /*<<< orphan*/  ocs_hw_io_t ; 
 int /*<<< orphan*/  ocs_hw_link_event_init (TYPE_3__*) ; 
 TYPE_9__* ocs_hw_qtop_parse (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_hw_read_max_dump_size (TYPE_3__*) ; 
 int /*<<< orphan*/  ocs_hw_workaround_setup (TYPE_3__*) ; 
 int /*<<< orphan*/  ocs_instance (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_list_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_lock_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_log_crit (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ocs_log_debug (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ocs_memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocs_strtoul (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sli_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ sli_get_if_type (int /*<<< orphan*/ *) ; 
 scalar_t__ sli_get_is_dual_ulp_capable (int /*<<< orphan*/ *) ; 
 scalar_t__ sli_get_is_ulp_enabled (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sli_get_max_qentries (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  sli_get_max_rsrc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sli_is_dif_inline_capable (int /*<<< orphan*/ *) ; 
 scalar_t__ sli_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ocs_hw_rtn_e
ocs_hw_setup(ocs_hw_t *hw, ocs_os_handle_t os, sli4_port_type_e port_type)
{
	uint32_t i;
	char prop_buf[32];

	if (hw == NULL) {
		ocs_log_err(os, "bad parameter(s) hw=%p\n", hw);
		return OCS_HW_RTN_ERROR;
	}

	if (hw->hw_setup_called) {
		/* Setup run-time workarounds.
		 * Call for each setup, to allow for hw_war_version
		 */
		ocs_hw_workaround_setup(hw);
		return OCS_HW_RTN_SUCCESS;
	}

	/*
	 * ocs_hw_init() relies on NULL pointers indicating that a structure
	 * needs allocation. If a structure is non-NULL, ocs_hw_init() won't
	 * free/realloc that memory
	 */
	ocs_memset(hw, 0, sizeof(ocs_hw_t));

	hw->hw_setup_called = TRUE;

	hw->os = os;

	ocs_lock_init(hw->os, &hw->cmd_lock, "HW_cmd_lock[%d]", ocs_instance(hw->os));
	ocs_list_init(&hw->cmd_head, ocs_command_ctx_t, link);
	ocs_list_init(&hw->cmd_pending, ocs_command_ctx_t, link);
	hw->cmd_head_count = 0;

	ocs_lock_init(hw->os, &hw->io_lock, "HW_io_lock[%d]", ocs_instance(hw->os));
	ocs_lock_init(hw->os, &hw->io_abort_lock, "HW_io_abort_lock[%d]", ocs_instance(hw->os));

	ocs_atomic_init(&hw->io_alloc_failed_count, 0);

	hw->config.speed = FC_LINK_SPEED_AUTO_16_8_4;
	hw->config.dif_seed = 0;
	hw->config.auto_xfer_rdy_blk_size_chip = OCS_HW_AUTO_XFER_RDY_BLK_SIZE_DEFAULT;
	hw->config.auto_xfer_rdy_ref_tag_is_lba = OCS_HW_AUTO_XFER_RDY_REF_TAG_IS_LBA_DEFAULT;
	hw->config.auto_xfer_rdy_app_tag_valid =  OCS_HW_AUTO_XFER_RDY_APP_TAG_VALID_DEFAULT;
	hw->config.auto_xfer_rdy_app_tag_value = OCS_HW_AUTO_XFER_RDY_APP_TAG_VALUE_DEFAULT;


	if (sli_setup(&hw->sli, hw->os, port_type)) {
		ocs_log_err(hw->os, "SLI setup failed\n");
		return OCS_HW_RTN_ERROR;
	}

	ocs_memset(hw->domains, 0, sizeof(hw->domains));

	ocs_memset(hw->fcf_index_fcfi, 0, sizeof(hw->fcf_index_fcfi));

	ocs_hw_link_event_init(hw);

	sli_callback(&hw->sli, SLI4_CB_LINK, ocs_hw_cb_link, hw);
	sli_callback(&hw->sli, SLI4_CB_FIP, ocs_hw_cb_fip, hw);

	/*
	 * Set all the queue sizes to the maximum allowed. These values may
	 * be changes later by the adjust and workaround functions.
	 */
	for (i = 0; i < ARRAY_SIZE(hw->num_qentries); i++) {
		hw->num_qentries[i] = sli_get_max_qentries(&hw->sli, i);
	}

	/*
	 * The RQ assignment for RQ pair mode.
	 */
	hw->config.rq_default_buffer_size = OCS_HW_RQ_SIZE_PAYLOAD;
	hw->config.n_io = sli_get_max_rsrc(&hw->sli, SLI_RSRC_FCOE_XRI);
	if (ocs_get_property("auto_xfer_rdy_xri_cnt", prop_buf, sizeof(prop_buf)) == 0) {
		hw->config.auto_xfer_rdy_xri_cnt = ocs_strtoul(prop_buf, 0, 0);
	}

	/* by default, enable initiator-only auto-ABTS emulation */
	hw->config.i_only_aab = TRUE;

	/* Setup run-time workarounds */
	ocs_hw_workaround_setup(hw);

	/* HW_WORKAROUND_OVERRIDE_FCFI_IN_SRB */
	if (hw->workaround.override_fcfi) {
		hw->first_domain_idx = -1;
	}

	/* Must be done after the workaround setup */
	if (SLI4_IF_TYPE_LANCER_FC_ETH == sli_get_if_type(&hw->sli)) {
		(void)ocs_hw_read_max_dump_size(hw);
	}

	/* calculate the number of WQs required. */
	ocs_hw_adjust_wqs(hw);

	/* Set the default dif mode */
	if (! sli_is_dif_inline_capable(&hw->sli)) {
		ocs_log_test(hw->os, "not inline capable, setting mode to separate\n");
		hw->config.dif_mode = OCS_HW_DIF_MODE_SEPARATE;
	}
	/* Workaround: BZ 161832 */
	if (hw->workaround.use_dif_sec_xri) {
		ocs_list_init(&hw->sec_hio_wait_list, ocs_hw_io_t, link);
	}

	/*
	 * Figure out the starting and max ULP to spread the WQs across the
	 * ULPs.
	 */
	if (sli_get_is_dual_ulp_capable(&hw->sli)) {
		if (sli_get_is_ulp_enabled(&hw->sli, 0) &&
		    sli_get_is_ulp_enabled(&hw->sli, 1)) {
			hw->ulp_start = 0;
			hw->ulp_max   = 1;
		} else if (sli_get_is_ulp_enabled(&hw->sli, 0)) {
			hw->ulp_start = 0;
			hw->ulp_max   = 0;
		} else {
			hw->ulp_start = 1;
			hw->ulp_max   = 1;
		}
	} else {
		if (sli_get_is_ulp_enabled(&hw->sli, 0)) {
			hw->ulp_start = 0;
			hw->ulp_max   = 0;
		} else {
			hw->ulp_start = 1;
			hw->ulp_max   = 1;
		}
	}
	ocs_log_debug(hw->os, "ulp_start %d, ulp_max %d\n",
		hw->ulp_start, hw->ulp_max);
	hw->config.queue_topology = hw_global.queue_topology_string;

	hw->qtop = ocs_hw_qtop_parse(hw, hw->config.queue_topology);

	hw->config.n_eq = hw->qtop->entry_counts[QTOP_EQ];
	hw->config.n_cq = hw->qtop->entry_counts[QTOP_CQ];
	hw->config.n_rq = hw->qtop->entry_counts[QTOP_RQ];
	hw->config.n_wq = hw->qtop->entry_counts[QTOP_WQ];
	hw->config.n_mq = hw->qtop->entry_counts[QTOP_MQ];

	/* Verify qtop configuration against driver supported configuration */
	if (hw->config.n_rq > OCE_HW_MAX_NUM_MRQ_PAIRS) {
		ocs_log_crit(hw->os, "Max supported MRQ pairs = %d\n",
				OCE_HW_MAX_NUM_MRQ_PAIRS);
		return OCS_HW_RTN_ERROR;
	}

	if (hw->config.n_eq > OCS_HW_MAX_NUM_EQ) {
		ocs_log_crit(hw->os, "Max supported EQs = %d\n",
				OCS_HW_MAX_NUM_EQ);
		return OCS_HW_RTN_ERROR;
	}
	
	if (hw->config.n_cq > OCS_HW_MAX_NUM_CQ) {
		ocs_log_crit(hw->os, "Max supported CQs = %d\n",
				OCS_HW_MAX_NUM_CQ);
		return OCS_HW_RTN_ERROR;
	}

	if (hw->config.n_wq > OCS_HW_MAX_NUM_WQ) {
		ocs_log_crit(hw->os, "Max supported WQs = %d\n",
				OCS_HW_MAX_NUM_WQ);
		return OCS_HW_RTN_ERROR;
	}

	if (hw->config.n_mq > OCS_HW_MAX_NUM_MQ) {
		ocs_log_crit(hw->os, "Max supported MQs = %d\n",
				OCS_HW_MAX_NUM_MQ);
		return OCS_HW_RTN_ERROR;
	}

	return OCS_HW_RTN_SUCCESS;
}