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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  t_HcFrame ;
typedef  int /*<<< orphan*/ * t_Handle ;
struct TYPE_13__ {int /*<<< orphan*/  qmChannel; int /*<<< orphan*/  dfltFqid; int /*<<< orphan*/  errFqid; } ;
struct TYPE_14__ {TYPE_1__ nonRxParams; } ;
struct TYPE_16__ {int /*<<< orphan*/  h_HcPortDev; TYPE_2__ specificParams; int /*<<< orphan*/  h_Fm; int /*<<< orphan*/  liodnBase; int /*<<< orphan*/  portId; int /*<<< orphan*/  portType; int /*<<< orphan*/  baseAddr; int /*<<< orphan*/  dataMemId; int /*<<< orphan*/  h_QmArg; int /*<<< orphan*/  f_QmEnqueue; int /*<<< orphan*/  h_FmPcd; } ;
typedef  TYPE_4__ t_FmPortParams ;
struct TYPE_15__ {int /*<<< orphan*/  qmChannel; int /*<<< orphan*/  confFqid; int /*<<< orphan*/  errFqid; int /*<<< orphan*/  liodnBase; int /*<<< orphan*/  portId; int /*<<< orphan*/  portBaseAddr; int /*<<< orphan*/  h_QmArg; int /*<<< orphan*/  f_QmEnqueue; } ;
struct TYPE_17__ {TYPE_3__ params; int /*<<< orphan*/  h_Fm; int /*<<< orphan*/  h_FmPcd; } ;
typedef  TYPE_5__ t_FmHcParams ;
typedef  TYPE_4__ t_FmHc ;
typedef  scalar_t__ t_Error ;
typedef  int /*<<< orphan*/  fmPortParam ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_dataMemId ; 
 scalar_t__ E_INVALID_HANDLE ; 
 scalar_t__ E_NO_MEMORY ; 
 scalar_t__ E_OK ; 
 int /*<<< orphan*/  FM_PORT_Config (TYPE_4__*) ; 
 scalar_t__ FM_PORT_ConfigMaxFrameLength (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FM_PORT_Enable (int /*<<< orphan*/ ) ; 
 scalar_t__ FM_PORT_Init (int /*<<< orphan*/ ) ; 
 scalar_t__ FillBufPool (TYPE_4__*) ; 
 int /*<<< orphan*/  FmHcFree (TYPE_4__*) ; 
 int /*<<< orphan*/  FmIsMaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  MINOR ; 
 char* NO_MSG ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  XX_Free (TYPE_4__*) ; 
 scalar_t__ XX_Malloc (int) ; 
 int /*<<< orphan*/  e_FM_PORT_TYPE_OH_HOST_COMMAND ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

t_Handle FmHcConfigAndInit(t_FmHcParams *p_FmHcParams)
{
    t_FmHc          *p_FmHc;
    t_FmPortParams  fmPortParam;
    t_Error         err;

    p_FmHc = (t_FmHc *)XX_Malloc(sizeof(t_FmHc));
    if (!p_FmHc)
    {
        REPORT_ERROR(MINOR, E_NO_MEMORY, ("HC obj"));
        return NULL;
    }
    memset(p_FmHc,0,sizeof(t_FmHc));

    p_FmHc->h_FmPcd             = p_FmHcParams->h_FmPcd;
    p_FmHc->f_QmEnqueue         = p_FmHcParams->params.f_QmEnqueue;
    p_FmHc->h_QmArg             = p_FmHcParams->params.h_QmArg;
    p_FmHc->dataMemId           = DEFAULT_dataMemId;

    err = FillBufPool(p_FmHc);
    if (err != E_OK)
    {
        REPORT_ERROR(MAJOR, err, NO_MSG);
        FmHcFree(p_FmHc);
        return NULL;
    }

    if (!FmIsMaster(p_FmHcParams->h_Fm))
        return (t_Handle)p_FmHc;

    memset(&fmPortParam, 0, sizeof(fmPortParam));
    fmPortParam.baseAddr    = p_FmHcParams->params.portBaseAddr;
    fmPortParam.portType    = e_FM_PORT_TYPE_OH_HOST_COMMAND;
    fmPortParam.portId      = p_FmHcParams->params.portId;
    fmPortParam.liodnBase   = p_FmHcParams->params.liodnBase;
    fmPortParam.h_Fm        = p_FmHcParams->h_Fm;

    fmPortParam.specificParams.nonRxParams.errFqid      = p_FmHcParams->params.errFqid;
    fmPortParam.specificParams.nonRxParams.dfltFqid     = p_FmHcParams->params.confFqid;
    fmPortParam.specificParams.nonRxParams.qmChannel    = p_FmHcParams->params.qmChannel;

    p_FmHc->h_HcPortDev = FM_PORT_Config(&fmPortParam);
    if (!p_FmHc->h_HcPortDev)
    {
        REPORT_ERROR(MAJOR, E_INVALID_HANDLE, ("FM HC port!"));
        XX_Free(p_FmHc);
        return NULL;
    }

    err = FM_PORT_ConfigMaxFrameLength(p_FmHc->h_HcPortDev,
                                       (uint16_t)sizeof(t_HcFrame));

    if (err != E_OK)
    {
        REPORT_ERROR(MAJOR, err, ("FM HC port init!"));
        FmHcFree(p_FmHc);
        return NULL;
    }

    /* final init */
    err = FM_PORT_Init(p_FmHc->h_HcPortDev);
    if (err != E_OK)
    {
        REPORT_ERROR(MAJOR, err, ("FM HC port init!"));
        FmHcFree(p_FmHc);
        return NULL;
    }

    err = FM_PORT_Enable(p_FmHc->h_HcPortDev);
    if (err != E_OK)
    {
        REPORT_ERROR(MAJOR, err, ("FM HC port enable!"));
        FmHcFree(p_FmHc);
        return NULL;
    }

    return (t_Handle)p_FmHc;
}