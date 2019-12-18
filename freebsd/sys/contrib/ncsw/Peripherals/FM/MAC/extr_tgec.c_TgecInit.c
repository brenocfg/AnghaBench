#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int majorRev; } ;
struct TYPE_3__ {struct tgec_cfg* h_Fm; TYPE_2__ fmRevInfo; int /*<<< orphan*/  macId; } ;
struct tgec_cfg {int exceptions; scalar_t__ mdioIrq; struct tgec_cfg* p_TgecDriverParam; int /*<<< orphan*/  macId; TYPE_1__ fmMacControllerDriver; void* p_UnicastAddrHash; void* p_MulticastAddrHash; int /*<<< orphan*/  p_MemMap; int /*<<< orphan*/  max_frame_length; int /*<<< orphan*/  skip_fman11_workaround; int /*<<< orphan*/  addr; } ;
typedef  struct tgec_cfg t_Tgec ;
typedef  scalar_t__ t_Handle ;
typedef  scalar_t__ t_Error ;
typedef  scalar_t__ t_EnetAddr ;

/* Variables and functions */
 void* AllocHashTable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_INIT_PARAMETERS (struct tgec_cfg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CheckInitParameters ; 
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_INVALID_STATE ; 
 scalar_t__ E_NO_MEMORY ; 
 scalar_t__ E_OK ; 
 int /*<<< orphan*/  FM_GetRevision (struct tgec_cfg*,TYPE_2__*) ; 
 int /*<<< orphan*/  FmRegisterIntr (struct tgec_cfg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tgec_cfg*) ; 
 scalar_t__ FmSetMacMaxFrame (struct tgec_cfg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeInitResources (struct tgec_cfg*) ; 
 int /*<<< orphan*/  HASH_TABLE_SIZE ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  MAKE_ENET_ADDR_FROM_UINT64 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  MINOR ; 
 scalar_t__ NO_IRQ ; 
 char* NO_MSG ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (struct tgec_cfg*,int /*<<< orphan*/ ) ; 
 int TGEC_IMASK_LOC_FAULT ; 
 int TGEC_IMASK_REM_FAULT ; 
 int /*<<< orphan*/  TgecErrException ; 
 int /*<<< orphan*/  TgecException ; 
 scalar_t__ TgecTxEccWorkaround (struct tgec_cfg*) ; 
 int /*<<< orphan*/  XX_EnableIntr (scalar_t__) ; 
 int /*<<< orphan*/  XX_Free (struct tgec_cfg*) ; 
 int /*<<< orphan*/  XX_SetIntr (scalar_t__,int /*<<< orphan*/ ,struct tgec_cfg*) ; 
 int /*<<< orphan*/  e_FM_INTR_TYPE_ERR ; 
 int /*<<< orphan*/  e_FM_MAC_10G ; 
 int /*<<< orphan*/  e_FM_MOD_10G_MAC ; 
 scalar_t__ fman_tgec_init (int /*<<< orphan*/ ,struct tgec_cfg*,int) ; 
 int /*<<< orphan*/  fman_tgec_set_erratum_tx_fifo_corruption_10gmac_a007 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fman_tgec_set_mac_address (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static t_Error TgecInit(t_Handle h_Tgec)
{
    t_Tgec                  *p_Tgec = (t_Tgec *)h_Tgec;
    struct tgec_cfg         *p_TgecDriverParam;
    t_EnetAddr              ethAddr;
    t_Error                 err;

    SANITY_CHECK_RETURN_ERROR(p_Tgec, E_INVALID_HANDLE);
    SANITY_CHECK_RETURN_ERROR(p_Tgec->p_TgecDriverParam, E_INVALID_STATE);
    SANITY_CHECK_RETURN_ERROR(p_Tgec->fmMacControllerDriver.h_Fm, E_INVALID_HANDLE);

    FM_GetRevision(p_Tgec->fmMacControllerDriver.h_Fm, &p_Tgec->fmMacControllerDriver.fmRevInfo);
    CHECK_INIT_PARAMETERS(p_Tgec, CheckInitParameters);

    p_TgecDriverParam = p_Tgec->p_TgecDriverParam;

    MAKE_ENET_ADDR_FROM_UINT64(p_Tgec->addr, ethAddr);
    fman_tgec_set_mac_address(p_Tgec->p_MemMap, (uint8_t *)ethAddr);

    /* interrupts */
#ifdef FM_10G_REM_N_LCL_FLT_EX_10GMAC_ERRATA_SW005
    {
        if (p_Tgec->fmMacControllerDriver.fmRevInfo.majorRev <=2)
            p_Tgec->exceptions &= ~(TGEC_IMASK_REM_FAULT | TGEC_IMASK_LOC_FAULT);
    }
#endif /* FM_10G_REM_N_LCL_FLT_EX_10GMAC_ERRATA_SW005 */

#ifdef FM_TX_ECC_FRMS_ERRATA_10GMAC_A004
    if (!p_Tgec->p_TgecDriverParam->skip_fman11_workaround &&
        ((err = TgecTxEccWorkaround(p_Tgec)) != E_OK))
    {
        FreeInitResources(p_Tgec);
        REPORT_ERROR(MINOR, err, ("TgecTxEccWorkaround FAILED"));
    }
#endif /* FM_TX_ECC_FRMS_ERRATA_10GMAC_A004 */

    err = fman_tgec_init(p_Tgec->p_MemMap, p_TgecDriverParam, p_Tgec->exceptions);
    if (err)
    {
        FreeInitResources(p_Tgec);
        RETURN_ERROR(MAJOR, err, ("This TGEC version does not support the required i/f mode"));
    }

    /* Max Frame Length */
    err = FmSetMacMaxFrame(p_Tgec->fmMacControllerDriver.h_Fm,
                           e_FM_MAC_10G,
                           p_Tgec->fmMacControllerDriver.macId,
                           p_TgecDriverParam->max_frame_length);
    if (err != E_OK)
    {
        FreeInitResources(p_Tgec);
        RETURN_ERROR(MINOR, err, NO_MSG);
    }
/* we consider having no IPC a non crasher... */

#ifdef FM_TX_FIFO_CORRUPTION_ERRATA_10GMAC_A007
    if (p_Tgec->fmMacControllerDriver.fmRevInfo.majorRev == 2)
        fman_tgec_set_erratum_tx_fifo_corruption_10gmac_a007(p_Tgec->p_MemMap);
#endif /* FM_TX_FIFO_CORRUPTION_ERRATA_10GMAC_A007 */

    p_Tgec->p_MulticastAddrHash = AllocHashTable(HASH_TABLE_SIZE);
    if (!p_Tgec->p_MulticastAddrHash)
    {
        FreeInitResources(p_Tgec);
        RETURN_ERROR(MAJOR, E_NO_MEMORY, ("allocation hash table is FAILED"));
    }

    p_Tgec->p_UnicastAddrHash = AllocHashTable(HASH_TABLE_SIZE);
    if (!p_Tgec->p_UnicastAddrHash)
    {
        FreeInitResources(p_Tgec);
        RETURN_ERROR(MAJOR, E_NO_MEMORY, ("allocation hash table is FAILED"));
    }

    FmRegisterIntr(p_Tgec->fmMacControllerDriver.h_Fm,
                   e_FM_MOD_10G_MAC,
                   p_Tgec->macId,
                   e_FM_INTR_TYPE_ERR,
                   TgecErrException,
                   p_Tgec);
    if (p_Tgec->mdioIrq != NO_IRQ)
    {
        XX_SetIntr(p_Tgec->mdioIrq, TgecException, p_Tgec);
        XX_EnableIntr(p_Tgec->mdioIrq);
    }

    XX_Free(p_TgecDriverParam);
    p_Tgec->p_TgecDriverParam = NULL;

    return E_OK;
}