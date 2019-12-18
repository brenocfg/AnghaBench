#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int options; TYPE_4__* p_LowQmPortal; } ;
typedef  TYPE_2__ t_QmPortal ;
struct TYPE_10__ {int /*<<< orphan*/  irq; } ;
struct TYPE_12__ {TYPE_1__ config; } ;

/* Variables and functions */
 int QMAN_PORTAL_FLAG_IRQ ; 
 int /*<<< orphan*/  XX_DisableIntr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XX_FreeIntr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qmPortalEqcrCceUpdate (TYPE_4__*) ; 
 int /*<<< orphan*/  qm_dqrr_finish (TYPE_4__*) ; 
 int /*<<< orphan*/  qm_eqcr_finish (TYPE_4__*) ; 
 int /*<<< orphan*/  qm_isr_finish (TYPE_4__*) ; 
 int /*<<< orphan*/  qm_mc_finish (TYPE_4__*) ; 
 int /*<<< orphan*/  qm_mr_finish (TYPE_4__*) ; 

__attribute__((used)) static void qman_destroy_portal(t_QmPortal *p_QmPortal)
{
    /* NB we do this to "quiesce" EQCR. If we add enqueue-completions or
     * something related to QM_PIRQ_EQCI, this may need fixing. */
    qmPortalEqcrCceUpdate(p_QmPortal->p_LowQmPortal);
    if (p_QmPortal->options & QMAN_PORTAL_FLAG_IRQ)
    {
        XX_DisableIntr(p_QmPortal->p_LowQmPortal->config.irq);
        XX_FreeIntr(p_QmPortal->p_LowQmPortal->config.irq);
    }
    qm_isr_finish(p_QmPortal->p_LowQmPortal);
    qm_mc_finish(p_QmPortal->p_LowQmPortal);
    qm_mr_finish(p_QmPortal->p_LowQmPortal);
    qm_dqrr_finish(p_QmPortal->p_LowQmPortal);
    qm_eqcr_finish(p_QmPortal->p_LowQmPortal);
}