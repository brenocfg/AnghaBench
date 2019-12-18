#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_11__ {size_t changedTextWithNoEncryptDeliverUncontrolled; size_t onlyScbIsSetDeliverUncontrolled; size_t unknownSciTreatMode; size_t invalidTagsDeliverUncontrolled; size_t encryptWithNoChangedTextDiscardUncontrolled; size_t untagTreatMode; size_t keysUnreadable; size_t reservedSc0; size_t byPassMode; size_t pnExhThr; size_t exceptions; int /*<<< orphan*/  h_Fm; int /*<<< orphan*/  h_FmMac; struct TYPE_11__* p_FmMacsecDriverParam; int /*<<< orphan*/  numTxScAvailable; int /*<<< orphan*/  numRxScAvailable; TYPE_2__* p_FmMacsecRegs; int /*<<< orphan*/  userExceptions; scalar_t__ mflSubtract; TYPE_1__* intrMng; } ;
typedef  TYPE_3__ t_FmMacsecDriverParam ;
typedef  TYPE_3__ t_FmMacsec ;
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_10__ {int /*<<< orphan*/  erer; int /*<<< orphan*/  tpnet; int /*<<< orphan*/  mfl; int /*<<< orphan*/  cfg; } ;
struct TYPE_9__ {int /*<<< orphan*/  f_Isr; } ;

/* Variables and functions */
 size_t CFG_BYPN_SHIFT ; 
 size_t CFG_ESCBT_SHIFT ; 
 size_t CFG_ITT_SHIFT ; 
 size_t CFG_KFT_SHIFT ; 
 size_t CFG_KSS_SHIFT ; 
 size_t CFG_S0I_SHIFT ; 
 size_t CFG_UECT_SHIFT ; 
 size_t CFG_UFT_SHIFT ; 
 size_t CFG_USFT_SHIFT ; 
 int /*<<< orphan*/  CHECK_INIT_PARAMETERS (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CheckFmMacsecParameters ; 
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_OK ; 
 size_t FM_MACSEC_EX_ECC ; 
 int /*<<< orphan*/  FM_MAC_GetId (int /*<<< orphan*/ ,size_t*) ; 
 size_t FM_MAC_GetMaxFrameLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FmRegisterIntr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  MacsecErrorIsr ; 
 int /*<<< orphan*/  MacsecEventIsr ; 
 int /*<<< orphan*/  NUM_OF_RX_SC ; 
 int /*<<< orphan*/  NUM_OF_TX_SC ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnimplementedIsr ; 
 int /*<<< orphan*/  WRITE_UINT32 (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  XX_Free (TYPE_3__*) ; 
 int /*<<< orphan*/  e_FM_INTR_TYPE_ERR ; 
 int /*<<< orphan*/  e_FM_INTR_TYPE_NORMAL ; 
 size_t e_FM_MACSEC_EV_DUMMY_LAST ; 
 int /*<<< orphan*/  e_FM_MOD_MACSEC ; 

__attribute__((used)) static t_Error MacsecInit(t_Handle h_FmMacsec)
{
    t_FmMacsec                  *p_FmMacsec = (t_FmMacsec*)h_FmMacsec;
    t_FmMacsecDriverParam       *p_FmMacsecDriverParam = NULL;
    uint32_t                    tmpReg,i,macId;

    SANITY_CHECK_RETURN_ERROR(p_FmMacsec, E_INVALID_HANDLE);
    SANITY_CHECK_RETURN_ERROR(p_FmMacsec->p_FmMacsecDriverParam, E_INVALID_HANDLE);

    CHECK_INIT_PARAMETERS(p_FmMacsec, CheckFmMacsecParameters);

    p_FmMacsecDriverParam = p_FmMacsec->p_FmMacsecDriverParam;

    for (i=0;i<e_FM_MACSEC_EV_DUMMY_LAST;i++)
        p_FmMacsec->intrMng[i].f_Isr = UnimplementedIsr;

    tmpReg = 0;
    tmpReg |= (p_FmMacsecDriverParam->changedTextWithNoEncryptDeliverUncontrolled << CFG_UECT_SHIFT)|
              (p_FmMacsecDriverParam->onlyScbIsSetDeliverUncontrolled << CFG_ESCBT_SHIFT)           |
              (p_FmMacsecDriverParam->unknownSciTreatMode << CFG_USFT_SHIFT)                        |
              (p_FmMacsecDriverParam->invalidTagsDeliverUncontrolled << CFG_ITT_SHIFT)              |
              (p_FmMacsecDriverParam->encryptWithNoChangedTextDiscardUncontrolled << CFG_KFT_SHIFT) |
              (p_FmMacsecDriverParam->untagTreatMode << CFG_UFT_SHIFT)                              |
              (p_FmMacsecDriverParam->keysUnreadable << CFG_KSS_SHIFT)                              |
              (p_FmMacsecDriverParam->reservedSc0 << CFG_S0I_SHIFT)                                 |
              (p_FmMacsecDriverParam->byPassMode << CFG_BYPN_SHIFT);
    WRITE_UINT32(p_FmMacsec->p_FmMacsecRegs->cfg, tmpReg);

    tmpReg = FM_MAC_GetMaxFrameLength(p_FmMacsec->h_FmMac);
    /* At least Ethernet FCS (4 bytes) overhead must be subtracted from MFL.
     * In addition, the SCI (8 bytes) overhead might be subtracted as well. */
    tmpReg -= p_FmMacsecDriverParam->mflSubtract;
    WRITE_UINT32(p_FmMacsec->p_FmMacsecRegs->mfl, tmpReg);

    WRITE_UINT32(p_FmMacsec->p_FmMacsecRegs->tpnet, p_FmMacsecDriverParam->pnExhThr);

    if (!p_FmMacsec->userExceptions)
        p_FmMacsec->exceptions &= ~FM_MACSEC_EX_ECC;
    WRITE_UINT32(p_FmMacsec->p_FmMacsecRegs->erer, p_FmMacsec->exceptions);

    p_FmMacsec->numRxScAvailable = NUM_OF_RX_SC;
    if (p_FmMacsecDriverParam->reservedSc0)
        p_FmMacsec->numRxScAvailable --;
    p_FmMacsec->numTxScAvailable = NUM_OF_TX_SC;

    XX_Free(p_FmMacsecDriverParam);
    p_FmMacsec->p_FmMacsecDriverParam = NULL;

    FM_MAC_GetId(p_FmMacsec->h_FmMac, &macId);
    FmRegisterIntr(p_FmMacsec->h_Fm,
                   e_FM_MOD_MACSEC,
                   (uint8_t)macId,
                   e_FM_INTR_TYPE_NORMAL,
                   MacsecEventIsr,
                   p_FmMacsec);

    FmRegisterIntr(p_FmMacsec->h_Fm,
                   e_FM_MOD_MACSEC,
                   0,
                   e_FM_INTR_TYPE_ERR,
                   MacsecErrorIsr,
                   p_FmMacsec);

    return E_OK;
}