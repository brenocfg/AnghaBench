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
typedef  int u64 ;
struct mm_struct {int /*<<< orphan*/  pgd; } ;
struct TYPE_2__ {int /*<<< orphan*/  asid_cache; } ;

/* Variables and functions */
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLBMISS_HANDLER_SETUP_PGD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  asid_versions_eq (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  boot_cpu_data ; 
 int /*<<< orphan*/  check_mmu_context (struct mm_struct*) ; 
 int /*<<< orphan*/  cmpxchg_relaxed (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  cpu_asid (unsigned int,struct mm_struct*) ; 
 int cpu_asid_mask (int /*<<< orphan*/ *) ; 
 int cpu_context (unsigned int,struct mm_struct*) ; 
 TYPE_1__* cpu_data ; 
 int /*<<< orphan*/  cpu_has_mmid ; 
 scalar_t__ cpu_has_shared_ftlb_entries ; 
 scalar_t__ cpu_has_vtag_icache ; 
 int /*<<< orphan*/  cpu_mmid_lock ; 
 int /*<<< orphan*/ * cpu_sibling_map ; 
 int /*<<< orphan*/  cpumask_clear_cpu (unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ cpumask_intersects (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ cpumask_test_cpu (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_icache_all () ; 
 int get_new_mmid (struct mm_struct*) ; 
 int /*<<< orphan*/  ginvt_mmid () ; 
 int /*<<< orphan*/  local_flush_tlb_all () ; 
 int /*<<< orphan*/  mmid_version ; 
 int /*<<< orphan*/  mtc0_tlbw_hazard () ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned int smp_processor_id () ; 
 int /*<<< orphan*/  sync_ginv () ; 
 int /*<<< orphan*/  tlb_flush_pending ; 
 int /*<<< orphan*/  write_c0_entryhi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_memorymapid (int) ; 

void check_switch_mmu_context(struct mm_struct *mm)
{
	unsigned int cpu = smp_processor_id();
	u64 ctx, old_active_mmid;
	unsigned long flags;

	if (!cpu_has_mmid) {
		check_mmu_context(mm);
		write_c0_entryhi(cpu_asid(cpu, mm));
		goto setup_pgd;
	}

	/*
	 * MMID switch fast-path, to avoid acquiring cpu_mmid_lock when it's
	 * unnecessary.
	 *
	 * The memory ordering here is subtle. If our active_mmids is non-zero
	 * and the MMID matches the current version, then we update the CPU's
	 * asid_cache with a relaxed cmpxchg. Racing with a concurrent rollover
	 * means that either:
	 *
	 * - We get a zero back from the cmpxchg and end up waiting on
	 *   cpu_mmid_lock in check_mmu_context(). Taking the lock synchronises
	 *   with the rollover and so we are forced to see the updated
	 *   generation.
	 *
	 * - We get a valid MMID back from the cmpxchg, which means the
	 *   relaxed xchg in flush_context will treat us as reserved
	 *   because atomic RmWs are totally ordered for a given location.
	 */
	ctx = cpu_context(cpu, mm);
	old_active_mmid = READ_ONCE(cpu_data[cpu].asid_cache);
	if (!old_active_mmid ||
	    !asid_versions_eq(cpu, ctx, atomic64_read(&mmid_version)) ||
	    !cmpxchg_relaxed(&cpu_data[cpu].asid_cache, old_active_mmid, ctx)) {
		raw_spin_lock_irqsave(&cpu_mmid_lock, flags);

		ctx = cpu_context(cpu, mm);
		if (!asid_versions_eq(cpu, ctx, atomic64_read(&mmid_version)))
			ctx = get_new_mmid(mm);

		WRITE_ONCE(cpu_data[cpu].asid_cache, ctx);
		raw_spin_unlock_irqrestore(&cpu_mmid_lock, flags);
	}

	/*
	 * Invalidate the local TLB if needed. Note that we must only clear our
	 * bit in tlb_flush_pending after this is complete, so that the
	 * cpu_has_shared_ftlb_entries case below isn't misled.
	 */
	if (cpumask_test_cpu(cpu, &tlb_flush_pending)) {
		if (cpu_has_vtag_icache)
			flush_icache_all();
		local_flush_tlb_all();
		cpumask_clear_cpu(cpu, &tlb_flush_pending);
	}

	write_c0_memorymapid(ctx & cpu_asid_mask(&boot_cpu_data));

	/*
	 * If this CPU shares FTLB entries with its siblings and one or more of
	 * those siblings hasn't yet invalidated its TLB following a version
	 * increase then we need to invalidate any TLB entries for our MMID
	 * that we might otherwise pick up from a sibling.
	 *
	 * We ifdef on CONFIG_SMP because cpu_sibling_map isn't defined in
	 * CONFIG_SMP=n kernels.
	 */
#ifdef CONFIG_SMP
	if (cpu_has_shared_ftlb_entries &&
	    cpumask_intersects(&tlb_flush_pending, &cpu_sibling_map[cpu])) {
		/* Ensure we operate on the new MMID */
		mtc0_tlbw_hazard();

		/*
		 * Invalidate all TLB entries associated with the new
		 * MMID, and wait for the invalidation to complete.
		 */
		ginvt_mmid();
		sync_ginv();
	}
#endif

setup_pgd:
	TLBMISS_HANDLER_SETUP_PGD(mm->pgd);
}