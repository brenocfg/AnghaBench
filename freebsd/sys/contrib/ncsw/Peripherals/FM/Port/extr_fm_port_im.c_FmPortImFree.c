#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_12__ {int /*<<< orphan*/  h_BufferPool; int /*<<< orphan*/  (* f_PutBuf ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  f_VirtToPhys; int /*<<< orphan*/  f_PhysToVirt; } ;
struct TYPE_13__ {size_t currBdId; scalar_t__ p_BdRing; int /*<<< orphan*/ * p_BdShadow; TYPE_4__* p_FmPortImPram; int /*<<< orphan*/  h_FmMuram; TYPE_2__ rxPool; } ;
struct TYPE_11__ {int /*<<< orphan*/  gen; } ;
struct TYPE_14__ {scalar_t__ portType; TYPE_3__ im; int /*<<< orphan*/  fmanCtrlEventId; int /*<<< orphan*/  h_Fm; TYPE_1__ rxQd; scalar_t__ exceptions; int /*<<< orphan*/  polling; } ;
typedef  TYPE_4__ t_FmPort ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_4__*) ; 
 int /*<<< orphan*/  BD_GET (size_t) ; 
 int BD_R_E ; 
 int BD_STATUS_AND_LENGTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BD_STATUS_AND_LENGTH_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BdBufferGet (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BdBufferSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FM_MURAM_FreeMem (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  FmFreeFmanCtrlEventReg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FmPortImRx (TYPE_4__*) ; 
 int /*<<< orphan*/  FmSetFmanCtrlIntr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FmUnregisterFmanCtrlIntr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t GetNextBdId (TYPE_4__*,size_t) ; 
 int /*<<< orphan*/  TxConf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_UINT16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XX_Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XX_FreeSmart (scalar_t__) ; 
 scalar_t__ e_FM_PORT_TYPE_RX ; 
 scalar_t__ e_FM_PORT_TYPE_RX_10G ; 
 int /*<<< orphan*/  e_TX_CONF_TYPE_FLUSH ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void FmPortImFree(t_FmPort *p_FmPort)
{
    uint32_t    bdStatus;
    uint8_t     *p_CurData;

    ASSERT_COND(p_FmPort);
    ASSERT_COND(p_FmPort->im.p_FmPortImPram);

    if ((p_FmPort->portType == e_FM_PORT_TYPE_RX) ||
        (p_FmPort->portType == e_FM_PORT_TYPE_RX_10G))
    {
        if (!p_FmPort->polling || p_FmPort->exceptions)
        {
            /* Deallocate and unregister interrupts */
            FmSetFmanCtrlIntr(p_FmPort->h_Fm, p_FmPort->fmanCtrlEventId, 0);

            FmFreeFmanCtrlEventReg(p_FmPort->h_Fm, p_FmPort->fmanCtrlEventId);

            WRITE_UINT16(p_FmPort->im.p_FmPortImPram->rxQd.gen, 0);

            FmUnregisterFmanCtrlIntr(p_FmPort->h_Fm, p_FmPort->fmanCtrlEventId);
        }
        /* Try first clean what has received */
        FmPortImRx(p_FmPort);

        /* Now, get rid of the the empty buffer! */
        bdStatus = BD_STATUS_AND_LENGTH(BD_GET(p_FmPort->im.currBdId));

        while (bdStatus & BD_R_E) /* while there is data in the Rx BD */
        {
            p_CurData = BdBufferGet(p_FmPort->im.rxPool.f_PhysToVirt, BD_GET(p_FmPort->im.currBdId));

            BdBufferSet(p_FmPort->im.rxPool.f_VirtToPhys, BD_GET(p_FmPort->im.currBdId), NULL);
            BD_STATUS_AND_LENGTH_SET(BD_GET(p_FmPort->im.currBdId), 0);

            p_FmPort->im.rxPool.f_PutBuf(p_FmPort->im.rxPool.h_BufferPool,
                                         p_CurData,
                                         p_FmPort->im.p_BdShadow[p_FmPort->im.currBdId]);

            p_FmPort->im.currBdId = GetNextBdId(p_FmPort, p_FmPort->im.currBdId);
            bdStatus = BD_STATUS_AND_LENGTH(BD_GET(p_FmPort->im.currBdId));
        }
    }
    else
        TxConf(p_FmPort, e_TX_CONF_TYPE_FLUSH);

    FM_MURAM_FreeMem(p_FmPort->im.h_FmMuram, p_FmPort->im.p_FmPortImPram);

    if (p_FmPort->im.p_BdShadow)
        XX_Free(p_FmPort->im.p_BdShadow);

    if (p_FmPort->im.p_BdRing)
        XX_FreeSmart(p_FmPort->im.p_BdRing);
}