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
struct dmar_unit {int inv_waitd_seq; int /*<<< orphan*/  inv_waitd_gen; } ;
struct dmar_qi_genseq {int seq; int /*<<< orphan*/  gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAR_ASSERT_LOCKED (struct dmar_unit*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cpu_spinwait () ; 
 int /*<<< orphan*/  dmar_qi_advance_tail (struct dmar_unit*) ; 
 int /*<<< orphan*/  dmar_qi_emit_wait_descr (struct dmar_unit*,int,int,int,int) ; 
 int /*<<< orphan*/  dmar_qi_ensure (struct dmar_unit*,int) ; 
 int /*<<< orphan*/  dmar_qi_seq_processed (struct dmar_unit*,struct dmar_qi_genseq*) ; 

__attribute__((used)) static void
dmar_qi_emit_wait_seq(struct dmar_unit *unit, struct dmar_qi_genseq *pseq,
    bool emit_wait)
{
	struct dmar_qi_genseq gsec;
	uint32_t seq;

	KASSERT(pseq != NULL, ("wait descriptor with no place for seq"));
	DMAR_ASSERT_LOCKED(unit);
	if (unit->inv_waitd_seq == 0xffffffff) {
		gsec.gen = unit->inv_waitd_gen;
		gsec.seq = unit->inv_waitd_seq;
		dmar_qi_ensure(unit, 1);
		dmar_qi_emit_wait_descr(unit, gsec.seq, false, true, false);
		dmar_qi_advance_tail(unit);
		while (!dmar_qi_seq_processed(unit, &gsec))
			cpu_spinwait();
		unit->inv_waitd_gen++;
		unit->inv_waitd_seq = 1;
	}
	seq = unit->inv_waitd_seq++;
	pseq->gen = unit->inv_waitd_gen;
	pseq->seq = seq;
	if (emit_wait) {
		dmar_qi_ensure(unit, 1);
		dmar_qi_emit_wait_descr(unit, seq, true, true, false);
	}
}