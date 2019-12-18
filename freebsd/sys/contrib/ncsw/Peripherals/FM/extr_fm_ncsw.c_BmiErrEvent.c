#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  h_App; int /*<<< orphan*/  (* f_Exception ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;struct fman_bmi_regs* p_FmBmiRegs; } ;
typedef  TYPE_1__ t_Fm ;
struct fman_bmi_regs {int dummy; } ;

/* Variables and functions */
 int BMI_ERR_INTR_EN_DISPATCH_RAM_ECC ; 
 int BMI_ERR_INTR_EN_LIST_RAM_ECC ; 
 int BMI_ERR_INTR_EN_STATISTICS_RAM_ECC ; 
 int BMI_ERR_INTR_EN_STORAGE_PROFILE_ECC ; 
 int /*<<< orphan*/  e_FM_EX_BMI_DISPATCH_RAM_ECC ; 
 int /*<<< orphan*/  e_FM_EX_BMI_LIST_RAM_ECC ; 
 int /*<<< orphan*/  e_FM_EX_BMI_STATISTICS_RAM_ECC ; 
 int /*<<< orphan*/  e_FM_EX_BMI_STORAGE_PROFILE_ECC ; 
 int fman_get_bmi_err_event (struct fman_bmi_regs*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void BmiErrEvent(t_Fm *p_Fm)
{
    uint32_t    event;
    struct fman_bmi_regs *bmi_rg = p_Fm->p_FmBmiRegs;


    event = fman_get_bmi_err_event(bmi_rg);

    if (event & BMI_ERR_INTR_EN_STORAGE_PROFILE_ECC)
        p_Fm->f_Exception(p_Fm->h_App,e_FM_EX_BMI_STORAGE_PROFILE_ECC);
    if (event & BMI_ERR_INTR_EN_LIST_RAM_ECC)
        p_Fm->f_Exception(p_Fm->h_App,e_FM_EX_BMI_LIST_RAM_ECC);
    if (event & BMI_ERR_INTR_EN_STATISTICS_RAM_ECC)
        p_Fm->f_Exception(p_Fm->h_App,e_FM_EX_BMI_STATISTICS_RAM_ECC);
    if (event & BMI_ERR_INTR_EN_DISPATCH_RAM_ECC)
        p_Fm->f_Exception(p_Fm->h_App,e_FM_EX_BMI_DISPATCH_RAM_ECC);
}