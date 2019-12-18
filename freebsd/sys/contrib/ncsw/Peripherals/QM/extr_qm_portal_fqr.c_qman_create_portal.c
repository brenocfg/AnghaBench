#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_25__ {int options; TYPE_3__* p_LowQmPortal; } ;
typedef  TYPE_1__ t_QmPortal ;
typedef  int /*<<< orphan*/  t_Error ;
struct qm_portal_config {int /*<<< orphan*/  irq; } ;
struct TYPE_26__ {struct qm_portal_config config; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_portalExceptions ; 
 int /*<<< orphan*/  ERROR_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_INVALID_STATE ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  MINOR ; 
 int QMAN_PORTAL_FLAG_DCA ; 
 int QMAN_PORTAL_FLAG_DSTASH ; 
 int QMAN_PORTAL_FLAG_IRQ ; 
 int QMAN_PORTAL_FLAG_RSTASH ; 
 int QMAN_PORTAL_FLAG_WAIT ; 
 int QM_PIRQ_DQRI ; 
 int QM_PIRQ_EQCI ; 
 int QM_PIRQ_MRI ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  XX_EnableIntr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XX_SetIntr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  e_QmPortalDequeuePullMode ; 
 int /*<<< orphan*/  e_QmPortalDequeuePushMode ; 
 int /*<<< orphan*/  e_QmPortalDqrrCCI ; 
 int /*<<< orphan*/  e_QmPortalDqrrDCA ; 
 int /*<<< orphan*/  e_QmPortalEqcrCCE ; 
 int /*<<< orphan*/  e_QmPortalMrCCI ; 
 int /*<<< orphan*/  e_QmPortalPVB ; 
 int /*<<< orphan*/  portal_isr ; 
 int /*<<< orphan*/ * qm_dqrr_current (TYPE_3__*) ; 
 int /*<<< orphan*/  qm_dqrr_finish (TYPE_3__*) ; 
 scalar_t__ qm_dqrr_init (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  qm_dqrr_sdqcr_set (TYPE_3__*,int) ; 
 int /*<<< orphan*/  qm_dqrr_set_ithresh (TYPE_3__*,int) ; 
 int /*<<< orphan*/  qm_eqcr_finish (TYPE_3__*) ; 
 int qm_eqcr_get_fill (TYPE_3__*) ; 
 int /*<<< orphan*/  qm_eqcr_init (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_isr_disable_write (TYPE_3__*,int) ; 
 int /*<<< orphan*/  qm_isr_enable_write (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_isr_finish (TYPE_3__*) ; 
 scalar_t__ qm_isr_init (TYPE_3__*) ; 
 int /*<<< orphan*/  qm_isr_set_iperiod (TYPE_3__*,int) ; 
 int /*<<< orphan*/  qm_isr_status_clear (TYPE_3__*,int) ; 
 int /*<<< orphan*/  qm_isr_uninhibit (TYPE_3__*) ; 
 int /*<<< orphan*/  qm_mc_finish (TYPE_3__*) ; 
 scalar_t__ qm_mc_init (TYPE_3__*) ; 
 int /*<<< orphan*/ * qm_mr_current (TYPE_3__*) ; 
 int /*<<< orphan*/  qm_mr_finish (TYPE_3__*) ; 
 scalar_t__ qm_mr_init (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_mr_set_ithresh (TYPE_3__*,int) ; 

__attribute__((used)) static t_Error qman_create_portal(t_QmPortal *p_QmPortal,
                                   uint32_t flags,
                                   uint32_t sdqcrFlags,
                                   uint8_t  dqrrSize)
{
    const struct qm_portal_config   *p_Config = &(p_QmPortal->p_LowQmPortal->config);
    int                             ret = 0;
    t_Error                         err;
    uint32_t                        isdr;

    if ((err = qm_eqcr_init(p_QmPortal->p_LowQmPortal, e_QmPortalPVB, e_QmPortalEqcrCCE)) != E_OK)
        RETURN_ERROR(MINOR, err, ("Qman EQCR initialization failed\n"));

    if (qm_dqrr_init(p_QmPortal->p_LowQmPortal,
                     sdqcrFlags ? e_QmPortalDequeuePushMode : e_QmPortalDequeuePullMode,
                     e_QmPortalPVB,
                     (flags & QMAN_PORTAL_FLAG_DCA) ? e_QmPortalDqrrDCA : e_QmPortalDqrrCCI,
                     dqrrSize,
                     (flags & QMAN_PORTAL_FLAG_RSTASH) ? 1 : 0,
                     (flags & QMAN_PORTAL_FLAG_DSTASH) ? 1 : 0)) {
        REPORT_ERROR(MAJOR, E_INVALID_STATE, ("DQRR initialization failed"));
        goto fail_dqrr;
    }

    if (qm_mr_init(p_QmPortal->p_LowQmPortal, e_QmPortalPVB, e_QmPortalMrCCI)) {
        REPORT_ERROR(MAJOR, E_INVALID_STATE, ("MR initialization failed"));
        goto fail_mr;
    }
    if (qm_mc_init(p_QmPortal->p_LowQmPortal)) {
        REPORT_ERROR(MAJOR, E_INVALID_STATE, ("MC initialization failed"));
        goto fail_mc;
    }
    if (qm_isr_init(p_QmPortal->p_LowQmPortal)) {
        REPORT_ERROR(MAJOR, E_INVALID_STATE, ("ISR initialization failed"));
        goto fail_isr;
    }
    /* static interrupt-gating controls */
    qm_dqrr_set_ithresh(p_QmPortal->p_LowQmPortal, 12);
    qm_mr_set_ithresh(p_QmPortal->p_LowQmPortal, 4);
    qm_isr_set_iperiod(p_QmPortal->p_LowQmPortal, 100);
    p_QmPortal->options = flags;
    isdr = 0xffffffff;
    qm_isr_status_clear(p_QmPortal->p_LowQmPortal, 0xffffffff);
    qm_isr_enable_write(p_QmPortal->p_LowQmPortal, DEFAULT_portalExceptions);
    qm_isr_disable_write(p_QmPortal->p_LowQmPortal, isdr);
    if (flags & QMAN_PORTAL_FLAG_IRQ)
    {
        XX_SetIntr(p_Config->irq, portal_isr, p_QmPortal);
        XX_EnableIntr(p_Config->irq);
        qm_isr_uninhibit(p_QmPortal->p_LowQmPortal);
    } else
        /* without IRQ, we can't block */
        flags &= ~QMAN_PORTAL_FLAG_WAIT;
    /* Need EQCR to be empty before continuing */
    isdr ^= QM_PIRQ_EQCI;
    qm_isr_disable_write(p_QmPortal->p_LowQmPortal, isdr);
    ret = qm_eqcr_get_fill(p_QmPortal->p_LowQmPortal);
    if (ret) {
        REPORT_ERROR(MAJOR, E_INVALID_STATE, ("EQCR unclean"));
        goto fail_eqcr_empty;
    }
    isdr ^= (QM_PIRQ_DQRI | QM_PIRQ_MRI);
    qm_isr_disable_write(p_QmPortal->p_LowQmPortal, isdr);
    if (qm_dqrr_current(p_QmPortal->p_LowQmPortal) != NULL)
    {
        REPORT_ERROR(MAJOR, E_INVALID_STATE, ("DQRR unclean"));
goto fail_dqrr_mr_empty;
    }
    if (qm_mr_current(p_QmPortal->p_LowQmPortal) != NULL)
    {
        REPORT_ERROR(MAJOR, E_INVALID_STATE, ("MR unclean"));
goto fail_dqrr_mr_empty;
    }
    qm_isr_disable_write(p_QmPortal->p_LowQmPortal, 0);
    qm_dqrr_sdqcr_set(p_QmPortal->p_LowQmPortal, sdqcrFlags);
    return E_OK;
fail_dqrr_mr_empty:
fail_eqcr_empty:
    qm_isr_finish(p_QmPortal->p_LowQmPortal);
fail_isr:
    qm_mc_finish(p_QmPortal->p_LowQmPortal);
fail_mc:
    qm_mr_finish(p_QmPortal->p_LowQmPortal);
fail_mr:
    qm_dqrr_finish(p_QmPortal->p_LowQmPortal);
fail_dqrr:
    qm_eqcr_finish(p_QmPortal->p_LowQmPortal);
    return ERROR_CODE(E_INVALID_STATE);
}