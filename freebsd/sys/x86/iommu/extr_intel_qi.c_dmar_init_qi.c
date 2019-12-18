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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
struct dmar_unit {int hw_cap; int qi_enabled; int inv_waitd_seq; unsigned long long inv_queue_size; int /*<<< orphan*/  inv_queue; int /*<<< orphan*/  inv_waitd_seq_hw; void* inv_waitd_seq_hw_phys; scalar_t__ inv_queue_avail; scalar_t__ inv_waitd_gen; int /*<<< orphan*/  unit; int /*<<< orphan*/  qi_taskqueue; int /*<<< orphan*/  qi_task; int /*<<< orphan*/  tlb_flush_entries; } ;

/* Variables and functions */
 int DMAR_CAP_CM ; 
 int /*<<< orphan*/  DMAR_HAS_QI (struct dmar_unit*) ; 
 int DMAR_ICS_IWC ; 
 int /*<<< orphan*/  DMAR_ICS_REG ; 
 int DMAR_IQA_QS_DEF ; 
 int DMAR_IQA_QS_MAX ; 
 int /*<<< orphan*/  DMAR_IQA_REG ; 
 int /*<<< orphan*/  DMAR_IQT_REG ; 
 scalar_t__ DMAR_IQ_DESCR_SZ ; 
 int /*<<< orphan*/  DMAR_LOCK (struct dmar_unit*) ; 
 int /*<<< orphan*/  DMAR_UNLOCK (struct dmar_unit*) ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 unsigned long long PAGE_SIZE ; 
 int /*<<< orphan*/  PI_AV ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dmar_unit*) ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int*) ; 
 int /*<<< orphan*/  VM_MEMATTR_DEFAULT ; 
 int /*<<< orphan*/  dmar_enable_qi (struct dmar_unit*) ; 
 int /*<<< orphan*/  dmar_enable_qi_intr (struct dmar_unit*) ; 
 int /*<<< orphan*/  dmar_high ; 
 int /*<<< orphan*/  dmar_qi_task ; 
 int dmar_read4 (struct dmar_unit*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmar_write4 (struct dmar_unit*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dmar_write8 (struct dmar_unit*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kmem_alloc_contig (unsigned long long,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* pmap_kextract (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_create_fast (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_start_threads (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 

int
dmar_init_qi(struct dmar_unit *unit)
{
	uint64_t iqa;
	uint32_t ics;
	int qi_sz;

	if (!DMAR_HAS_QI(unit) || (unit->hw_cap & DMAR_CAP_CM) != 0)
		return (0);
	unit->qi_enabled = 1;
	TUNABLE_INT_FETCH("hw.dmar.qi", &unit->qi_enabled);
	if (!unit->qi_enabled)
		return (0);

	TAILQ_INIT(&unit->tlb_flush_entries);
	TASK_INIT(&unit->qi_task, 0, dmar_qi_task, unit);
	unit->qi_taskqueue = taskqueue_create_fast("dmarqf", M_WAITOK,
	    taskqueue_thread_enqueue, &unit->qi_taskqueue);
	taskqueue_start_threads(&unit->qi_taskqueue, 1, PI_AV,
	    "dmar%d qi taskq", unit->unit);

	unit->inv_waitd_gen = 0;
	unit->inv_waitd_seq = 1;

	qi_sz = DMAR_IQA_QS_DEF;
	TUNABLE_INT_FETCH("hw.dmar.qi_size", &qi_sz);
	if (qi_sz > DMAR_IQA_QS_MAX)
		qi_sz = DMAR_IQA_QS_MAX;
	unit->inv_queue_size = (1ULL << qi_sz) * PAGE_SIZE;
	/* Reserve one descriptor to prevent wraparound. */
	unit->inv_queue_avail = unit->inv_queue_size - DMAR_IQ_DESCR_SZ;

	/* The invalidation queue reads by DMARs are always coherent. */
	unit->inv_queue = kmem_alloc_contig(unit->inv_queue_size, M_WAITOK |
	    M_ZERO, 0, dmar_high, PAGE_SIZE, 0, VM_MEMATTR_DEFAULT);
	unit->inv_waitd_seq_hw_phys = pmap_kextract(
	    (vm_offset_t)&unit->inv_waitd_seq_hw);

	DMAR_LOCK(unit);
	dmar_write8(unit, DMAR_IQT_REG, 0);
	iqa = pmap_kextract(unit->inv_queue);
	iqa |= qi_sz;
	dmar_write8(unit, DMAR_IQA_REG, iqa);
	dmar_enable_qi(unit);
	ics = dmar_read4(unit, DMAR_ICS_REG);
	if ((ics & DMAR_ICS_IWC) != 0) {
		ics = DMAR_ICS_IWC;
		dmar_write4(unit, DMAR_ICS_REG, ics);
	}
	dmar_enable_qi_intr(unit);
	DMAR_UNLOCK(unit);

	return (0);
}