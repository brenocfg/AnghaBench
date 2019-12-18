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
typedef  int uint16_t ;
typedef  scalar_t__ t_Handle ;
typedef  scalar_t__ t_Error ;
typedef  scalar_t__ t_EnetAddr ;
struct TYPE_4__ {int /*<<< orphan*/  minorRev; int /*<<< orphan*/  majorRev; } ;
struct TYPE_3__ {struct dtsec_cfg* h_Fm; int /*<<< orphan*/  macId; TYPE_2__ fmRevInfo; } ;
struct dtsec_cfg {int enetMode; scalar_t__ mdioIrq; struct dtsec_cfg* p_DtsecDriverParam; int /*<<< orphan*/  macId; TYPE_1__ fmMacControllerDriver; void* p_UnicastAddrHash; void* p_MulticastAddrHash; int /*<<< orphan*/  p_MemMap; scalar_t__ tbipa; int /*<<< orphan*/  exceptions; int /*<<< orphan*/  addr; int /*<<< orphan*/  halfdup_on; int /*<<< orphan*/  halfDuplex; } ;
typedef  struct dtsec_cfg t_Dtsec ;
typedef  enum enet_speed { ____Placeholder_enet_speed } enet_speed ;
typedef  enum enet_interface { ____Placeholder_enet_interface } enet_interface ;

