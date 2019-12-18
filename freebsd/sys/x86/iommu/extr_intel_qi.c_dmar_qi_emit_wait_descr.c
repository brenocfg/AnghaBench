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
typedef  int /*<<< orphan*/  uint32_t ;
struct dmar_unit {int /*<<< orphan*/  inv_waitd_seq_hw_phys; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAR_ASSERT_LOCKED (struct dmar_unit*) ; 
 int DMAR_IQ_DESCR_WAIT_FN ; 
 int DMAR_IQ_DESCR_WAIT_ID ; 
 int DMAR_IQ_DESCR_WAIT_IF ; 
 int DMAR_IQ_DESCR_WAIT_SD (int /*<<< orphan*/ ) ; 
 int DMAR_IQ_DESCR_WAIT_SW ; 
 int /*<<< orphan*/  dmar_qi_emit (struct dmar_unit*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dmar_qi_emit_wait_descr(struct dmar_unit *unit, uint32_t seq, bool intr,
    bool memw, bool fence)
{

	DMAR_ASSERT_LOCKED(unit);
	dmar_qi_emit(unit, DMAR_IQ_DESCR_WAIT_ID |
	    (intr ? DMAR_IQ_DESCR_WAIT_IF : 0) |
	    (memw ? DMAR_IQ_DESCR_WAIT_SW : 0) |
	    (fence ? DMAR_IQ_DESCR_WAIT_FN : 0) |
	    (memw ? DMAR_IQ_DESCR_WAIT_SD(seq) : 0),
	    memw ? unit->inv_waitd_seq_hw_phys : 0);
}