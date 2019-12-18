#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct qman_fq {int flags; int /*<<< orphan*/  h_QmPortal; scalar_t__ h_QmFqr; } ;
typedef  struct qman_fq t_QmFqr ;
typedef  scalar_t__ t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (struct qman_fq*) ; 
 int /*<<< orphan*/  E_INVALID_STATE ; 
 scalar_t__ E_OK ; 
 int /*<<< orphan*/  MAJOR ; 
 int QMAN_FQ_STATE_NE ; 
 int QM_VDQCR_NUMFRAMES_TILLEMPTY ; 
 int QM_VDQCR_PRECEDENCE_VDQCR ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ freeDrainedFq (struct qman_fq*) ; 
 scalar_t__ qman_volatile_dequeue (int /*<<< orphan*/ ,struct qman_fq*,int) ; 

__attribute__((used)) static t_Error drainRetiredFq(struct qman_fq *p_Fq)
{
    t_QmFqr     *p_QmFqr;

    ASSERT_COND(p_Fq);
    p_QmFqr = (t_QmFqr *)p_Fq->h_QmFqr;
    ASSERT_COND(p_QmFqr);

    if (p_Fq->flags & QMAN_FQ_STATE_NE)
    {
        if (qman_volatile_dequeue(p_QmFqr->h_QmPortal, p_Fq,
                                (QM_VDQCR_PRECEDENCE_VDQCR | QM_VDQCR_NUMFRAMES_TILLEMPTY)) != E_OK)

            RETURN_ERROR(MAJOR, E_INVALID_STATE, ("drain with volatile failed"));
        return E_OK;
    }
    else
        return freeDrainedFq(p_Fq);
}