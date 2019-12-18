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
typedef  int uint32_t ;
struct qman_fq {int state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int FALSE ; 
 int QMAN_FQ_DESTROY_PARKED ; 
 int /*<<< orphan*/  UNUSED (int) ; 
#define  qman_fq_state_oos 129 
#define  qman_fq_state_parked 128 

__attribute__((used)) static void qman_destroy_fq(struct qman_fq *p_Fq, uint32_t flags)
{
    /* We don't need to lock the FQ as it is a pre-condition that the FQ be
     * quiesced. Instead, run some checks. */
    UNUSED(flags);
    switch (p_Fq->state) {
    case qman_fq_state_parked:
        ASSERT_COND(flags & QMAN_FQ_DESTROY_PARKED);
    case qman_fq_state_oos:
        return;
    default:
        break;
    }
    ASSERT_COND(FALSE);
}