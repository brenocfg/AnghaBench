#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_23__ {scalar_t__ size; scalar_t__ extBufOffset; scalar_t__ intContextOffset; } ;
struct fman_port_cfg {int tx_fifo_deq_pipeline_depth; int rx_pri_elevation; int rx_fifo_thr; scalar_t__ rx_cut_end_bytes; scalar_t__ checksum_bytes_ignore; int tx_fifo_min_level; int tx_fifo_low_comf_level; scalar_t__ discard_override; } ;
struct TYPE_14__ {int /*<<< orphan*/  numOfPools; scalar_t__ poolsGrpModeEnable; } ;
struct TYPE_15__ {scalar_t__ startMargins; } ;
struct TYPE_16__ {int manipExtraSpace; } ;
struct TYPE_24__ {int /*<<< orphan*/  numOfPoolsUsed; } ;
struct TYPE_21__ {int liodnOffset; scalar_t__ deqSubPortal; int dfltFqid; int errFqid; int errorsToDiscard; scalar_t__ cheksumLastBytesIgnore; scalar_t__ deqPrefetchOption; scalar_t__ setSizeOfFifo; scalar_t__ setNumOfOpenDmas; scalar_t__ setNumOfTasks; TYPE_8__ intContext; struct fman_port_cfg dfltCfg; TYPE_10__ bufPoolDepletion; TYPE_11__ bufMargins; TYPE_1__ bufferPrefixContent; scalar_t__ p_BackupBmPools; TYPE_9__ extBufPools; } ;
typedef  TYPE_6__ t_FmPortDriverParam ;
struct TYPE_20__ {int majorRev; } ;
struct TYPE_19__ {int extra; int num; } ;
struct TYPE_18__ {scalar_t__ num; scalar_t__ extra; } ;
struct TYPE_17__ {scalar_t__ num; scalar_t__ extra; } ;
struct TYPE_22__ {scalar_t__ portType; TYPE_6__* p_FmPortDriverParam; TYPE_5__ fmRevInfo; TYPE_4__ fifoBufs; TYPE_3__ openDmas; TYPE_2__ tasks; scalar_t__ imEn; } ;
typedef  TYPE_7__ t_FmPort ;
typedef  scalar_t__ t_Error ;

/* Variables and functions */
 int BMI_FIFO_UNITS ; 
 int BMI_STATUS_OP_MASK_UNUSED ; 
 int BMI_STATUS_RX_MASK_UNUSED ; 
 scalar_t__ DEFAULT_notSupported ; 
 scalar_t__ DPAA_LIODN_DONT_OVERRIDE ; 
 scalar_t__ ERROR_CODE (scalar_t__) ; 
 int /*<<< orphan*/  E_CONFLICT ; 
 int /*<<< orphan*/  E_INVALID_OPERATION ; 
 int /*<<< orphan*/  E_INVALID_SELECTION ; 
 int /*<<< orphan*/  E_INVALID_VALUE ; 
 int /*<<< orphan*/  E_NOT_SUPPORTED ; 
 scalar_t__ E_OK ; 
 int FM_LIODN_OFFSET_MASK ; 
 scalar_t__ FM_MAX_NUM_OF_SUB_PORTALS ; 
 scalar_t__ FRAME_END_DATA_SIZE ; 
 scalar_t__ FmPortImCheckInitParameters (TYPE_7__*) ; 
 scalar_t__ FmSpCheckBufMargins (TYPE_11__*) ; 
 scalar_t__ FmSpCheckBufPoolsParams (TYPE_9__*,scalar_t__,TYPE_10__*) ; 
 scalar_t__ FmSpCheckIntContextParams (TYPE_8__*) ; 
 int /*<<< orphan*/  MAJOR ; 
 scalar_t__ MAX_FIFO_PIPELINE_DEPTH ; 
 scalar_t__ MAX_NUM_OF_DMAS ; 
 scalar_t__ MAX_NUM_OF_EXTRA_DMAS ; 
 scalar_t__ MAX_NUM_OF_EXTRA_TASKS ; 
 scalar_t__ MAX_NUM_OF_TASKS ; 
 int MAX_PORT_FIFO_SIZE ; 
 scalar_t__ MIN_NUM_OF_OP_DMAS ; 
 scalar_t__ MIN_TX_INT_OFFSET ; 
 char* NO_MSG ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ e_FM_PORT_TYPE_OH_HOST_COMMAND ; 
 scalar_t__ e_FM_PORT_TYPE_OH_OFFLINE_PARSING ; 
 scalar_t__ e_FM_PORT_TYPE_RX ; 
 scalar_t__ e_FM_PORT_TYPE_RX_10G ; 
 scalar_t__ e_FM_PORT_TYPE_TX ; 
 scalar_t__ e_FM_PORT_TYPE_TX_10G ; 

