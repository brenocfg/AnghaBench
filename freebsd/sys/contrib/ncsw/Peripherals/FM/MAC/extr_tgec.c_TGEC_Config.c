#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t_TgecMiiAccessMemMap ;
struct tgec_cfg {int /*<<< orphan*/  h_App; int /*<<< orphan*/  f_Event; int /*<<< orphan*/  f_Exception; int /*<<< orphan*/  mdioIrq; int /*<<< orphan*/  exceptions; int /*<<< orphan*/  macId; int /*<<< orphan*/  enetMode; int /*<<< orphan*/  addr; int /*<<< orphan*/ * p_MiiMemMap; struct tgec_regs* p_MemMap; struct tgec_cfg* p_TgecDriverParam; int /*<<< orphan*/  fmMacControllerDriver; } ;
typedef  struct tgec_cfg t_Tgec ;
typedef  struct tgec_cfg* t_Handle ;
struct TYPE_4__ {uintptr_t baseAddr; int /*<<< orphan*/  h_App; int /*<<< orphan*/  f_Event; int /*<<< orphan*/  f_Exception; int /*<<< orphan*/  mdioIrq; int /*<<< orphan*/  macId; int /*<<< orphan*/  enetMode; int /*<<< orphan*/  addr; } ;
typedef  TYPE_1__ t_FmMacParams ;
struct tgec_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_exceptions ; 
 int /*<<< orphan*/  ENET_ADDR_TO_UINT64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_NO_MEMORY ; 
 int /*<<< orphan*/  E_NULL_POINTER ; 
 int /*<<< orphan*/  InitFmMacControllerDriver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_VALUE (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 uintptr_t TGEC_TO_MII_OFFSET ; 
 scalar_t__ UINT_TO_PTR (uintptr_t) ; 
 int /*<<< orphan*/  XX_Free (struct tgec_cfg*) ; 
 scalar_t__ XX_Malloc (int) ; 
 int /*<<< orphan*/  fman_tgec_defconfig (struct tgec_cfg*) ; 
 int /*<<< orphan*/  memset (struct tgec_cfg*,int /*<<< orphan*/ ,int) ; 

t_Handle TGEC_Config(t_FmMacParams *p_FmMacParam)
{
    t_Tgec              *p_Tgec;
    struct tgec_cfg     *p_TgecDriverParam;
    uintptr_t           baseAddr;

    SANITY_CHECK_RETURN_VALUE(p_FmMacParam, E_NULL_POINTER, NULL);

    baseAddr = p_FmMacParam->baseAddr;
    /* allocate memory for the UCC GETH data structure. */
    p_Tgec = (t_Tgec *)XX_Malloc(sizeof(t_Tgec));
    if (!p_Tgec)
    {
        REPORT_ERROR(MAJOR, E_NO_MEMORY, ("10G MAC driver structure"));
        return NULL;
    }
    memset(p_Tgec, 0, sizeof(t_Tgec));
    InitFmMacControllerDriver(&p_Tgec->fmMacControllerDriver);

    /* allocate memory for the 10G MAC driver parameters data structure. */
    p_TgecDriverParam = (struct tgec_cfg *) XX_Malloc(sizeof(struct tgec_cfg));
    if (!p_TgecDriverParam)
    {
        REPORT_ERROR(MAJOR, E_NO_MEMORY, ("10G MAC driver parameters"));
        XX_Free(p_Tgec);
        return NULL;
    }
    memset(p_TgecDriverParam, 0, sizeof(struct tgec_cfg));

    /* Plant parameter structure pointer */
    p_Tgec->p_TgecDriverParam = p_TgecDriverParam;

    fman_tgec_defconfig(p_TgecDriverParam);

    p_Tgec->p_MemMap        = (struct tgec_regs *)UINT_TO_PTR(baseAddr);
    p_Tgec->p_MiiMemMap     = (t_TgecMiiAccessMemMap *)UINT_TO_PTR(baseAddr + TGEC_TO_MII_OFFSET);
    p_Tgec->addr            = ENET_ADDR_TO_UINT64(p_FmMacParam->addr);
    p_Tgec->enetMode        = p_FmMacParam->enetMode;
    p_Tgec->macId           = p_FmMacParam->macId;
    p_Tgec->exceptions      = DEFAULT_exceptions;
    p_Tgec->mdioIrq         = p_FmMacParam->mdioIrq;
    p_Tgec->f_Exception     = p_FmMacParam->f_Exception;
    p_Tgec->f_Event         = p_FmMacParam->f_Event;
    p_Tgec->h_App           = p_FmMacParam->h_App;

    return p_Tgec;
}