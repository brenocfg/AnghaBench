#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ t_Handle ;
struct TYPE_4__ {void* cntUnsupportedFormat; void* cntLengthErr; void* cntWredDiscard; void* cntRxOutOfBuffersDiscard; void* cntRxListDmaErr; void* cntRxFilterFrame; void* cntRxLargeFrame; void* cntRxBadFrame; void* cntDeallocBuf; void* cntDiscardFrame; void* cntFrame; void* cntRxPauseActivation; void* cntFifoUtil; void* cntDmaUtil; void* cntQueueUtil; void* cntTaskUtil; void* cntCycle; } ;
typedef  TYPE_1__ t_FmPortBmiStats ;
struct TYPE_5__ {scalar_t__ portType; } ;
typedef  TYPE_2__ t_FmPort ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  E_OK ; 
 void* FM_PORT_GetCounter (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e_FM_PORT_COUNTERS_CYCLE ; 
 int /*<<< orphan*/  e_FM_PORT_COUNTERS_DEALLOC_BUF ; 
 int /*<<< orphan*/  e_FM_PORT_COUNTERS_DISCARD_FRAME ; 
 int /*<<< orphan*/  e_FM_PORT_COUNTERS_DMA_UTIL ; 
 int /*<<< orphan*/  e_FM_PORT_COUNTERS_FIFO_UTIL ; 
 int /*<<< orphan*/  e_FM_PORT_COUNTERS_FRAME ; 
 int /*<<< orphan*/  e_FM_PORT_COUNTERS_LENGTH_ERR ; 
 int /*<<< orphan*/  e_FM_PORT_COUNTERS_QUEUE_UTIL ; 
 int /*<<< orphan*/  e_FM_PORT_COUNTERS_RX_BAD_FRAME ; 
 int /*<<< orphan*/  e_FM_PORT_COUNTERS_RX_FILTER_FRAME ; 
 int /*<<< orphan*/  e_FM_PORT_COUNTERS_RX_LARGE_FRAME ; 
 int /*<<< orphan*/  e_FM_PORT_COUNTERS_RX_LIST_DMA_ERR ; 
 int /*<<< orphan*/  e_FM_PORT_COUNTERS_RX_OUT_OF_BUFFERS_DISCARD ; 
 int /*<<< orphan*/  e_FM_PORT_COUNTERS_RX_PAUSE_ACTIVATION ; 
 int /*<<< orphan*/  e_FM_PORT_COUNTERS_TASK_UTIL ; 
 int /*<<< orphan*/  e_FM_PORT_COUNTERS_UNSUPPRTED_FORMAT ; 
 int /*<<< orphan*/  e_FM_PORT_COUNTERS_WRED_DISCARD ; 
 scalar_t__ e_FM_PORT_TYPE_OH_OFFLINE_PARSING ; 
 scalar_t__ e_FM_PORT_TYPE_RX ; 
 scalar_t__ e_FM_PORT_TYPE_RX_10G ; 
 scalar_t__ e_FM_PORT_TYPE_TX ; 
 scalar_t__ e_FM_PORT_TYPE_TX_10G ; 

t_Error FM_PORT_GetBmiCounters(t_Handle h_FmPort, t_FmPortBmiStats *p_BmiStats)
{
    t_FmPort *p_FmPort = (t_FmPort*)h_FmPort;

    if ((p_FmPort->portType == e_FM_PORT_TYPE_RX)
            || (p_FmPort->portType == e_FM_PORT_TYPE_RX_10G)){
        p_BmiStats->cntCycle =
            FM_PORT_GetCounter(h_FmPort, e_FM_PORT_COUNTERS_CYCLE);
            /* fmbm_rccn */
        p_BmiStats->cntTaskUtil =
            FM_PORT_GetCounter(h_FmPort, e_FM_PORT_COUNTERS_TASK_UTIL);
            /* fmbm_rtuc */
        p_BmiStats->cntQueueUtil =
            FM_PORT_GetCounter(h_FmPort, e_FM_PORT_COUNTERS_QUEUE_UTIL);
            /* fmbm_rrquc */
        p_BmiStats->cntDmaUtil =
            FM_PORT_GetCounter(h_FmPort, e_FM_PORT_COUNTERS_DMA_UTIL);
            /* fmbm_rduc */
        p_BmiStats->cntFifoUtil =
            FM_PORT_GetCounter(h_FmPort, e_FM_PORT_COUNTERS_FIFO_UTIL);
            /* fmbm_rfuc */
        p_BmiStats->cntRxPauseActivation =
            FM_PORT_GetCounter(h_FmPort, e_FM_PORT_COUNTERS_RX_PAUSE_ACTIVATION);
            /* fmbm_rpac */
        p_BmiStats->cntFrame =
            FM_PORT_GetCounter(h_FmPort, e_FM_PORT_COUNTERS_FRAME);
            /* fmbm_rfrc */
        p_BmiStats->cntDiscardFrame =
            FM_PORT_GetCounter(h_FmPort, e_FM_PORT_COUNTERS_DISCARD_FRAME);
            /* fmbm_rfdc */
        p_BmiStats->cntDeallocBuf =
            FM_PORT_GetCounter(h_FmPort, e_FM_PORT_COUNTERS_DEALLOC_BUF);
            /* fmbm_rbdc */
        p_BmiStats->cntRxBadFrame =
            FM_PORT_GetCounter(h_FmPort, e_FM_PORT_COUNTERS_RX_BAD_FRAME);
            /* fmbm_rfbc */
        p_BmiStats->cntRxLargeFrame =
            FM_PORT_GetCounter(h_FmPort, e_FM_PORT_COUNTERS_RX_LARGE_FRAME);
            /* fmbm_rlfc */
        p_BmiStats->cntRxFilterFrame =
            FM_PORT_GetCounter(h_FmPort, e_FM_PORT_COUNTERS_RX_FILTER_FRAME);
            /* fmbm_rffc */
        p_BmiStats->cntRxListDmaErr =
            FM_PORT_GetCounter(h_FmPort, e_FM_PORT_COUNTERS_RX_LIST_DMA_ERR);
            /* fmbm_rfldec */
        p_BmiStats->cntRxOutOfBuffersDiscard =
            FM_PORT_GetCounter(h_FmPort, e_FM_PORT_COUNTERS_RX_OUT_OF_BUFFERS_DISCARD);
            /* fmbm_rodc */
        p_BmiStats->cntWredDiscard = 0;
        p_BmiStats->cntLengthErr = 0;
        p_BmiStats->cntUnsupportedFormat = 0;
    }
    else if ((p_FmPort->portType == e_FM_PORT_TYPE_TX)
                || (p_FmPort->portType == e_FM_PORT_TYPE_TX_10G)){
        p_BmiStats->cntCycle =
            FM_PORT_GetCounter(h_FmPort, e_FM_PORT_COUNTERS_CYCLE);
            /* fmbm_tccn */
        p_BmiStats->cntTaskUtil =
            FM_PORT_GetCounter(h_FmPort, e_FM_PORT_COUNTERS_TASK_UTIL);
            /* fmbm_ttuc */
        p_BmiStats->cntQueueUtil =
            FM_PORT_GetCounter(h_FmPort, e_FM_PORT_COUNTERS_QUEUE_UTIL);
            /* fmbm_ttcquc */
        p_BmiStats->cntDmaUtil =
            FM_PORT_GetCounter(h_FmPort, e_FM_PORT_COUNTERS_DMA_UTIL);
            /* fmbm_tduc */
        p_BmiStats->cntFifoUtil =
            FM_PORT_GetCounter(h_FmPort, e_FM_PORT_COUNTERS_FIFO_UTIL);
            /* fmbm_tfuc */
        p_BmiStats->cntRxPauseActivation = 0;
        p_BmiStats->cntFrame =
            FM_PORT_GetCounter(h_FmPort, e_FM_PORT_COUNTERS_FRAME);
            /* fmbm_tfrc */
        p_BmiStats->cntDiscardFrame =
            FM_PORT_GetCounter(h_FmPort, e_FM_PORT_COUNTERS_DISCARD_FRAME);
            /* fmbm_tfdc */
        p_BmiStats->cntDeallocBuf =
            FM_PORT_GetCounter(h_FmPort, e_FM_PORT_COUNTERS_DEALLOC_BUF);
            /* fmbm_tbdc */
        p_BmiStats->cntRxBadFrame = 0;
        p_BmiStats->cntRxLargeFrame = 0;
        p_BmiStats->cntRxFilterFrame = 0;
        p_BmiStats->cntRxListDmaErr = 0;
        p_BmiStats->cntRxOutOfBuffersDiscard = 0;
        p_BmiStats->cntWredDiscard = 0;
        p_BmiStats->cntLengthErr =
            FM_PORT_GetCounter(h_FmPort, e_FM_PORT_COUNTERS_LENGTH_ERR);
            /* fmbm_tfledc */
        p_BmiStats->cntUnsupportedFormat =
            FM_PORT_GetCounter(h_FmPort, e_FM_PORT_COUNTERS_UNSUPPRTED_FORMAT);
            /* fmbm_tfufdc */
    }
    else if (p_FmPort->portType == e_FM_PORT_TYPE_OH_OFFLINE_PARSING) {
        p_BmiStats->cntCycle =
            FM_PORT_GetCounter(h_FmPort, e_FM_PORT_COUNTERS_CYCLE);
            /* fmbm_occn */
        p_BmiStats->cntTaskUtil =
            FM_PORT_GetCounter(h_FmPort, e_FM_PORT_COUNTERS_TASK_UTIL);
            /* fmbm_otuc */
        p_BmiStats->cntQueueUtil = 0;
        p_BmiStats->cntDmaUtil =
            FM_PORT_GetCounter(h_FmPort, e_FM_PORT_COUNTERS_DMA_UTIL);
            /* fmbm_oduc */
        p_BmiStats->cntFifoUtil =
            FM_PORT_GetCounter(h_FmPort, e_FM_PORT_COUNTERS_FIFO_UTIL);
            /* fmbm_ofuc*/
        p_BmiStats->cntRxPauseActivation = 0;
        p_BmiStats->cntFrame =
            FM_PORT_GetCounter(h_FmPort, e_FM_PORT_COUNTERS_FRAME);
            /* fmbm_ofrc */
        p_BmiStats->cntDiscardFrame =
            FM_PORT_GetCounter(h_FmPort, e_FM_PORT_COUNTERS_DISCARD_FRAME);
            /* fmbm_ofdc */
        p_BmiStats->cntDeallocBuf =
            FM_PORT_GetCounter(h_FmPort, e_FM_PORT_COUNTERS_DEALLOC_BUF);
            /* fmbm_obdc*/
        p_BmiStats->cntRxBadFrame = 0;
        p_BmiStats->cntRxLargeFrame = 0;
        p_BmiStats->cntRxFilterFrame =
            FM_PORT_GetCounter(h_FmPort, e_FM_PORT_COUNTERS_RX_FILTER_FRAME);
            /* fmbm_offc */
        p_BmiStats->cntRxListDmaErr =
            FM_PORT_GetCounter(h_FmPort, e_FM_PORT_COUNTERS_RX_LIST_DMA_ERR);
            /* fmbm_ofldec */
        p_BmiStats->cntRxOutOfBuffersDiscard =
            FM_PORT_GetCounter(h_FmPort, e_FM_PORT_COUNTERS_RX_OUT_OF_BUFFERS_DISCARD);
            /* fmbm_rodc */
        p_BmiStats->cntWredDiscard =
            FM_PORT_GetCounter(h_FmPort, e_FM_PORT_COUNTERS_WRED_DISCARD);
            /* fmbm_ofwdc */
        p_BmiStats->cntLengthErr =
            FM_PORT_GetCounter(h_FmPort, e_FM_PORT_COUNTERS_LENGTH_ERR);
            /* fmbm_ofledc */
        p_BmiStats->cntUnsupportedFormat =
            FM_PORT_GetCounter(h_FmPort, e_FM_PORT_COUNTERS_UNSUPPRTED_FORMAT);
            /* fmbm_ofufdc */
    }
    return E_OK;
}