#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_9__ {int options; int /*<<< orphan*/  (* f_LoopDequeueRingCB ) (TYPE_2__*) ;TYPE_4__* p_LowQmPortal; } ;
typedef  TYPE_2__ t_QmPortal ;
struct TYPE_8__ {int /*<<< orphan*/  cpu; } ;
struct TYPE_10__ {TYPE_1__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LoopMessageRing (TYPE_2__*,int) ; 
 int QMAN_PORTAL_FLAG_IRQ_FAST ; 
 int QMAN_PORTAL_FLAG_IRQ_SLOW ; 
 int /*<<< orphan*/  TRACE ; 
 int qm_isr_enable_read (TYPE_4__*) ; 
 int /*<<< orphan*/  qm_isr_status_clear (TYPE_4__*,int) ; 
 int qm_isr_status_read (TYPE_4__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void portal_isr(void *ptr)
{
    t_QmPortal  *p_QmPortal = ptr;
    uint32_t    event = 0;
    uint32_t    enableEvents = qm_isr_enable_read(p_QmPortal->p_LowQmPortal);

    DBG(TRACE, ("software-portal %d got interrupt", p_QmPortal->p_LowQmPortal->config.cpu));

    event |= (qm_isr_status_read(p_QmPortal->p_LowQmPortal) &
            enableEvents);

    qm_isr_status_clear(p_QmPortal->p_LowQmPortal, event);
    /* Only do fast-path handling if it's required */
    if (/*(event & QM_PIRQ_DQRI) &&*/
        (p_QmPortal->options & QMAN_PORTAL_FLAG_IRQ_FAST))
        p_QmPortal->f_LoopDequeueRingCB(p_QmPortal);
    if (p_QmPortal->options & QMAN_PORTAL_FLAG_IRQ_SLOW)
        LoopMessageRing(p_QmPortal, event);
}