__attribute__((used)) static t_Error CheckInitParameters(t_FmPort *p_FmPort)
{
    t_FmPortDriverParam *p_Params = p_FmPort->p_FmPortDriverParam;
    struct fman_port_cfg *p_DfltConfig = &p_Params->dfltCfg;
    t_Error ans = E_OK;
    uint32_t unusedMask;

    if (p_FmPort->imEn)
    {
        if (p_FmPort->portType == e_FM_PORT_TYPE_RX_10G)
            if (p_FmPort->p_FmPortDriverParam->dfltCfg.tx_fifo_deq_pipeline_depth
                    > 2)
                RETURN_ERROR(
                        MAJOR,
                        E_INVALID_VALUE,
                        ("fifoDeqPipelineDepth for IM 10G can't be larger than 2"));

        if ((ans = FmPortImCheckInitParameters(p_FmPort)) != E_OK)
            return ERROR_CODE(ans);
    }
    else
    {
        /****************************************/
        /*   Rx only                            */
        /****************************************/
        if ((p_FmPort->portType == e_FM_PORT_TYPE_RX)
                || (p_FmPort->portType == e_FM_PORT_TYPE_RX_10G))
        {
            /* external buffer pools */
            if (!p_Params->extBufPools.numOfPoolsUsed)
                RETURN_ERROR(
                        MAJOR,
                        E_INVALID_VALUE,
                        ("extBufPools.numOfPoolsUsed=0. At least one buffer pool must be defined"));

            if (FmSpCheckBufPoolsParams(&p_Params->extBufPools,
                                        p_Params->p_BackupBmPools,
                                        &p_Params->bufPoolDepletion) != E_OK)
                RETURN_ERROR(MAJOR, E_INVALID_VALUE, NO_MSG);

            /* Check that part of IC that needs copying is small enough to enter start margin */
            if (p_Params->intContext.size
                    && (p_Params->intContext.size
                            + p_Params->intContext.extBufOffset
                            > p_Params->bufMargins.startMargins))
                RETURN_ERROR(MAJOR, E_INVALID_VALUE,
                             ("intContext.size is larger than start margins"));

            if ((p_Params->liodnOffset != (uint16_t)DPAA_LIODN_DONT_OVERRIDE)
                    && (p_Params->liodnOffset & ~FM_LIODN_OFFSET_MASK))
                RETURN_ERROR(
                        MAJOR,
                        E_INVALID_VALUE,
                        ("liodnOffset is larger than %d", FM_LIODN_OFFSET_MASK+1));

#ifdef FM_NO_BACKUP_POOLS
            if ((p_FmPort->fmRevInfo.majorRev != 4) && (p_FmPort->fmRevInfo.majorRev < 6))
            if (p_FmPort->p_FmPortDriverParam->p_BackupBmPools)
            RETURN_ERROR(MAJOR, E_NOT_SUPPORTED, ("BackupBmPools"));
#endif /* FM_NO_BACKUP_POOLS */
        }

        /****************************************/
        /*   Non Rx ports                       */
        /****************************************/
        else
        {
            if (p_Params->deqSubPortal >= FM_MAX_NUM_OF_SUB_PORTALS)
                RETURN_ERROR(
                        MAJOR,
                        E_INVALID_VALUE,
                        (" deqSubPortal has to be in the range of 0 - %d", FM_MAX_NUM_OF_SUB_PORTALS));

            /* to protect HW internal-context from overwrite */
            if ((p_Params->intContext.size)
                    && (p_Params->intContext.intContextOffset
                            < MIN_TX_INT_OFFSET))
                RETURN_ERROR(
                        MAJOR,
                        E_INVALID_VALUE,
                        ("non-Rx intContext.intContextOffset can't be smaller than %d", MIN_TX_INT_OFFSET));

            if ((p_FmPort->portType == e_FM_PORT_TYPE_TX)
                    || (p_FmPort->portType == e_FM_PORT_TYPE_TX_10G)
                    /* in O/H DEFAULT_notSupported indicates that it is not supported and should not be checked */
                    || (p_FmPort->p_FmPortDriverParam->dfltCfg.tx_fifo_deq_pipeline_depth
                            != DEFAULT_notSupported))
            {
                /* Check that not larger than 8 */
                if ((!p_FmPort->p_FmPortDriverParam->dfltCfg.tx_fifo_deq_pipeline_depth)
                        || (p_FmPort->p_FmPortDriverParam->dfltCfg.tx_fifo_deq_pipeline_depth
                                > MAX_FIFO_PIPELINE_DEPTH))
                    RETURN_ERROR(
                            MAJOR,
                            E_INVALID_VALUE,
                            ("fifoDeqPipelineDepth can't be larger than %d", MAX_FIFO_PIPELINE_DEPTH));
            }
        }

        /****************************************/
        /*   Rx Or Offline Parsing              */
        /****************************************/
        if ((p_FmPort->portType == e_FM_PORT_TYPE_RX)
                || (p_FmPort->portType == e_FM_PORT_TYPE_RX_10G)
                || (p_FmPort->portType == e_FM_PORT_TYPE_OH_OFFLINE_PARSING))
        {
            if (!p_Params->dfltFqid)
                RETURN_ERROR(MAJOR, E_INVALID_VALUE,
                             ("dfltFqid must be between 1 and 2^24-1"));
#if defined(FM_CAPWAP_SUPPORT) && defined(FM_LOCKUP_ALIGNMENT_ERRATA_FMAN_SW004)
            if (p_FmPort->p_FmPortDriverParam->bufferPrefixContent.manipExtraSpace % 16)
            RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("bufferPrefixContent.manipExtraSpace has to be devidable by 16"));
#endif /* defined(FM_CAPWAP_SUPPORT) && ... */
        }

        /****************************************/
        /*   All ports                          */
        /****************************************/
        /* common BMI registers values */
        /* Check that Queue Id is not larger than 2^24, and is not 0 */
        if ((p_Params->errFqid & ~0x00FFFFFF) || !p_Params->errFqid)
            RETURN_ERROR(MAJOR, E_INVALID_VALUE,
                         ("errFqid must be between 1 and 2^24-1"));
        if (p_Params->dfltFqid & ~0x00FFFFFF)
            RETURN_ERROR(MAJOR, E_INVALID_VALUE,
                         ("dfltFqid must be between 1 and 2^24-1"));
    }

    /****************************************/
    /*   Rx only                            */
    /****************************************/
    if ((p_FmPort->portType == e_FM_PORT_TYPE_RX)
            || (p_FmPort->portType == e_FM_PORT_TYPE_RX_10G))
    {
        if (p_DfltConfig->rx_pri_elevation % BMI_FIFO_UNITS)
            RETURN_ERROR(
                    MAJOR,
                    E_INVALID_VALUE,
                    ("rxFifoPriElevationLevel has to be divisible by %d", BMI_FIFO_UNITS));
        if ((p_DfltConfig->rx_pri_elevation < BMI_FIFO_UNITS)
                || (p_DfltConfig->rx_pri_elevation > MAX_PORT_FIFO_SIZE))
            RETURN_ERROR(
                    MAJOR,
                    E_INVALID_VALUE,
                    ("rxFifoPriElevationLevel has to be in the range of 256 - %d", MAX_PORT_FIFO_SIZE));
        if (p_DfltConfig->rx_fifo_thr % BMI_FIFO_UNITS)
            RETURN_ERROR(
                    MAJOR,
                    E_INVALID_VALUE,
                    ("rxFifoThreshold has to be divisible by %d", BMI_FIFO_UNITS));
        if ((p_DfltConfig->rx_fifo_thr < BMI_FIFO_UNITS)
                || (p_DfltConfig->rx_fifo_thr > MAX_PORT_FIFO_SIZE))
            RETURN_ERROR(
                    MAJOR,
                    E_INVALID_VALUE,
                    ("rxFifoThreshold has to be in the range of 256 - %d", MAX_PORT_FIFO_SIZE));

        /* Check that not larger than 16 */
        if (p_DfltConfig->rx_cut_end_bytes > FRAME_END_DATA_SIZE)
            RETURN_ERROR(
                    MAJOR,
                    E_INVALID_VALUE,
                    ("cutBytesFromEnd can't be larger than %d", FRAME_END_DATA_SIZE));

        if (FmSpCheckBufMargins(&p_Params->bufMargins) != E_OK)
            RETURN_ERROR(MAJOR, E_INVALID_VALUE, NO_MSG);

        /* extra FIFO size (allowed only to Rx ports) */
        if (p_Params->setSizeOfFifo
                && (p_FmPort->fifoBufs.extra % BMI_FIFO_UNITS))
            RETURN_ERROR(
                    MAJOR,
                    E_INVALID_VALUE,
                    ("fifoBufs.extra has to be divisible by %d", BMI_FIFO_UNITS));

        if (p_Params->bufPoolDepletion.poolsGrpModeEnable
                && !p_Params->bufPoolDepletion.numOfPools)
            RETURN_ERROR(
                    MAJOR,
                    E_INVALID_VALUE,
                    ("bufPoolDepletion.numOfPools can not be 0 when poolsGrpModeEnable=TRUE"));
#ifdef FM_CSI_CFED_LIMIT
        if (p_FmPort->fmRevInfo.majorRev == 4)
        {
            /* Check that not larger than 16 */
            if (p_DfltConfig->rx_cut_end_bytes + p_DfltConfig->checksum_bytes_ignore > FRAME_END_DATA_SIZE)
            RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("cheksumLastBytesIgnore + cutBytesFromEnd can't be larger than %d", FRAME_END_DATA_SIZE));
        }
