#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {TYPE_1__* isp_devparam; int /*<<< orphan*/  isp_max_queue_depth; int /*<<< orphan*/  isp_selection_timeout; void* isp_cmd_dma_burst_enable; void* isp_data_dma_burst_enabl; int /*<<< orphan*/  isp_data_line_active_neg; int /*<<< orphan*/  isp_req_ack_active_neg; int /*<<< orphan*/  isp_async_data_setup; int /*<<< orphan*/  isp_retry_delay; int /*<<< orphan*/  isp_retry_count; int /*<<< orphan*/  isp_bus_reset_delay; int /*<<< orphan*/  isp_initiator_id; int /*<<< orphan*/  isp_fifo_threshold; } ;
typedef  TYPE_2__ sdparam ;
struct TYPE_9__ {int isp_confopts; } ;
typedef  TYPE_3__ ispsoftc_t ;
struct TYPE_7__ {int /*<<< orphan*/  nvrm_flags; int /*<<< orphan*/  goal_flags; int /*<<< orphan*/  nvrm_period; int /*<<< orphan*/  goal_period; int /*<<< orphan*/  nvrm_offset; int /*<<< orphan*/  goal_offset; scalar_t__ actv_flags; int /*<<< orphan*/  exc_throttle; int /*<<< orphan*/  dev_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPARM_ARQ ; 
 int /*<<< orphan*/  DPARM_DISC ; 
 int /*<<< orphan*/  DPARM_PARITY ; 
 int /*<<< orphan*/  DPARM_RENEG ; 
 int /*<<< orphan*/  DPARM_SYNC ; 
 int /*<<< orphan*/  DPARM_TQING ; 
 int /*<<< orphan*/  DPARM_WIDE ; 
 int /*<<< orphan*/  ISP1080_NVRAM_ASYNC_DATA_SETUP_TIME (int /*<<< orphan*/ *,int) ; 
 void* ISP1080_NVRAM_BURST_ENABLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP1080_NVRAM_BUS_RESET_DELAY (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ISP1080_NVRAM_BUS_RETRY_COUNT (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ISP1080_NVRAM_BUS_RETRY_DELAY (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ISP1080_NVRAM_DATA_LINE_ACTIVE_NEGATION (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ISP1080_NVRAM_FIFO_THRESHOLD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP1080_NVRAM_INITIATOR_ID (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ISP1080_NVRAM_MAX_QUEUE_DEPTH (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ISP1080_NVRAM_REQ_ACK_ACTIVE_NEGATION (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ISP1080_NVRAM_SELECTION_TIMEOUT (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ISP1080_NVRAM_TGT_DEVICE_ENABLE (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ ISP1080_NVRAM_TGT_DISC (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ISP1080_NVRAM_TGT_EXEC_THROTTLE (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ ISP1080_NVRAM_TGT_PARITY (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ ISP1080_NVRAM_TGT_RENEG (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ ISP1080_NVRAM_TGT_SYNC (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ISP1080_NVRAM_TGT_SYNC_OFFSET (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ISP1080_NVRAM_TGT_SYNC_PERIOD (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ ISP1080_NVRAM_TGT_TQING (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ ISP1080_NVRAM_TGT_WIDE (int /*<<< orphan*/ *,int,int) ; 
 int ISP_CFG_OWNLOOPID ; 
 int MAX_TARGETS ; 
 TYPE_2__* SDPARAM (TYPE_3__*,int) ; 

__attribute__((used)) static void
isp_parse_nvram_1080(ispsoftc_t *isp, int bus, uint8_t *nvram_data)
{
	sdparam *sdp = SDPARAM(isp, bus);
	int tgt;

	sdp->isp_fifo_threshold =
	    ISP1080_NVRAM_FIFO_THRESHOLD(nvram_data);

	if ((isp->isp_confopts & ISP_CFG_OWNLOOPID) == 0)
		sdp->isp_initiator_id = ISP1080_NVRAM_INITIATOR_ID(nvram_data, bus);

	sdp->isp_bus_reset_delay =
	    ISP1080_NVRAM_BUS_RESET_DELAY(nvram_data, bus);

	sdp->isp_retry_count =
	    ISP1080_NVRAM_BUS_RETRY_COUNT(nvram_data, bus);

	sdp->isp_retry_delay =
	    ISP1080_NVRAM_BUS_RETRY_DELAY(nvram_data, bus);

	sdp->isp_async_data_setup =
	    ISP1080_NVRAM_ASYNC_DATA_SETUP_TIME(nvram_data, bus);

	sdp->isp_req_ack_active_neg =
	    ISP1080_NVRAM_REQ_ACK_ACTIVE_NEGATION(nvram_data, bus);

	sdp->isp_data_line_active_neg =
	    ISP1080_NVRAM_DATA_LINE_ACTIVE_NEGATION(nvram_data, bus);

	sdp->isp_data_dma_burst_enabl =
	    ISP1080_NVRAM_BURST_ENABLE(nvram_data);

	sdp->isp_cmd_dma_burst_enable =
	    ISP1080_NVRAM_BURST_ENABLE(nvram_data);

	sdp->isp_selection_timeout =
	    ISP1080_NVRAM_SELECTION_TIMEOUT(nvram_data, bus);

	sdp->isp_max_queue_depth =
	     ISP1080_NVRAM_MAX_QUEUE_DEPTH(nvram_data, bus);

	for (tgt = 0; tgt < MAX_TARGETS; tgt++) {
		sdp->isp_devparam[tgt].dev_enable =
		    ISP1080_NVRAM_TGT_DEVICE_ENABLE(nvram_data, tgt, bus);
		sdp->isp_devparam[tgt].exc_throttle =
			ISP1080_NVRAM_TGT_EXEC_THROTTLE(nvram_data, tgt, bus);
		sdp->isp_devparam[tgt].nvrm_offset =
			ISP1080_NVRAM_TGT_SYNC_OFFSET(nvram_data, tgt, bus);
		sdp->isp_devparam[tgt].nvrm_period =
			ISP1080_NVRAM_TGT_SYNC_PERIOD(nvram_data, tgt, bus);
		sdp->isp_devparam[tgt].nvrm_flags = 0;
		if (ISP1080_NVRAM_TGT_RENEG(nvram_data, tgt, bus))
			sdp->isp_devparam[tgt].nvrm_flags |= DPARM_RENEG;
		sdp->isp_devparam[tgt].nvrm_flags |= DPARM_ARQ;
		if (ISP1080_NVRAM_TGT_TQING(nvram_data, tgt, bus))
			sdp->isp_devparam[tgt].nvrm_flags |= DPARM_TQING;
		if (ISP1080_NVRAM_TGT_SYNC(nvram_data, tgt, bus))
			sdp->isp_devparam[tgt].nvrm_flags |= DPARM_SYNC;
		if (ISP1080_NVRAM_TGT_WIDE(nvram_data, tgt, bus))
			sdp->isp_devparam[tgt].nvrm_flags |= DPARM_WIDE;
		if (ISP1080_NVRAM_TGT_PARITY(nvram_data, tgt, bus))
			sdp->isp_devparam[tgt].nvrm_flags |= DPARM_PARITY;
		if (ISP1080_NVRAM_TGT_DISC(nvram_data, tgt, bus))
			sdp->isp_devparam[tgt].nvrm_flags |= DPARM_DISC;
		sdp->isp_devparam[tgt].actv_flags = 0;
		sdp->isp_devparam[tgt].goal_offset =
		    sdp->isp_devparam[tgt].nvrm_offset;
		sdp->isp_devparam[tgt].goal_period =
		    sdp->isp_devparam[tgt].nvrm_period;
		sdp->isp_devparam[tgt].goal_flags =
		    sdp->isp_devparam[tgt].nvrm_flags;
	}
}