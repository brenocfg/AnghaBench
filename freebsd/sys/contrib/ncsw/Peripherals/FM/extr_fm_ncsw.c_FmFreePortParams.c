#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int uint16_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_12__ {size_t hardwarePortId; int deqPipelineDepth; scalar_t__ enumPortType; } ;
typedef  TYPE_3__ t_FmIpcPortFreeParams ;
struct TYPE_13__ {int /*<<< orphan*/  msgBody; int /*<<< orphan*/  msgId; } ;
typedef  TYPE_4__ t_FmIpcMsg ;
struct TYPE_14__ {size_t hardwarePortId; scalar_t__ portType; int deqPipelineDepth; } ;
typedef  TYPE_5__ t_FmInterModulePortFreeParams ;
struct TYPE_15__ {scalar_t__ guestId; int hcPortInitialized; int /*<<< orphan*/  h_Spinlock; TYPE_2__* p_FmStateStruct; int /*<<< orphan*/ * h_IpcSessions; struct fman_bmi_regs* p_FmBmiRegs; struct fman_qmi_regs* p_FmQmiRegs; } ;
typedef  TYPE_6__ t_Fm ;
typedef  scalar_t__ t_Error ;
struct fman_qmi_regs {int dummy; } ;
struct fman_bmi_regs {int dummy; } ;
typedef  int /*<<< orphan*/  portParams ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_10__ {int majorRev; } ;
struct TYPE_11__ {size_t accumulatedNumOfTasks; size_t accumulatedNumOfOpenDmas; size_t extraOpenDmasPoolSize; int accumulatedFifoSize; int accumulatedNumOfDeqTnums; void* lowEndRestriction; scalar_t__* portMaxFrameLengths1G; scalar_t__* portMaxFrameLengths10G; TYPE_1__ revInfo; int /*<<< orphan*/ * portsTypes; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int BMI_FIFO_UNITS ; 
 scalar_t__ E_OK ; 
 void* FALSE ; 
 int /*<<< orphan*/  FM_FREE_PORT ; 
 size_t FM_MAX_NUM_OF_10G_MACS ; 
 size_t FM_MAX_NUM_OF_1G_MACS ; 
 int /*<<< orphan*/  HW_PORT_ID_TO_SW_PORT_ID (size_t,size_t) ; 
 int IN_RANGE (int,size_t,int) ; 
 int /*<<< orphan*/  MINOR ; 
 scalar_t__ NCSW_MASTER_ID ; 
 int /*<<< orphan*/  NO_MSG ; 
 int QMI_MAX_NUM_OF_TNUMS ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ XX_IpcSendMessage (int /*<<< orphan*/ ,size_t*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ XX_LockIntrSpinlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XX_UnlockIntrSpinlock (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  e_FM_PORT_TYPE_DUMMY ; 
 scalar_t__ e_FM_PORT_TYPE_OH_HOST_COMMAND ; 
 scalar_t__ e_FM_PORT_TYPE_RX ; 
 scalar_t__ e_FM_PORT_TYPE_RX_10G ; 
 scalar_t__ e_FM_PORT_TYPE_TX ; 
 scalar_t__ e_FM_PORT_TYPE_TX_10G ; 
 size_t fman_get_num_of_dmas (struct fman_bmi_regs*,size_t) ; 
 size_t fman_get_num_of_tasks (struct fman_bmi_regs*,size_t) ; 
 int fman_get_size_of_fifo (struct fman_bmi_regs*,size_t) ; 
 int /*<<< orphan*/  fman_set_num_of_open_dmas (struct fman_bmi_regs*,size_t,int,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  fman_set_qmi_deq_th (struct fman_qmi_regs*,size_t) ; 
 int /*<<< orphan*/  fman_set_qmi_enq_th (struct fman_qmi_regs*,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

void FmFreePortParams(t_Handle h_Fm,t_FmInterModulePortFreeParams *p_PortParams)
{
    t_Fm                    *p_Fm = (t_Fm*)h_Fm;
    uint32_t                intFlags;
    uint8_t                 hardwarePortId = p_PortParams->hardwarePortId;
    uint8_t                 numOfTasks, numOfDmas, macId;
    uint16_t                sizeOfFifo;
    t_Error                 err;
    t_FmIpcPortFreeParams   portParams;
    t_FmIpcMsg              msg;
    struct fman_qmi_regs *qmi_rg = p_Fm->p_FmQmiRegs;
    struct fman_bmi_regs *bmi_rg = p_Fm->p_FmBmiRegs;

    if (p_Fm->guestId != NCSW_MASTER_ID)
    {
        portParams.hardwarePortId = p_PortParams->hardwarePortId;
        portParams.enumPortType = (uint32_t)p_PortParams->portType;
        portParams.deqPipelineDepth = p_PortParams->deqPipelineDepth;
        memset(&msg, 0, sizeof(msg));
        msg.msgId = FM_FREE_PORT;
        memcpy(msg.msgBody, &portParams, sizeof(portParams));
        err = XX_IpcSendMessage(p_Fm->h_IpcSessions[0],
                                (uint8_t*)&msg,
                                sizeof(msg.msgId)+sizeof(portParams),
                                NULL,
                                NULL,
                                NULL,
                                NULL);
        if (err != E_OK)
            REPORT_ERROR(MINOR, err, NO_MSG);
        return;
    }

    ASSERT_COND(IN_RANGE(1, hardwarePortId, 63));

    intFlags = XX_LockIntrSpinlock(p_Fm->h_Spinlock);

    if (p_PortParams->portType == e_FM_PORT_TYPE_OH_HOST_COMMAND)
    {
        ASSERT_COND(p_Fm->hcPortInitialized);
        p_Fm->hcPortInitialized = FALSE;
    }

    p_Fm->p_FmStateStruct->portsTypes[hardwarePortId] = e_FM_PORT_TYPE_DUMMY;

    /* free numOfTasks */
    numOfTasks = fman_get_num_of_tasks(bmi_rg, hardwarePortId);
    ASSERT_COND(p_Fm->p_FmStateStruct->accumulatedNumOfTasks >= numOfTasks);
    p_Fm->p_FmStateStruct->accumulatedNumOfTasks -= numOfTasks;

    /* free numOfOpenDmas */
    numOfDmas = fman_get_num_of_dmas(bmi_rg, hardwarePortId);
    ASSERT_COND(p_Fm->p_FmStateStruct->accumulatedNumOfOpenDmas >= numOfDmas);
    p_Fm->p_FmStateStruct->accumulatedNumOfOpenDmas -= numOfDmas;

#ifdef FM_HAS_TOTAL_DMAS
    if (p_Fm->p_FmStateStruct->revInfo.majorRev < 6)
    {
        /* update total num of DMA's with committed number of open DMAS, and max uncommitted pool. */
        fman_set_num_of_open_dmas(bmi_rg,
                                  hardwarePortId,
                                  1,
                                  0,
                         (uint8_t)(p_Fm->p_FmStateStruct->accumulatedNumOfOpenDmas + p_Fm->p_FmStateStruct->extraOpenDmasPoolSize));
    }
#endif /* FM_HAS_TOTAL_DMAS */

    /* free sizeOfFifo */
    sizeOfFifo = fman_get_size_of_fifo(bmi_rg, hardwarePortId);
    ASSERT_COND(p_Fm->p_FmStateStruct->accumulatedFifoSize >= (sizeOfFifo * BMI_FIFO_UNITS));
    p_Fm->p_FmStateStruct->accumulatedFifoSize -= (sizeOfFifo * BMI_FIFO_UNITS);

#ifdef FM_QMI_NO_DEQ_OPTIONS_SUPPORT
    if (p_Fm->p_FmStateStruct->revInfo.majorRev != 4)
#endif /* FM_QMI_NO_DEQ_OPTIONS_SUPPORT */
    if ((p_PortParams->portType != e_FM_PORT_TYPE_RX) &&
        (p_PortParams->portType != e_FM_PORT_TYPE_RX_10G))
    /* for transmit & O/H ports */
    {
        uint8_t     enqTh;
        uint8_t     deqTh;

        /* update qmi ENQ/DEQ threshold */
        p_Fm->p_FmStateStruct->accumulatedNumOfDeqTnums -= p_PortParams->deqPipelineDepth;

        /* p_Fm->p_FmStateStruct->accumulatedNumOfDeqTnums is now smaller,
           so we can enlarge enqTh */
        enqTh = (uint8_t)(QMI_MAX_NUM_OF_TNUMS - p_Fm->p_FmStateStruct->accumulatedNumOfDeqTnums - 1);

         /* p_Fm->p_FmStateStruct->accumulatedNumOfDeqTnums is now smaller,
            so we can reduce deqTh */
        deqTh = (uint8_t)(p_Fm->p_FmStateStruct->accumulatedNumOfDeqTnums + 1);

        fman_set_qmi_enq_th(qmi_rg, enqTh);
        fman_set_qmi_deq_th(qmi_rg, deqTh);
    }

    HW_PORT_ID_TO_SW_PORT_ID(macId, hardwarePortId);

#if defined(FM_MAX_NUM_OF_10G_MACS) && (FM_MAX_NUM_OF_10G_MACS)
    if ((p_PortParams->portType == e_FM_PORT_TYPE_TX_10G) ||
        (p_PortParams->portType == e_FM_PORT_TYPE_RX_10G))
    {
        ASSERT_COND(macId < FM_MAX_NUM_OF_10G_MACS);
        p_Fm->p_FmStateStruct->portMaxFrameLengths10G[macId] = 0;
    }
    else
#endif /* defined(FM_MAX_NUM_OF_10G_MACS) && ... */
    if ((p_PortParams->portType == e_FM_PORT_TYPE_TX) ||
        (p_PortParams->portType == e_FM_PORT_TYPE_RX))
    {
        ASSERT_COND(macId < FM_MAX_NUM_OF_1G_MACS);
        p_Fm->p_FmStateStruct->portMaxFrameLengths1G[macId] = 0;
    }

#ifdef FM_LOW_END_RESTRICTION
    if ((hardwarePortId==0x1) || (hardwarePortId==0x29))
        p_Fm->p_FmStateStruct->lowEndRestriction = FALSE;
#endif /* FM_LOW_END_RESTRICTION */
    XX_UnlockIntrSpinlock(p_Fm->h_Spinlock, intFlags);
}