#endif /* FM_CSI_CFED_LIMIT */
    }

    /****************************************/
    /*   Non Rx ports                       */
    /****************************************/
    /* extra FIFO size (allowed only to Rx ports) */
    else
        if (p_FmPort->fifoBufs.extra)
            RETURN_ERROR(MAJOR, E_INVALID_VALUE,
                         (" No fifoBufs.extra for non Rx ports"));

    /****************************************/
    /*   Tx only                            */
    /****************************************/
    if ((p_FmPort->portType == e_FM_PORT_TYPE_TX)
            || (p_FmPort->portType == e_FM_PORT_TYPE_TX_10G))
    {
        if (p_DfltConfig->tx_fifo_min_level % BMI_FIFO_UNITS)
            RETURN_ERROR(
                    MAJOR,
                    E_INVALID_VALUE,
                    ("txFifoMinFillLevel has to be divisible by %d", BMI_FIFO_UNITS));
        if (p_DfltConfig->tx_fifo_min_level > (MAX_PORT_FIFO_SIZE - 256))
            RETURN_ERROR(
                    MAJOR,
                    E_INVALID_VALUE,
                    ("txFifoMinFillLevel has to be in the range of 0 - %d", (MAX_PORT_FIFO_SIZE - 256)));
        if (p_DfltConfig->tx_fifo_low_comf_level % BMI_FIFO_UNITS)
            RETURN_ERROR(
                    MAJOR,
                    E_INVALID_VALUE,
                    ("txFifoLowComfLevel has to be divisible by %d", BMI_FIFO_UNITS));
        if ((p_DfltConfig->tx_fifo_low_comf_level < BMI_FIFO_UNITS)
                || (p_DfltConfig->tx_fifo_low_comf_level > MAX_PORT_FIFO_SIZE))
            RETURN_ERROR(
                    MAJOR,
                    E_INVALID_VALUE,
                    ("txFifoLowComfLevel has to be in the range of 256 - %d", MAX_PORT_FIFO_SIZE));

        if (p_FmPort->portType == e_FM_PORT_TYPE_TX)
            if (p_FmPort->p_FmPortDriverParam->dfltCfg.tx_fifo_deq_pipeline_depth
                    > 2)
                RETURN_ERROR(
                        MAJOR, E_INVALID_VALUE,
                        ("fifoDeqPipelineDepth for 1G can't be larger than 2"));
    }

    /****************************************/
    /*   Non Tx Ports                       */
    /****************************************/
    /* If discard override was selected , no frames may be discarded. */
    else
        if (p_DfltConfig->discard_override && p_Params->errorsToDiscard)
            RETURN_ERROR(
                    MAJOR,
                    E_CONFLICT,
                    ("errorsToDiscard is not empty, but frmDiscardOverride selected (all discarded frames to be enqueued to error queue)."));

    /****************************************/
    /*   Rx and Offline parsing             */
    /****************************************/
    if ((p_FmPort->portType == e_FM_PORT_TYPE_RX)
            || (p_FmPort->portType == e_FM_PORT_TYPE_RX_10G)
            || (p_FmPort->portType == e_FM_PORT_TYPE_OH_OFFLINE_PARSING))
    {
        if (p_FmPort->portType == e_FM_PORT_TYPE_OH_OFFLINE_PARSING)
            unusedMask = BMI_STATUS_OP_MASK_UNUSED;
        else
            unusedMask = BMI_STATUS_RX_MASK_UNUSED;

        /* Check that no common bits with BMI_STATUS_MASK_UNUSED */
        if (p_Params->errorsToDiscard & unusedMask)
            RETURN_ERROR(MAJOR, E_INVALID_SELECTION,
                         ("errorsToDiscard contains undefined bits"));
    }

    /****************************************/
    /*   Offline Ports                      */
    /****************************************/