/* Variables and functions */
 void* AllocHashTable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_INIT_PARAMETERS (struct dtsec_cfg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CheckInitParameters ; 
 int /*<<< orphan*/  DTSEC_MII_WritePhyReg (struct dtsec_cfg*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  Dtsec1588Isr ; 
 int /*<<< orphan*/  DtsecIsr ; 
 int /*<<< orphan*/  DtsecMdioIsr ; 
 scalar_t__ DtsecSetStatistics (scalar_t__,int /*<<< orphan*/ ) ; 
 int ENET_IF_SGMII_BASEX ; 
 scalar_t__ ENET_INTERFACE_FROM_MODE (int) ; 
 scalar_t__ ENET_SPEED_FROM_MODE (int) ; 
 int /*<<< orphan*/  EXTENDED_HASH_TABLE_SIZE ; 
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_INVALID_STATE ; 
 scalar_t__ E_NO_MEMORY ; 
 scalar_t__ E_OK ; 
 int /*<<< orphan*/  FM_GetRevision (struct dtsec_cfg*,TYPE_2__*) ; 
 int /*<<< orphan*/  FmRegisterIntr (struct dtsec_cfg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dtsec_cfg*) ; 
 scalar_t__ FmSetMacMaxFrame (struct dtsec_cfg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FreeInitResources (struct dtsec_cfg*) ; 
 int /*<<< orphan*/  HASH_TABLE_SIZE ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  MAKE_ENET_ADDR_FROM_UINT64 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  MINOR ; 
 scalar_t__ NO_IRQ ; 
 char* NO_MSG ; 
 int PHY_CR_ANE ; 
 int PHY_CR_FULLDUPLEX ; 
 int PHY_CR_PHY_RESET ; 
 int PHY_CR_RESET_AN ; 
 int PHY_CR_SPEED1 ; 
 int PHY_TBIANA_1000X ; 
 int PHY_TBIANA_SGMII ; 
 int PHY_TBICON_CLK_SEL ; 
 int PHY_TBICON_SRESET ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (struct dtsec_cfg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XX_EnableIntr (scalar_t__) ; 
 int /*<<< orphan*/  XX_Free (struct dtsec_cfg*) ; 
 int /*<<< orphan*/  XX_SetIntr (scalar_t__,int /*<<< orphan*/ ,struct dtsec_cfg*) ; 
 scalar_t__ e_ENET_IF_SGMII ; 
 int /*<<< orphan*/  e_FM_INTR_TYPE_ERR ; 
 int /*<<< orphan*/  e_FM_INTR_TYPE_NORMAL ; 
 int /*<<< orphan*/  e_FM_MAC_1G ; 
 int /*<<< orphan*/  e_FM_MAC_FULL_STATISTICS ; 
 int /*<<< orphan*/  e_FM_MOD_1G_MAC ; 
 int fman_dtsec_get_max_frame_len (int /*<<< orphan*/ ) ; 
 scalar_t__ fman_dtsec_init (int /*<<< orphan*/ ,struct dtsec_cfg*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static t_Error DtsecInit(t_Handle h_Dtsec)
{
    t_Dtsec             *p_Dtsec = (t_Dtsec *)h_Dtsec;
    struct dtsec_cfg    *p_DtsecDriverParam;
    t_Error             err;
    uint16_t            maxFrmLn;
    enum enet_interface enet_interface;
    enum enet_speed     enet_speed;
    t_EnetAddr          ethAddr;

    SANITY_CHECK_RETURN_ERROR(p_Dtsec, E_INVALID_HANDLE);
    SANITY_CHECK_RETURN_ERROR(p_Dtsec->p_DtsecDriverParam, E_INVALID_STATE);
    SANITY_CHECK_RETURN_ERROR(p_Dtsec->fmMacControllerDriver.h_Fm, E_INVALID_HANDLE);

    FM_GetRevision(p_Dtsec->fmMacControllerDriver.h_Fm, &p_Dtsec->fmMacControllerDriver.fmRevInfo);
    CHECK_INIT_PARAMETERS(p_Dtsec, CheckInitParameters);

    p_DtsecDriverParam  = p_Dtsec->p_DtsecDriverParam;
    p_Dtsec->halfDuplex = p_DtsecDriverParam->halfdup_on;

    enet_interface = (enum enet_interface)ENET_INTERFACE_FROM_MODE(p_Dtsec->enetMode);
    enet_speed = (enum enet_speed)ENET_SPEED_FROM_MODE(p_Dtsec->enetMode);
    MAKE_ENET_ADDR_FROM_UINT64(p_Dtsec->addr, ethAddr);

    err = (t_Error)fman_dtsec_init(p_Dtsec->p_MemMap,
                              p_DtsecDriverParam,
                              enet_interface,
                              enet_speed,
                              (uint8_t*)ethAddr,
                              p_Dtsec->fmMacControllerDriver.fmRevInfo.majorRev,
                              p_Dtsec->fmMacControllerDriver.fmRevInfo.minorRev,
                              p_Dtsec->exceptions);
    if (err)
    {
        FreeInitResources(p_Dtsec);
        RETURN_ERROR(MAJOR, err, ("This DTSEC version does not support the required i/f mode"));
    }

    if (ENET_INTERFACE_FROM_MODE(p_Dtsec->enetMode) == e_ENET_IF_SGMII)
    {
        uint16_t            tmpReg16;

        /* Configure the TBI PHY Control Register */
        tmpReg16 = PHY_TBICON_CLK_SEL | PHY_TBICON_SRESET;
        DTSEC_MII_WritePhyReg(p_Dtsec, (uint8_t)p_DtsecDriverParam->tbipa, 17, tmpReg16);

        tmpReg16 = PHY_TBICON_CLK_SEL;
        DTSEC_MII_WritePhyReg(p_Dtsec, (uint8_t)p_DtsecDriverParam->tbipa, 17, tmpReg16);

        tmpReg16 = (PHY_CR_PHY_RESET | PHY_CR_ANE | PHY_CR_FULLDUPLEX | PHY_CR_SPEED1);
        DTSEC_MII_WritePhyReg(p_Dtsec, (uint8_t)p_DtsecDriverParam->tbipa, 0, tmpReg16);

        if (p_Dtsec->enetMode & ENET_IF_SGMII_BASEX)
            tmpReg16 = PHY_TBIANA_1000X;
        else
            tmpReg16 = PHY_TBIANA_SGMII;
        DTSEC_MII_WritePhyReg(p_Dtsec, (uint8_t)p_DtsecDriverParam->tbipa, 4, tmpReg16);

        tmpReg16 = (PHY_CR_ANE | PHY_CR_RESET_AN | PHY_CR_FULLDUPLEX | PHY_CR_SPEED1);

        DTSEC_MII_WritePhyReg(p_Dtsec, (uint8_t)p_DtsecDriverParam->tbipa, 0, tmpReg16);
    }

    /* Max Frame Length */
    maxFrmLn = fman_dtsec_get_max_frame_len(p_Dtsec->p_MemMap);
    err = FmSetMacMaxFrame(p_Dtsec->fmMacControllerDriver.h_Fm, e_FM_MAC_1G,
            p_Dtsec->fmMacControllerDriver.macId, maxFrmLn);
    if (err)
        RETURN_ERROR(MINOR,err, NO_MSG);

    p_Dtsec->p_MulticastAddrHash = AllocHashTable(EXTENDED_HASH_TABLE_SIZE);
    if (!p_Dtsec->p_MulticastAddrHash) {
        FreeInitResources(p_Dtsec);
        RETURN_ERROR(MAJOR, E_NO_MEMORY, ("MC hash table is FAILED"));
    }

    p_Dtsec->p_UnicastAddrHash = AllocHashTable(HASH_TABLE_SIZE);
    if (!p_Dtsec->p_UnicastAddrHash)
    {
        FreeInitResources(p_Dtsec);
        RETURN_ERROR(MAJOR, E_NO_MEMORY, ("UC hash table is FAILED"));
    }

    /* register err intr handler for dtsec to FPM (err)*/
    FmRegisterIntr(p_Dtsec->fmMacControllerDriver.h_Fm,
                   e_FM_MOD_1G_MAC,
                   p_Dtsec->macId,
                   e_FM_INTR_TYPE_ERR,
                   DtsecIsr,
                   p_Dtsec);
    /* register 1588 intr handler for TMR to FPM (normal)*/
    FmRegisterIntr(p_Dtsec->fmMacControllerDriver.h_Fm,
                   e_FM_MOD_1G_MAC,
                   p_Dtsec->macId,
                   e_FM_INTR_TYPE_NORMAL,
                   Dtsec1588Isr,
                   p_Dtsec);
    /* register normal intr handler for dtsec to main interrupt controller. */
    if (p_Dtsec->mdioIrq != NO_IRQ)
    {
        XX_SetIntr(p_Dtsec->mdioIrq, DtsecMdioIsr, p_Dtsec);
        XX_EnableIntr(p_Dtsec->mdioIrq);
    }

    XX_Free(p_DtsecDriverParam);
    p_Dtsec->p_DtsecDriverParam = NULL;

    err = DtsecSetStatistics(h_Dtsec, e_FM_MAC_FULL_STATISTICS);
    if (err)
    {
        FreeInitResources(p_Dtsec);
        RETURN_ERROR(MAJOR, err, ("Undefined statistics level"));
    }

    return E_OK;
}