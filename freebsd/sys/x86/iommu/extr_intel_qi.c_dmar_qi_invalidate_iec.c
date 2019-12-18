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
typedef  scalar_t__ u_int ;
struct dmar_unit {scalar_t__ irte_cnt; } ;
struct dmar_qi_genseq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAR_ASSERT_LOCKED (struct dmar_unit*) ; 
 int DMAR_IQ_DESCR_IEC_IDX ; 
 int DMAR_IQ_DESCR_IEC_IIDX (scalar_t__) ; 
 int DMAR_IQ_DESCR_IEC_IM (scalar_t__) ; 
 int DMAR_IQ_DESCR_IEC_INV ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  dmar_qi_advance_tail (struct dmar_unit*) ; 
 int /*<<< orphan*/  dmar_qi_emit (struct dmar_unit*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmar_qi_emit_wait_seq (struct dmar_unit*,struct dmar_qi_genseq*,int) ; 
 int /*<<< orphan*/  dmar_qi_ensure (struct dmar_unit*,int) ; 
 int /*<<< orphan*/  dmar_qi_wait_for_seq (struct dmar_unit*,struct dmar_qi_genseq*,int) ; 
 scalar_t__ ffs (scalar_t__) ; 

void
dmar_qi_invalidate_iec(struct dmar_unit *unit, u_int start, u_int cnt)
{
	struct dmar_qi_genseq gseq;
	u_int c, l;

	DMAR_ASSERT_LOCKED(unit);
	KASSERT(start < unit->irte_cnt && start < start + cnt &&
	    start + cnt <= unit->irte_cnt,
	    ("inv iec overflow %d %d %d", unit->irte_cnt, start, cnt));
	for (; cnt > 0; cnt -= c, start += c) {
		l = ffs(start | cnt) - 1;
		c = 1 << l;
		dmar_qi_ensure(unit, 1);
		dmar_qi_emit(unit, DMAR_IQ_DESCR_IEC_INV |
		    DMAR_IQ_DESCR_IEC_IDX | DMAR_IQ_DESCR_IEC_IIDX(start) |
		    DMAR_IQ_DESCR_IEC_IM(l), 0);
	}
	dmar_qi_ensure(unit, 1);
	dmar_qi_emit_wait_seq(unit, &gseq, true);
	dmar_qi_advance_tail(unit);

	/*
	 * The caller of the function, in particular,
	 * dmar_ir_program_irte(), may be called from the context
	 * where the sleeping is forbidden (in fact, the
	 * intr_table_lock mutex may be held, locked from
	 * intr_shuffle_irqs()).  Wait for the invalidation completion
	 * using the busy wait.
	 *
	 * The impact on the interrupt input setup code is small, the
	 * expected overhead is comparable with the chipset register
	 * read.  It is more harmful for the parallel DMA operations,
	 * since we own the dmar unit lock until whole invalidation
	 * queue is processed, which includes requests possibly issued
	 * before our request.
	 */
	dmar_qi_wait_for_seq(unit, &gseq, true);
}