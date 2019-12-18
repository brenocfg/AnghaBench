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
struct TYPE_3__ {int /*<<< orphan*/  h_App; int /*<<< orphan*/  (* f_Exception ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;struct fman_qmi_regs* p_FmQmiRegs; } ;
typedef  TYPE_1__ t_Fm ;
struct fman_qmi_regs {int dummy; } ;

/* Variables and functions */
 int QMI_INTR_EN_SINGLE_ECC ; 
 int /*<<< orphan*/  e_FM_EX_QMI_SINGLE_ECC ; 
 int fman_get_qmi_event (struct fman_qmi_regs*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void QmiEvent(t_Fm *p_Fm)
{
    uint32_t    event;
    struct fman_qmi_regs *qmi_rg = p_Fm->p_FmQmiRegs;

    event = fman_get_qmi_event(qmi_rg);

    if (event & QMI_INTR_EN_SINGLE_ECC)
        p_Fm->f_Exception(p_Fm->h_App,e_FM_EX_QMI_SINGLE_ECC);
}