#ifdef FM_OP_OPEN_DMA_MIN_LIMIT
    if ((p_FmPort->fmRevInfo.majorRev >= 6)
            && (p_FmPort->portType == e_FM_PORT_TYPE_OH_OFFLINE_PARSING)
            && p_Params->setNumOfOpenDmas
            && (p_FmPort->openDmas.num < MIN_NUM_OF_OP_DMAS))
        RETURN_ERROR(
                MAJOR,
                E_INVALID_VALUE,
                ("For Offline port, openDmas.num can't be smaller than %d", MIN_NUM_OF_OP_DMAS));
#endif /* FM_OP_OPEN_DMA_MIN_LIMIT */

    /****************************************/
    /*   Offline & HC Ports                 */
    /****************************************/
    if ((p_FmPort->portType == e_FM_PORT_TYPE_OH_OFFLINE_PARSING)
            || (p_FmPort->portType == e_FM_PORT_TYPE_OH_HOST_COMMAND))
    {
#ifndef FM_FRAME_END_PARAMS_FOR_OP
        if ((p_FmPort->fmRevInfo.majorRev < 6) &&
                (p_FmPort->p_FmPortDriverParam->cheksumLastBytesIgnore != DEFAULT_notSupported))
        /* this is an indication that user called config for this mode which is not supported in this integration */
        RETURN_ERROR(MAJOR, E_NOT_SUPPORTED, ("cheksumLastBytesIgnore is available for Rx & Tx ports only"));
#endif /* !FM_FRAME_END_PARAMS_FOR_OP */

#ifndef FM_DEQ_PIPELINE_PARAMS_FOR_OP
        if ((!((p_FmPort->fmRevInfo.majorRev == 4) ||
                                (p_FmPort->fmRevInfo.majorRev >= 6))) &&
                (p_FmPort->p_FmPortDriverParam->dfltCfg.tx_fifo_deq_pipeline_depth != DEFAULT_notSupported))
        /* this is an indication that user called config for this mode which is not supported in this integration */
        RETURN_ERROR(MAJOR, E_INVALID_OPERATION, ("fifoDeqPipelineDepth is available for Tx ports only"));
#endif /* !FM_DEQ_PIPELINE_PARAMS_FOR_OP */
    }

    /****************************************/
    /*   All ports                          */
    /****************************************/
    /* Check that not larger than 16 */
    if ((p_Params->cheksumLastBytesIgnore > FRAME_END_DATA_SIZE)
            && ((p_Params->cheksumLastBytesIgnore != DEFAULT_notSupported)))
        RETURN_ERROR(
                MAJOR,
                E_INVALID_VALUE,
                ("cheksumLastBytesIgnore can't be larger than %d", FRAME_END_DATA_SIZE));

    if (FmSpCheckIntContextParams(&p_Params->intContext) != E_OK)
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, NO_MSG);

    /* common BMI registers values */
    if (p_Params->setNumOfTasks
            && ((!p_FmPort->tasks.num)
                    || (p_FmPort->tasks.num > MAX_NUM_OF_TASKS)))
        RETURN_ERROR(MAJOR, E_INVALID_VALUE,
                     ("tasks.num can't be larger than %d", MAX_NUM_OF_TASKS));
    if (p_Params->setNumOfTasks
            && (p_FmPort->tasks.extra > MAX_NUM_OF_EXTRA_TASKS))
        RETURN_ERROR(
                MAJOR,
                E_INVALID_VALUE,
                ("tasks.extra can't be larger than %d", MAX_NUM_OF_EXTRA_TASKS));
    if (p_Params->setNumOfOpenDmas
            && ((!p_FmPort->openDmas.num)
                    || (p_FmPort->openDmas.num > MAX_NUM_OF_DMAS)))
        RETURN_ERROR(MAJOR, E_INVALID_VALUE,
                     ("openDmas.num can't be larger than %d", MAX_NUM_OF_DMAS));
    if (p_Params->setNumOfOpenDmas
            && (p_FmPort->openDmas.extra > MAX_NUM_OF_EXTRA_DMAS))
        RETURN_ERROR(
                MAJOR,
                E_INVALID_VALUE,
                ("openDmas.extra can't be larger than %d", MAX_NUM_OF_EXTRA_DMAS));
    if (p_Params->setSizeOfFifo
            && (!p_FmPort->fifoBufs.num
                    || (p_FmPort->fifoBufs.num > MAX_PORT_FIFO_SIZE)))
        RETURN_ERROR(
                MAJOR,
                E_INVALID_VALUE,
                ("fifoBufs.num has to be in the range of 256 - %d", MAX_PORT_FIFO_SIZE));
    if (p_Params->setSizeOfFifo && (p_FmPort->fifoBufs.num % BMI_FIFO_UNITS))
        RETURN_ERROR(
                MAJOR, E_INVALID_VALUE,
                ("fifoBufs.num has to be divisible by %d", BMI_FIFO_UNITS));

#ifdef FM_QMI_NO_DEQ_OPTIONS_SUPPORT
    if (p_FmPort->fmRevInfo.majorRev == 4)
    if (p_FmPort->p_FmPortDriverParam->deqPrefetchOption != DEFAULT_notSupported)
    /* this is an indication that user called config for this mode which is not supported in this integration */
    RETURN_ERROR(MAJOR, E_INVALID_OPERATION, ("deqPrefetchOption"));
#endif /* FM_QMI_NO_DEQ_OPTIONS_SUPPORT */

    return E_OK;
}