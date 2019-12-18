#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  txScParams ;
struct TYPE_14__ {void* sci; int /*<<< orphan*/  scId; void* cipherSuite; int /*<<< orphan*/  confidentialityOffset; int /*<<< orphan*/  confidentialityEnable; int /*<<< orphan*/  protectFrames; int /*<<< orphan*/  sciInsertionMode; int /*<<< orphan*/  validateFrames; int /*<<< orphan*/  replayWindow; int /*<<< orphan*/  replayProtect; } ;
typedef  TYPE_1__ t_TxScParams ;
struct TYPE_15__ {scalar_t__ inUse; int /*<<< orphan*/  scId; } ;
typedef  TYPE_2__ t_SecYSc ;
typedef  TYPE_1__ t_RxScParams ;
typedef  TYPE_2__* t_Handle ;
struct TYPE_16__ {size_t numOfRxSc; size_t numOfTxSc; struct TYPE_16__* h_FmMacsec; int /*<<< orphan*/  confidentialityOffset; int /*<<< orphan*/  confidentialityEnable; int /*<<< orphan*/  protectFrames; int /*<<< orphan*/  sciInsertionMode; TYPE_2__* p_TxSc; int /*<<< orphan*/  validateFrames; int /*<<< orphan*/  replayWindow; int /*<<< orphan*/  replayProtect; TYPE_2__* p_RxSc; } ;
typedef  TYPE_5__ t_FmMacsecSecY ;
typedef  int /*<<< orphan*/  t_Error ;
typedef  int /*<<< orphan*/  rxScParams ;
typedef  void* macsecSCI_t ;
typedef  scalar_t__ e_ScType ;
typedef  void* e_FmMacsecSecYCipherSuite ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_5__*) ; 
 int /*<<< orphan*/  E_FULL ; 
 int /*<<< orphan*/  E_NO_MEMORY ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  FmMacsecCreateRxSc (TYPE_5__*,TYPE_1__*) ; 
 int /*<<< orphan*/  FmMacsecCreateTxSc (TYPE_5__*,TYPE_1__*) ; 
 int /*<<< orphan*/  MAJOR ; 
 size_t NUM_OF_RX_SC ; 
 size_t NUM_OF_TX_SC ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ TRUE ; 
 scalar_t__ e_SC_RX ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static t_Handle FmMacsecSecYCreateSc(t_FmMacsecSecY             *p_FmMacsecSecY,
                                     macsecSCI_t                sci,
                                     e_FmMacsecSecYCipherSuite  cipherSuite,
                                     e_ScType                   type)
{
    t_SecYSc        *p_ScTable;
    void            *p_Params;
    uint32_t        numOfSc,i;
    t_Error         err = E_OK;
    t_RxScParams    rxScParams;
    t_TxScParams    txScParams;

    ASSERT_COND(p_FmMacsecSecY);
    ASSERT_COND(p_FmMacsecSecY->h_FmMacsec);

    if (type == e_SC_RX)
    {
        memset(&rxScParams, 0, sizeof(rxScParams));
        i                                   = (NUM_OF_RX_SC - 1);
        p_ScTable                           = p_FmMacsecSecY->p_RxSc;
        numOfSc                             = p_FmMacsecSecY->numOfRxSc;
        rxScParams.confidentialityOffset    = p_FmMacsecSecY->confidentialityOffset;
        rxScParams.replayProtect            = p_FmMacsecSecY->replayProtect;
        rxScParams.replayWindow             = p_FmMacsecSecY->replayWindow;
        rxScParams.validateFrames           = p_FmMacsecSecY->validateFrames;
        rxScParams.cipherSuite              = cipherSuite;
        p_Params = &rxScParams;
    }
    else
    {
        memset(&txScParams, 0, sizeof(txScParams));
        i                                   = (NUM_OF_TX_SC - 1);
        p_ScTable                           = p_FmMacsecSecY->p_TxSc;
        numOfSc                             = p_FmMacsecSecY->numOfTxSc;
        txScParams.sciInsertionMode         = p_FmMacsecSecY->sciInsertionMode;
        txScParams.protectFrames            = p_FmMacsecSecY->protectFrames;
        txScParams.confidentialityEnable    = p_FmMacsecSecY->confidentialityEnable;
        txScParams.confidentialityOffset    = p_FmMacsecSecY->confidentialityOffset;
        txScParams.cipherSuite              = cipherSuite;
        p_Params = &txScParams;
    }

    for (i=0;i<numOfSc;i++)
        if (!p_ScTable[i].inUse)
            break;
    if (i == numOfSc)
    {
        REPORT_ERROR(MAJOR, E_FULL, ("FM MACSEC SECY SC"));
        return NULL;
    }

    if (type == e_SC_RX)
    {
        ((t_RxScParams *)p_Params)->scId = p_ScTable[i].scId;
        ((t_RxScParams *)p_Params)->sci  = sci;
        if ((err = FmMacsecCreateRxSc(p_FmMacsecSecY->h_FmMacsec, (t_RxScParams *)p_Params)) != E_OK)
        {
            REPORT_ERROR(MAJOR, E_NO_MEMORY, ("FM MACSEC SECY RX SC"));
            return NULL;
        }
    }
    else
    {
        ((t_TxScParams *)p_Params)->scId = p_ScTable[i].scId;
        ((t_TxScParams *)p_Params)->sci  = sci;
        if ((err = FmMacsecCreateTxSc(p_FmMacsecSecY->h_FmMacsec, (t_TxScParams *)p_Params)) != E_OK)
        {
            REPORT_ERROR(MAJOR, E_NO_MEMORY, ("FM MACSEC SECY TX SC"));
            return NULL;
        }
    }

    p_ScTable[i].inUse = TRUE;
    return &p_ScTable[i];
}