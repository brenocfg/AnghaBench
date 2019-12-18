#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ guestId; int exceptions; TYPE_1__* p_FmPcdKg; int /*<<< orphan*/  h_Fm; } ;
typedef  TYPE_2__ t_FmPcd ;
typedef  scalar_t__ t_Error ;
struct fman_kg_regs {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  schemesIds; scalar_t__ numOfSchemes; struct fman_kg_regs* p_FmPcdKgRegs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 scalar_t__ E_OK ; 
 int FM_EX_KG_DOUBLE_ECC ; 
 int /*<<< orphan*/  FmEnableRamsEcc (int /*<<< orphan*/ ) ; 
 scalar_t__ FmPcdKgAllocSchemes (TYPE_2__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FmRegisterIntr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  GET_NIA_BMI_AC_ENQ_FRAME (TYPE_2__*) ; 
 int /*<<< orphan*/  MINOR ; 
 scalar_t__ NCSW_MASTER_ID ; 
 int /*<<< orphan*/  NO_MSG ; 
 int /*<<< orphan*/  PcdKgErrorException ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e_FM_INTR_TYPE_ERR ; 
 int /*<<< orphan*/  e_FM_MOD_KG ; 
 int /*<<< orphan*/  fman_kg_enable_scheme_interrupts (struct fman_kg_regs*) ; 
 int /*<<< orphan*/  fman_kg_init (struct fman_kg_regs*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static t_Error KgInitMaster(t_FmPcd *p_FmPcd)
{
    t_Error                     err = E_OK;
    struct fman_kg_regs         *p_Regs = p_FmPcd->p_FmPcdKg->p_FmPcdKgRegs;

    ASSERT_COND(p_FmPcd->guestId == NCSW_MASTER_ID);

    if (p_FmPcd->exceptions & FM_EX_KG_DOUBLE_ECC)
        FmEnableRamsEcc(p_FmPcd->h_Fm);

    fman_kg_init(p_Regs, p_FmPcd->exceptions, GET_NIA_BMI_AC_ENQ_FRAME(p_FmPcd));

    /* register even if no interrupts enabled, to allow future enablement */
    FmRegisterIntr(p_FmPcd->h_Fm,
                   e_FM_MOD_KG,
                   0,
                   e_FM_INTR_TYPE_ERR,
                   PcdKgErrorException,
                   p_FmPcd);

    fman_kg_enable_scheme_interrupts(p_Regs);

    if (p_FmPcd->p_FmPcdKg->numOfSchemes)
    {
        err = FmPcdKgAllocSchemes(p_FmPcd,
                                  p_FmPcd->p_FmPcdKg->numOfSchemes,
                                  p_FmPcd->guestId,
                                  p_FmPcd->p_FmPcdKg->schemesIds);
        if (err)
            RETURN_ERROR(MINOR, err, NO_MSG);
    }

    return E_OK;
}