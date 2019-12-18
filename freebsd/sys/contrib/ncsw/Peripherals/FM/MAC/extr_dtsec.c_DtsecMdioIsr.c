#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_2__ {int /*<<< orphan*/  h_App; int /*<<< orphan*/  (* f_Event ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;struct dtsec_regs* p_MemMap; } ;
typedef  TYPE_1__ t_Dtsec ;
struct dtsec_regs {int /*<<< orphan*/  ievent; int /*<<< orphan*/  imask; } ;

/* Variables and functions */
 int DTSEC_IMASK_MMRDEN ; 
 int DTSEC_IMASK_MMWREN ; 
 int GET_UINT32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_UINT32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  e_FM_MAC_EX_1G_MII_MNG_RD_COMPLET ; 
 int /*<<< orphan*/  e_FM_MAC_EX_1G_MII_MNG_WR_COMPLET ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void DtsecMdioIsr(t_Handle h_Dtsec)
{
    t_Dtsec             *p_Dtsec = (t_Dtsec *)h_Dtsec;
    uint32_t            event;
    struct dtsec_regs   *p_DtsecMemMap = p_Dtsec->p_MemMap;

    event = GET_UINT32(p_DtsecMemMap->ievent);
    /* handle only MDIO events */
    event &= (DTSEC_IMASK_MMRDEN | DTSEC_IMASK_MMWREN);
    if (event)
    {
        event &= GET_UINT32(p_DtsecMemMap->imask);

        WRITE_UINT32(p_DtsecMemMap->ievent, event);

        if (event & DTSEC_IMASK_MMRDEN)
            p_Dtsec->f_Event(p_Dtsec->h_App, e_FM_MAC_EX_1G_MII_MNG_RD_COMPLET);
        if (event & DTSEC_IMASK_MMWREN)
            p_Dtsec->f_Event(p_Dtsec->h_App, e_FM_MAC_EX_1G_MII_MNG_WR_COMPLET);
    }
}