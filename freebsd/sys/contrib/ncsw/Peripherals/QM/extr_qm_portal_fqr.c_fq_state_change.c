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
typedef  int uint8_t ;
struct qman_fq {int flags; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int fqs; } ;
struct qm_mr_entry {TYPE_1__ fq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int /*<<< orphan*/  FQLOCK (struct qman_fq*) ; 
 int /*<<< orphan*/  FQUNLOCK (struct qman_fq*) ; 
 int QMAN_FQ_STATE_CHANGING ; 
 int QMAN_FQ_STATE_NE ; 
 int QMAN_FQ_STATE_ORL ; 
 int QM_MR_FQS_NOTEMPTY ; 
 int QM_MR_FQS_ORLPRESENT ; 
#define  QM_MR_VERB_FQPN 130 
#define  QM_MR_VERB_FQRL 129 
#define  QM_MR_VERB_FQRN 128 
 int /*<<< orphan*/  qman_fq_state_parked ; 
 int /*<<< orphan*/  qman_fq_state_retired ; 
 int /*<<< orphan*/  qman_fq_state_sched ; 

__attribute__((used)) static __inline__ void fq_state_change(struct qman_fq *p_Fq,
                                       struct qm_mr_entry *p_Msg,
                                       uint8_t verb)
{
    FQLOCK(p_Fq);
    switch(verb) {
        case QM_MR_VERB_FQRL:
            ASSERT_COND(p_Fq->flags & QMAN_FQ_STATE_ORL);
            p_Fq->flags &= ~QMAN_FQ_STATE_ORL;
            break;
        case QM_MR_VERB_FQRN:
            ASSERT_COND((p_Fq->state == qman_fq_state_parked) ||
                (p_Fq->state == qman_fq_state_sched));
            ASSERT_COND(p_Fq->flags & QMAN_FQ_STATE_CHANGING);
            p_Fq->flags &= ~QMAN_FQ_STATE_CHANGING;
            if (p_Msg->fq.fqs & QM_MR_FQS_NOTEMPTY)
                p_Fq->flags |= QMAN_FQ_STATE_NE;
            if (p_Msg->fq.fqs & QM_MR_FQS_ORLPRESENT)
                p_Fq->flags |= QMAN_FQ_STATE_ORL;
            p_Fq->state = qman_fq_state_retired;
            break;
        case QM_MR_VERB_FQPN:
            ASSERT_COND(p_Fq->state == qman_fq_state_sched);
            ASSERT_COND(p_Fq->flags & QMAN_FQ_STATE_CHANGING);
            p_Fq->state = qman_fq_state_parked;
    }
    FQUNLOCK(p_Fq);
}