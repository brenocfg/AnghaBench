#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_13__ {TYPE_4__* qmi_regs; TYPE_3__* bmi_regs; } ;
struct TYPE_14__ {int requiredAction; int origNonRxQmiRegsPndn; scalar_t__ portType; int savedBmiNia; int /*<<< orphan*/  orFmanCtrl; int /*<<< orphan*/  hardwarePortId; int /*<<< orphan*/  h_Fm; TYPE_5__ port; int /*<<< orphan*/  h_FmPcd; } ;
typedef  TYPE_6__ t_FmPort ;
typedef  scalar_t__ t_Error ;
struct TYPE_12__ {int /*<<< orphan*/  volatile fmqm_pnen; int /*<<< orphan*/  volatile fmqm_pndn; } ;
struct TYPE_10__ {int /*<<< orphan*/  volatile fmbm_rfene; int /*<<< orphan*/  fmbm_rfne; } ;
struct TYPE_9__ {int /*<<< orphan*/  volatile fmbm_ofene; int /*<<< orphan*/  fmbm_ofne; } ;
struct TYPE_11__ {TYPE_2__ rx; TYPE_1__ oh; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_6__*) ; 
 int BMI_RFNE_FDCS_MASK ; 
 int /*<<< orphan*/  E_INVALID_STATE ; 
 scalar_t__ E_OK ; 
 scalar_t__ FmPcdGetHcHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FmPcdHcSync (int /*<<< orphan*/ ) ; 
 scalar_t__ FmSetNumOfRiscsPerPort (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int GET_NO_PCD_NIA_BMI_AC_ENQ_FRAME () ; 
 int /*<<< orphan*/  MAJOR ; 
 int NIA_BMI_AC_RELEASE ; 
 int NIA_ENG_BMI ; 
 int NIA_ENG_QMI_ENQ ; 
 int NIA_ORDER_RESTOR ; 
 int /*<<< orphan*/  NO_MSG ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int UPDATE_FMFP_PRC_WITH_ONE_RISC_ONLY ; 
 int UPDATE_NIA_FENE ; 
 int UPDATE_NIA_PNDN ; 
 int UPDATE_NIA_PNEN ; 
 int /*<<< orphan*/  WRITE_UINT32 (int /*<<< orphan*/  volatile,int) ; 
 scalar_t__ e_FM_PORT_TYPE_OH_OFFLINE_PARSING ; 

__attribute__((used)) static t_Error DetachPCD(t_FmPort *p_FmPort)
{
    volatile uint32_t *p_BmiNia = NULL;

    ASSERT_COND(p_FmPort);

    /* get PCD registers pointers */
    if (p_FmPort->requiredAction & UPDATE_NIA_PNDN)
        WRITE_UINT32(p_FmPort->port.qmi_regs->fmqm_pndn,
                     p_FmPort->origNonRxQmiRegsPndn);

    if (p_FmPort->portType == e_FM_PORT_TYPE_OH_OFFLINE_PARSING)
        p_BmiNia = &p_FmPort->port.bmi_regs->oh.fmbm_ofne;
    else
        p_BmiNia = &p_FmPort->port.bmi_regs->rx.fmbm_rfne;

    WRITE_UINT32(
            *p_BmiNia,
            (p_FmPort->savedBmiNia & BMI_RFNE_FDCS_MASK) | GET_NO_PCD_NIA_BMI_AC_ENQ_FRAME());

    if (FmPcdGetHcHandle(p_FmPort->h_FmPcd))
        FmPcdHcSync(p_FmPort->h_FmPcd);

    if (p_FmPort->requiredAction & UPDATE_NIA_FENE)
    {
        if (p_FmPort->portType == e_FM_PORT_TYPE_OH_OFFLINE_PARSING)
            WRITE_UINT32(p_FmPort->port.bmi_regs->oh.fmbm_ofene,
                         NIA_ENG_QMI_ENQ | NIA_ORDER_RESTOR);
        else
            WRITE_UINT32(p_FmPort->port.bmi_regs->rx.fmbm_rfene,
                         NIA_ENG_QMI_ENQ | NIA_ORDER_RESTOR);
    }

    if (p_FmPort->requiredAction & UPDATE_NIA_PNEN)
        WRITE_UINT32(p_FmPort->port.qmi_regs->fmqm_pnen,
                     NIA_ENG_BMI | NIA_BMI_AC_RELEASE);

    if (p_FmPort->requiredAction & UPDATE_FMFP_PRC_WITH_ONE_RISC_ONLY)
        if (FmSetNumOfRiscsPerPort(p_FmPort->h_Fm, p_FmPort->hardwarePortId, 2,
                                   p_FmPort->orFmanCtrl) != E_OK)
            RETURN_ERROR(MAJOR, E_INVALID_STATE, NO_MSG);

    p_FmPort->requiredAction = 0;

    return E_OK;
}