#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_16__ {int taskCompVal; int queueCompVal; int dmaCompVal; int fifoCompVal; } ;
typedef  TYPE_4__ t_FmPortPerformanceCnt ;
struct TYPE_15__ {int num; } ;
struct TYPE_14__ {scalar_t__ num; } ;
struct TYPE_13__ {scalar_t__ num; } ;
struct TYPE_17__ {scalar_t__ portType; TYPE_3__ fifoBufs; TYPE_2__ openDmas; TYPE_1__ tasks; int /*<<< orphan*/  portId; } ;
typedef  TYPE_5__ t_FmPort ;
typedef  int /*<<< orphan*/  t_Error ;
typedef  int /*<<< orphan*/  savedParams ;

/* Variables and functions */
 int BMI_FIFO_UNITS ; 
 int /*<<< orphan*/  ClearPerfCnts (TYPE_5__*) ; 
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_INVALID_STATE ; 
 int /*<<< orphan*/  E_OK ; 
 int FALSE ; 
 scalar_t__ FM_PORT_GetCounter (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FM_PORT_SetPerformanceCounters (TYPE_5__*,int) ; 
 int /*<<< orphan*/  FM_PORT_SetPerformanceCountersParams (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  NO_MSG ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int /*<<< orphan*/  XX_Print (char*,int,...) ; 
 int /*<<< orphan*/  XX_UDelay (int) ; 
 int /*<<< orphan*/  e_FM_PORT_COUNTERS_DMA_UTIL ; 
 int /*<<< orphan*/  e_FM_PORT_COUNTERS_FIFO_UTIL ; 
 int /*<<< orphan*/  e_FM_PORT_COUNTERS_TASK_UTIL ; 
 scalar_t__ e_FM_PORT_TYPE_OH_HOST_COMMAND ; 
 scalar_t__ e_FM_PORT_TYPE_OH_OFFLINE_PARSING ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

t_Error FM_PORT_AnalyzePerformanceParams(t_Handle h_FmPort)
{
    t_FmPort *p_FmPort = (t_FmPort*)h_FmPort;
    t_FmPortPerformanceCnt currParams, savedParams;
    t_Error err;
    bool underTest, failed = FALSE;

    SANITY_CHECK_RETURN_ERROR(p_FmPort, E_INVALID_HANDLE);

    XX_Print("Analyzing Performance parameters for port (type %d, id%d)\n",
             p_FmPort->portType, p_FmPort->portId);

    currParams.taskCompVal = (uint8_t)p_FmPort->tasks.num;
    if ((p_FmPort->portType == e_FM_PORT_TYPE_OH_OFFLINE_PARSING)
            || (p_FmPort->portType == e_FM_PORT_TYPE_OH_HOST_COMMAND))
        currParams.queueCompVal = 0;
    else
        currParams.queueCompVal = 1;
    currParams.dmaCompVal = (uint8_t)p_FmPort->openDmas.num;
    currParams.fifoCompVal = p_FmPort->fifoBufs.num;

    FM_PORT_SetPerformanceCounters(p_FmPort, FALSE);
    ClearPerfCnts(p_FmPort);
    if ((err = FM_PORT_SetPerformanceCountersParams(p_FmPort, &currParams))
            != E_OK)
        RETURN_ERROR(MAJOR, err, NO_MSG);
    FM_PORT_SetPerformanceCounters(p_FmPort, TRUE);
    XX_UDelay(1000000);
    FM_PORT_SetPerformanceCounters(p_FmPort, FALSE);
    if (FM_PORT_GetCounter(p_FmPort, e_FM_PORT_COUNTERS_TASK_UTIL))
    {
        XX_Print(
                "Max num of defined port tasks (%d) utilized - Please enlarge\n",
                p_FmPort->tasks.num);
        failed = TRUE;
    }
    if (FM_PORT_GetCounter(p_FmPort, e_FM_PORT_COUNTERS_DMA_UTIL))
    {
        XX_Print(
                "Max num of defined port openDmas (%d) utilized - Please enlarge\n",
                p_FmPort->openDmas.num);
        failed = TRUE;
    }
    if (FM_PORT_GetCounter(p_FmPort, e_FM_PORT_COUNTERS_FIFO_UTIL))
    {
        XX_Print(
                "Max size of defined port fifo (%d) utilized - Please enlarge\n",
                p_FmPort->fifoBufs.num);
        failed = TRUE;
    }
    if (failed)
        RETURN_ERROR(MAJOR, E_INVALID_STATE, NO_MSG);

    memset(&savedParams, 0, sizeof(savedParams));
    while (TRUE)
    {
        underTest = FALSE;
        if ((currParams.taskCompVal != 1) && !savedParams.taskCompVal)
        {
            currParams.taskCompVal--;
            underTest = TRUE;
        }
        if ((currParams.dmaCompVal != 1) && !savedParams.dmaCompVal)
        {
            currParams.dmaCompVal--;
            underTest = TRUE;
        }
        if ((currParams.fifoCompVal != BMI_FIFO_UNITS)
                && !savedParams.fifoCompVal)
        {
            currParams.fifoCompVal -= BMI_FIFO_UNITS;
            underTest = TRUE;
        }
        if (!underTest)
            break;

        ClearPerfCnts(p_FmPort);
        if ((err = FM_PORT_SetPerformanceCountersParams(p_FmPort, &currParams))
                != E_OK)
            RETURN_ERROR(MAJOR, err, NO_MSG);
        FM_PORT_SetPerformanceCounters(p_FmPort, TRUE);
        XX_UDelay(1000000);
        FM_PORT_SetPerformanceCounters(p_FmPort, FALSE);

        if (!savedParams.taskCompVal
                && FM_PORT_GetCounter(p_FmPort, e_FM_PORT_COUNTERS_TASK_UTIL))
            savedParams.taskCompVal = (uint8_t)(currParams.taskCompVal + 2);
        if (!savedParams.dmaCompVal
                && FM_PORT_GetCounter(p_FmPort, e_FM_PORT_COUNTERS_DMA_UTIL))
            savedParams.dmaCompVal = (uint8_t)(currParams.dmaCompVal + 2);
        if (!savedParams.fifoCompVal
                && FM_PORT_GetCounter(p_FmPort, e_FM_PORT_COUNTERS_FIFO_UTIL))
            savedParams.fifoCompVal = currParams.fifoCompVal
                    + (2 * BMI_FIFO_UNITS);
    }

    XX_Print("best vals: tasks %d, dmas %d, fifos %d\n",
             savedParams.taskCompVal, savedParams.dmaCompVal,
             savedParams.fifoCompVal);
    return E_OK;
}