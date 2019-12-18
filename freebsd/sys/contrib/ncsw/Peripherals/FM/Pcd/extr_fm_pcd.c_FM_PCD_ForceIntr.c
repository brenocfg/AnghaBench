#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int t_Handle ;
struct TYPE_10__ {scalar_t__ guestId; int exceptions; TYPE_4__* p_FmPcdPlcr; TYPE_2__* p_FmPcdKg; int /*<<< orphan*/  p_FmPcdPrs; int /*<<< orphan*/  p_FmPcdDriverParam; } ;
typedef  TYPE_5__ t_FmPcd ;
typedef  int /*<<< orphan*/  t_Error ;
typedef  int e_FmPcdExceptions ;
struct TYPE_9__ {TYPE_3__* p_FmPcdPlcrRegs; } ;
struct TYPE_8__ {int /*<<< orphan*/  fmpl_ifr; int /*<<< orphan*/  fmpl_eifr; } ;
struct TYPE_7__ {TYPE_1__* p_FmPcdKgRegs; } ;
struct TYPE_6__ {int /*<<< orphan*/  fmkg_feer; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_INVALID_STATE ; 
 int /*<<< orphan*/  E_NOT_SUPPORTED ; 
 int /*<<< orphan*/  E_OK ; 
 int FM_EX_KG_DOUBLE_ECC ; 
 int FM_EX_KG_KEYSIZE_OVERFLOW ; 
 int FM_PCD_EX_PLCR_ATOMIC_ACTION_COMPLETE ; 
 int FM_PCD_EX_PLCR_DOUBLE_ECC ; 
 int FM_PCD_EX_PLCR_INIT_ENTRY_ERROR ; 
 int FM_PCD_EX_PLCR_PRAM_SELF_INIT_COMPLETE ; 
 int FM_PCD_EX_PRS_DOUBLE_ECC ; 
 int FM_PCD_EX_PRS_SINGLE_ECC ; 
 int FM_PCD_PLCR_ATOMIC_ACTION_COMPLETE ; 
 int FM_PCD_PLCR_DOUBLE_ECC ; 
 int FM_PCD_PLCR_INIT_ENTRY_ERROR ; 
 int FM_PCD_PLCR_PRAM_SELF_INIT_COMPLETE ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  MINOR ; 
 scalar_t__ NCSW_MASTER_ID ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_UINT32 (int /*<<< orphan*/ ,int) ; 
#define  e_FM_PCD_KG_EXCEPTION_DOUBLE_ECC 135 
#define  e_FM_PCD_KG_EXCEPTION_KEYSIZE_OVERFLOW 134 
#define  e_FM_PCD_PLCR_EXCEPTION_ATOMIC_ACTION_COMPLETE 133 
#define  e_FM_PCD_PLCR_EXCEPTION_DOUBLE_ECC 132 
#define  e_FM_PCD_PLCR_EXCEPTION_INIT_ENTRY_ERROR 131 
#define  e_FM_PCD_PLCR_EXCEPTION_PRAM_SELF_INIT_COMPLETE 130 
#define  e_FM_PCD_PRS_EXCEPTION_DOUBLE_ECC 129 
#define  e_FM_PCD_PRS_EXCEPTION_SINGLE_ECC 128 

t_Error FM_PCD_ForceIntr (t_Handle h_FmPcd, e_FmPcdExceptions exception)
{
    t_FmPcd            *p_FmPcd = (t_FmPcd*)h_FmPcd;

    SANITY_CHECK_RETURN_ERROR(h_FmPcd, E_INVALID_HANDLE);
    SANITY_CHECK_RETURN_ERROR(!p_FmPcd->p_FmPcdDriverParam, E_INVALID_STATE);

    if (p_FmPcd->guestId != NCSW_MASTER_ID)
        RETURN_ERROR(MAJOR, E_NOT_SUPPORTED, ("FM_PCD_ForceIntr - guest mode!"));

    switch (exception)
    {
        case (e_FM_PCD_KG_EXCEPTION_DOUBLE_ECC):
        case (e_FM_PCD_KG_EXCEPTION_KEYSIZE_OVERFLOW):
            if (!p_FmPcd->p_FmPcdKg)
                RETURN_ERROR(MINOR, E_INVALID_STATE, ("Can't ask for this interrupt - keygen is not working"));
            break;
        case (e_FM_PCD_PLCR_EXCEPTION_DOUBLE_ECC):
        case (e_FM_PCD_PLCR_EXCEPTION_INIT_ENTRY_ERROR):
        case (e_FM_PCD_PLCR_EXCEPTION_PRAM_SELF_INIT_COMPLETE):
        case (e_FM_PCD_PLCR_EXCEPTION_ATOMIC_ACTION_COMPLETE):
            if (!p_FmPcd->p_FmPcdPlcr)
                RETURN_ERROR(MINOR, E_INVALID_STATE, ("Can't ask for this interrupt - policer is not working"));
            break;
        case (e_FM_PCD_PRS_EXCEPTION_DOUBLE_ECC):
        case (e_FM_PCD_PRS_EXCEPTION_SINGLE_ECC):
           if (!p_FmPcd->p_FmPcdPrs)
                RETURN_ERROR(MINOR, E_INVALID_STATE, ("Can't ask for this interrupt -parsrer is not working"));
            break;
        default:
            RETURN_ERROR(MAJOR, E_INVALID_STATE, ("Invalid interrupt requested"));
    }
    switch (exception)
    {
        case e_FM_PCD_PRS_EXCEPTION_DOUBLE_ECC:
            if (!(p_FmPcd->exceptions & FM_PCD_EX_PRS_DOUBLE_ECC))
                RETURN_ERROR(MINOR, E_NOT_SUPPORTED, ("The selected exception is masked"));
            break;
        case e_FM_PCD_PRS_EXCEPTION_SINGLE_ECC:
            if (!(p_FmPcd->exceptions & FM_PCD_EX_PRS_SINGLE_ECC))
                RETURN_ERROR(MINOR, E_NOT_SUPPORTED, ("The selected exception is masked"));
            break;
        case e_FM_PCD_KG_EXCEPTION_DOUBLE_ECC:
            if (!(p_FmPcd->exceptions & FM_EX_KG_DOUBLE_ECC))
                RETURN_ERROR(MINOR, E_NOT_SUPPORTED, ("The selected exception is masked"));
            WRITE_UINT32(p_FmPcd->p_FmPcdKg->p_FmPcdKgRegs->fmkg_feer, FM_EX_KG_DOUBLE_ECC);
            break;
        case e_FM_PCD_KG_EXCEPTION_KEYSIZE_OVERFLOW:
            if (!(p_FmPcd->exceptions & FM_EX_KG_KEYSIZE_OVERFLOW))
                RETURN_ERROR(MINOR, E_NOT_SUPPORTED, ("The selected exception is masked"));
            WRITE_UINT32(p_FmPcd->p_FmPcdKg->p_FmPcdKgRegs->fmkg_feer, FM_EX_KG_KEYSIZE_OVERFLOW);
            break;
        case e_FM_PCD_PLCR_EXCEPTION_DOUBLE_ECC:
            if (!(p_FmPcd->exceptions & FM_PCD_EX_PLCR_DOUBLE_ECC))
                RETURN_ERROR(MINOR, E_NOT_SUPPORTED, ("The selected exception is masked"));
            WRITE_UINT32(p_FmPcd->p_FmPcdPlcr->p_FmPcdPlcrRegs->fmpl_eifr, FM_PCD_PLCR_DOUBLE_ECC);
            break;
        case e_FM_PCD_PLCR_EXCEPTION_INIT_ENTRY_ERROR:
            if (!(p_FmPcd->exceptions & FM_PCD_EX_PLCR_INIT_ENTRY_ERROR))
                RETURN_ERROR(MINOR, E_NOT_SUPPORTED, ("The selected exception is masked"));
            WRITE_UINT32(p_FmPcd->p_FmPcdPlcr->p_FmPcdPlcrRegs->fmpl_eifr, FM_PCD_PLCR_INIT_ENTRY_ERROR);
            break;
        case e_FM_PCD_PLCR_EXCEPTION_PRAM_SELF_INIT_COMPLETE:
            if (!(p_FmPcd->exceptions & FM_PCD_EX_PLCR_PRAM_SELF_INIT_COMPLETE))
                RETURN_ERROR(MINOR, E_NOT_SUPPORTED, ("The selected exception is masked"));
            WRITE_UINT32(p_FmPcd->p_FmPcdPlcr->p_FmPcdPlcrRegs->fmpl_ifr, FM_PCD_PLCR_PRAM_SELF_INIT_COMPLETE);
            break;
        case e_FM_PCD_PLCR_EXCEPTION_ATOMIC_ACTION_COMPLETE:
            if (!(p_FmPcd->exceptions & FM_PCD_EX_PLCR_ATOMIC_ACTION_COMPLETE))
                RETURN_ERROR(MINOR, E_NOT_SUPPORTED, ("The selected exception is masked"));
            WRITE_UINT32(p_FmPcd->p_FmPcdPlcr->p_FmPcdPlcrRegs->fmpl_ifr, FM_PCD_PLCR_ATOMIC_ACTION_COMPLETE);
            break;
    }

    return E_OK;
}