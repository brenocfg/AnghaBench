#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_12__ {int bufferSize; scalar_t__ f_VirtToPhys; scalar_t__ f_PhysToVirt; int /*<<< orphan*/  f_PutBuf; int /*<<< orphan*/  f_GetBuf; int /*<<< orphan*/  h_BufferPool; } ;
struct TYPE_14__ {int /*<<< orphan*/  f_TxConf; int /*<<< orphan*/  f_RxStore; TYPE_1__ rxPoolParams; int /*<<< orphan*/  dataMemAttributes; int /*<<< orphan*/  dataMemId; int /*<<< orphan*/  liodnOffset; int /*<<< orphan*/  h_FmMuram; } ;
struct TYPE_15__ {TYPE_3__ imRxTxParams; } ;
struct TYPE_17__ {TYPE_4__ specificParams; } ;
typedef  TYPE_6__ t_FmPortParams ;
struct TYPE_13__ {int bufferSize; scalar_t__ f_VirtToPhys; scalar_t__ f_PhysToVirt; int /*<<< orphan*/  f_PutBuf; int /*<<< orphan*/  f_GetBuf; int /*<<< orphan*/  h_BufferPool; } ;
struct TYPE_16__ {int mrblr; int /*<<< orphan*/  bdRingSize; int /*<<< orphan*/  f_TxConf; TYPE_2__ rxPool; int /*<<< orphan*/  f_RxStore; int /*<<< orphan*/  fwExtStructsMemAttr; int /*<<< orphan*/  fwExtStructsMemId; int /*<<< orphan*/  dataMemAttributes; int /*<<< orphan*/  dataMemId; int /*<<< orphan*/  h_FmMuram; } ;
struct TYPE_18__ {scalar_t__ portType; TYPE_5__ im; scalar_t__ fmanCtrlEventId; int /*<<< orphan*/  polling; int /*<<< orphan*/  h_Fm; int /*<<< orphan*/  exceptions; TYPE_8__* p_FmPortDriverParam; } ;
typedef  TYPE_7__ t_FmPort ;
struct TYPE_19__ {int /*<<< orphan*/  liodnOffset; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_7__*) ; 
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DEFAULT_PORT_ImfwExtStructsMemAttr ; 
 int /*<<< orphan*/  DEFAULT_PORT_ImfwExtStructsMemId ; 
 int /*<<< orphan*/  DEFAULT_PORT_exception ; 
 int /*<<< orphan*/  DEFAULT_PORT_rxBdRingLength ; 
 int /*<<< orphan*/  DEFAULT_PORT_txBdRingLength ; 
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FmIsMaster (int /*<<< orphan*/ ) ; 
 scalar_t__ NO_IRQ ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARNING ; 
 scalar_t__ XX_PhysToVirt ; 
 scalar_t__ XX_VirtToPhys ; 
 scalar_t__ e_FM_PORT_TYPE_RX ; 
 scalar_t__ e_FM_PORT_TYPE_RX_10G ; 

void FmPortConfigIM (t_FmPort *p_FmPort, t_FmPortParams *p_FmPortParams)
{
    ASSERT_COND(p_FmPort);

    SANITY_CHECK_RETURN(p_FmPort->p_FmPortDriverParam, E_INVALID_HANDLE);

    p_FmPort->im.h_FmMuram                      = p_FmPortParams->specificParams.imRxTxParams.h_FmMuram;
    p_FmPort->p_FmPortDriverParam->liodnOffset  = p_FmPortParams->specificParams.imRxTxParams.liodnOffset;
    p_FmPort->im.dataMemId                      = p_FmPortParams->specificParams.imRxTxParams.dataMemId;
    p_FmPort->im.dataMemAttributes              = p_FmPortParams->specificParams.imRxTxParams.dataMemAttributes;

    p_FmPort->im.fwExtStructsMemId              = DEFAULT_PORT_ImfwExtStructsMemId;
    p_FmPort->im.fwExtStructsMemAttr            = DEFAULT_PORT_ImfwExtStructsMemAttr;

    if ((p_FmPort->portType == e_FM_PORT_TYPE_RX) ||
        (p_FmPort->portType == e_FM_PORT_TYPE_RX_10G))
    {
        p_FmPort->im.rxPool.h_BufferPool    = p_FmPortParams->specificParams.imRxTxParams.rxPoolParams.h_BufferPool;
        p_FmPort->im.rxPool.f_GetBuf        = p_FmPortParams->specificParams.imRxTxParams.rxPoolParams.f_GetBuf;
        p_FmPort->im.rxPool.f_PutBuf        = p_FmPortParams->specificParams.imRxTxParams.rxPoolParams.f_PutBuf;
        p_FmPort->im.rxPool.bufferSize      = p_FmPortParams->specificParams.imRxTxParams.rxPoolParams.bufferSize;
        p_FmPort->im.rxPool.f_PhysToVirt    = p_FmPortParams->specificParams.imRxTxParams.rxPoolParams.f_PhysToVirt;
        if (!p_FmPort->im.rxPool.f_PhysToVirt)
            p_FmPort->im.rxPool.f_PhysToVirt = XX_PhysToVirt;
        p_FmPort->im.rxPool.f_VirtToPhys    = p_FmPortParams->specificParams.imRxTxParams.rxPoolParams.f_VirtToPhys;
        if (!p_FmPort->im.rxPool.f_VirtToPhys)
            p_FmPort->im.rxPool.f_VirtToPhys = XX_VirtToPhys;
        p_FmPort->im.f_RxStore              = p_FmPortParams->specificParams.imRxTxParams.f_RxStore;

        p_FmPort->im.mrblr                  = 0x8000;
        while (p_FmPort->im.mrblr)
        {
            if (p_FmPort->im.rxPool.bufferSize & p_FmPort->im.mrblr)
                break;
            p_FmPort->im.mrblr >>= 1;
        }
        if (p_FmPort->im.mrblr != p_FmPort->im.rxPool.bufferSize)
            DBG(WARNING, ("Max-Rx-Buffer-Length set to %d", p_FmPort->im.mrblr));
        p_FmPort->im.bdRingSize             = DEFAULT_PORT_rxBdRingLength;
        p_FmPort->exceptions                = DEFAULT_PORT_exception;
        if (FmIsMaster(p_FmPort->h_Fm))
            p_FmPort->polling               = FALSE;
        else
            p_FmPort->polling               = TRUE;
        p_FmPort->fmanCtrlEventId           = (uint8_t)NO_IRQ;
    }
    else
    {
        p_FmPort->im.f_TxConf               = p_FmPortParams->specificParams.imRxTxParams.f_TxConf;

        p_FmPort->im.bdRingSize             = DEFAULT_PORT_txBdRingLength;
    }
}