#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {unsigned long vm_start; unsigned long vm_end; int vm_flags; unsigned long vm_pgoff; int /*<<< orphan*/  vm_page_prot; } ;
struct revmap_entry {unsigned long guest_rpte; } ;
struct page {int dummy; } ;
struct TYPE_10__ {unsigned long pgfault_addr; unsigned long* pgfault_hpte; long pgfault_index; TYPE_2__* pgfault_cache; } ;
struct kvm_vcpu {struct kvm* kvm; TYPE_3__ arch; } ;
struct kvm_run {int dummy; } ;
struct TYPE_8__ {unsigned long* rmap; } ;
struct kvm_memory_slot {int flags; unsigned long base_gfn; TYPE_1__ arch; } ;
struct TYPE_12__ {struct revmap_entry* rev; scalar_t__ virt; } ;
struct TYPE_11__ {int /*<<< orphan*/  mmu_ready; TYPE_5__ hpt; int /*<<< orphan*/  mmio_update; } ;
struct kvm {unsigned long mmu_notifier_seq; TYPE_4__ arch; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_14__ {TYPE_6__* mm; } ;
struct TYPE_13__ {int /*<<< orphan*/  pgd; int /*<<< orphan*/  mmap_sem; } ;
struct TYPE_9__ {long mmio_update; unsigned long rpte; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_ARCH_300 ; 
 unsigned long DSISR_ISSTORE ; 
 int EFAULT ; 
 int /*<<< orphan*/  FOLL_WRITE ; 
 unsigned long HPTE_R_C ; 
 unsigned long HPTE_R_G ; 
 unsigned long HPTE_R_I ; 
 unsigned long HPTE_R_KEY_HI ; 
 unsigned long HPTE_R_M ; 
 unsigned long HPTE_R_PP0 ; 
 unsigned long HPTE_R_R ; 
 unsigned long HPTE_R_RPN ; 
 unsigned long HPTE_R_W ; 
 unsigned long HPTE_V_ABSENT ; 
 unsigned long HPTE_V_HVLOCK ; 
 unsigned long HPTE_V_VALID ; 
 unsigned long KVMPPC_RMAP_RC_SHIFT ; 
 int KVM_MEMSLOT_INVALID ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 scalar_t__ PageHuge (struct page*) ; 
 int RESUME_GUEST ; 
 int /*<<< orphan*/  SetPageDirty (struct page*) ; 
 int VM_PFNMAP ; 
 unsigned int VM_WRITE ; 
 int /*<<< orphan*/  __pte (int /*<<< orphan*/ ) ; 
 scalar_t__ __pte_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __unlock_hpte (int /*<<< orphan*/ *,unsigned long) ; 
 long atomic64_read (int /*<<< orphan*/ *) ; 
 unsigned long be64_to_cpu (int /*<<< orphan*/ ) ; 
 struct page* compound_head (struct page*) ; 
 unsigned long compound_order (struct page*) ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  cpu_to_be64 (unsigned long) ; 
 TYPE_7__* current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eieio () ; 
 int /*<<< orphan*/ * find_current_mm_pte (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct vm_area_struct* find_vma (TYPE_6__*,unsigned long) ; 
 long get_user_pages_fast (unsigned long,int,int /*<<< orphan*/ ,struct page**) ; 
 unsigned long gfn_to_hva_memslot (struct kvm_memory_slot*,unsigned long) ; 
 struct kvm_memory_slot* gfn_to_memslot (struct kvm*,unsigned long) ; 
 int /*<<< orphan*/  hpte_cache_flags_ok (unsigned long,int) ; 
 scalar_t__ hpte_is_writable (unsigned long) ; 
 unsigned long hpte_make_readonly (unsigned long) ; 
 unsigned long hpte_new_to_old_r (unsigned long) ; 
 unsigned long hpte_new_to_old_v (unsigned long,unsigned long) ; 
 unsigned long hpte_old_to_new_r (unsigned long,unsigned long) ; 
 unsigned long hpte_old_to_new_v (unsigned long) ; 
 scalar_t__ kvm_is_radix (struct kvm*) ; 
 unsigned long kvmppc_actual_pgsz (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  kvmppc_add_revmap_chain (struct kvm*,struct revmap_entry*,unsigned long*,long,int /*<<< orphan*/ ) ; 
 int kvmppc_book3s_radix_page_fault (struct kvm_run*,struct kvm_vcpu*,unsigned long,unsigned long) ; 
 int kvmppc_hv_emulate_mmio (struct kvm_run*,struct kvm_vcpu*,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  kvmppc_invalidate_hpte (struct kvm*,int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  kvmppc_read_update_linux_pte (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  lock_rmap (unsigned long*) ; 
 scalar_t__ mmu_notifier_retry (struct kvm*,unsigned long) ; 
 unsigned long page_to_pfn (struct page*) ; 
 int /*<<< orphan*/  pgprot_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int pte_ci (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  trace_kvm_page_fault_enter (struct kvm_vcpu*,unsigned long*,struct kvm_memory_slot*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  trace_kvm_page_fault_exit (struct kvm_vcpu*,unsigned long*,long) ; 
 int /*<<< orphan*/  try_lock_hpte (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  unlock_hpte (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  unlock_rmap (unsigned long*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int kvmppc_book3s_hv_page_fault(struct kvm_run *run, struct kvm_vcpu *vcpu,
				unsigned long ea, unsigned long dsisr)
{
	struct kvm *kvm = vcpu->kvm;
	unsigned long hpte[3], r;
	unsigned long hnow_v, hnow_r;
	__be64 *hptep;
	unsigned long mmu_seq, psize, pte_size;
	unsigned long gpa_base, gfn_base;
	unsigned long gpa, gfn, hva, pfn;
	struct kvm_memory_slot *memslot;
	unsigned long *rmap;
	struct revmap_entry *rev;
	struct page *page, *pages[1];
	long index, ret, npages;
	bool is_ci;
	unsigned int writing, write_ok;
	struct vm_area_struct *vma;
	unsigned long rcbits;
	long mmio_update;

	if (kvm_is_radix(kvm))
		return kvmppc_book3s_radix_page_fault(run, vcpu, ea, dsisr);

	/*
	 * Real-mode code has already searched the HPT and found the
	 * entry we're interested in.  Lock the entry and check that
	 * it hasn't changed.  If it has, just return and re-execute the
	 * instruction.
	 */
	if (ea != vcpu->arch.pgfault_addr)
		return RESUME_GUEST;

	if (vcpu->arch.pgfault_cache) {
		mmio_update = atomic64_read(&kvm->arch.mmio_update);
		if (mmio_update == vcpu->arch.pgfault_cache->mmio_update) {
			r = vcpu->arch.pgfault_cache->rpte;
			psize = kvmppc_actual_pgsz(vcpu->arch.pgfault_hpte[0],
						   r);
			gpa_base = r & HPTE_R_RPN & ~(psize - 1);
			gfn_base = gpa_base >> PAGE_SHIFT;
			gpa = gpa_base | (ea & (psize - 1));
			return kvmppc_hv_emulate_mmio(run, vcpu, gpa, ea,
						dsisr & DSISR_ISSTORE);
		}
	}
	index = vcpu->arch.pgfault_index;
	hptep = (__be64 *)(kvm->arch.hpt.virt + (index << 4));
	rev = &kvm->arch.hpt.rev[index];
	preempt_disable();
	while (!try_lock_hpte(hptep, HPTE_V_HVLOCK))
		cpu_relax();
	hpte[0] = be64_to_cpu(hptep[0]) & ~HPTE_V_HVLOCK;
	hpte[1] = be64_to_cpu(hptep[1]);
	hpte[2] = r = rev->guest_rpte;
	unlock_hpte(hptep, hpte[0]);
	preempt_enable();

	if (cpu_has_feature(CPU_FTR_ARCH_300)) {
		hpte[0] = hpte_new_to_old_v(hpte[0], hpte[1]);
		hpte[1] = hpte_new_to_old_r(hpte[1]);
	}
	if (hpte[0] != vcpu->arch.pgfault_hpte[0] ||
	    hpte[1] != vcpu->arch.pgfault_hpte[1])
		return RESUME_GUEST;

	/* Translate the logical address and get the page */
	psize = kvmppc_actual_pgsz(hpte[0], r);
	gpa_base = r & HPTE_R_RPN & ~(psize - 1);
	gfn_base = gpa_base >> PAGE_SHIFT;
	gpa = gpa_base | (ea & (psize - 1));
	gfn = gpa >> PAGE_SHIFT;
	memslot = gfn_to_memslot(kvm, gfn);

	trace_kvm_page_fault_enter(vcpu, hpte, memslot, ea, dsisr);

	/* No memslot means it's an emulated MMIO region */
	if (!memslot || (memslot->flags & KVM_MEMSLOT_INVALID))
		return kvmppc_hv_emulate_mmio(run, vcpu, gpa, ea,
					      dsisr & DSISR_ISSTORE);

	/*
	 * This should never happen, because of the slot_is_aligned()
	 * check in kvmppc_do_h_enter().
	 */
	if (gfn_base < memslot->base_gfn)
		return -EFAULT;

	/* used to check for invalidations in progress */
	mmu_seq = kvm->mmu_notifier_seq;
	smp_rmb();

	ret = -EFAULT;
	is_ci = false;
	pfn = 0;
	page = NULL;
	pte_size = PAGE_SIZE;
	writing = (dsisr & DSISR_ISSTORE) != 0;
	/* If writing != 0, then the HPTE must allow writing, if we get here */
	write_ok = writing;
	hva = gfn_to_hva_memslot(memslot, gfn);
	npages = get_user_pages_fast(hva, 1, writing ? FOLL_WRITE : 0, pages);
	if (npages < 1) {
		/* Check if it's an I/O mapping */
		down_read(&current->mm->mmap_sem);
		vma = find_vma(current->mm, hva);
		if (vma && vma->vm_start <= hva && hva + psize <= vma->vm_end &&
		    (vma->vm_flags & VM_PFNMAP)) {
			pfn = vma->vm_pgoff +
				((hva - vma->vm_start) >> PAGE_SHIFT);
			pte_size = psize;
			is_ci = pte_ci(__pte((pgprot_val(vma->vm_page_prot))));
			write_ok = vma->vm_flags & VM_WRITE;
		}
		up_read(&current->mm->mmap_sem);
		if (!pfn)
			goto out_put;
	} else {
		page = pages[0];
		pfn = page_to_pfn(page);
		if (PageHuge(page)) {
			page = compound_head(page);
			pte_size <<= compound_order(page);
		}
		/* if the guest wants write access, see if that is OK */
		if (!writing && hpte_is_writable(r)) {
			pte_t *ptep, pte;
			unsigned long flags;
			/*
			 * We need to protect against page table destruction
			 * hugepage split and collapse.
			 */
			local_irq_save(flags);
			ptep = find_current_mm_pte(current->mm->pgd,
						   hva, NULL, NULL);
			if (ptep) {
				pte = kvmppc_read_update_linux_pte(ptep, 1);
				if (__pte_write(pte))
					write_ok = 1;
			}
			local_irq_restore(flags);
		}
	}

	if (psize > pte_size)
		goto out_put;

	/* Check WIMG vs. the actual page we're accessing */
	if (!hpte_cache_flags_ok(r, is_ci)) {
		if (is_ci)
			goto out_put;
		/*
		 * Allow guest to map emulated device memory as
		 * uncacheable, but actually make it cacheable.
		 */
		r = (r & ~(HPTE_R_W|HPTE_R_I|HPTE_R_G)) | HPTE_R_M;
	}

	/*
	 * Set the HPTE to point to pfn.
	 * Since the pfn is at PAGE_SIZE granularity, make sure we
	 * don't mask out lower-order bits if psize < PAGE_SIZE.
	 */
	if (psize < PAGE_SIZE)
		psize = PAGE_SIZE;
	r = (r & HPTE_R_KEY_HI) | (r & ~(HPTE_R_PP0 - psize)) |
					((pfn << PAGE_SHIFT) & ~(psize - 1));
	if (hpte_is_writable(r) && !write_ok)
		r = hpte_make_readonly(r);
	ret = RESUME_GUEST;
	preempt_disable();
	while (!try_lock_hpte(hptep, HPTE_V_HVLOCK))
		cpu_relax();
	hnow_v = be64_to_cpu(hptep[0]);
	hnow_r = be64_to_cpu(hptep[1]);
	if (cpu_has_feature(CPU_FTR_ARCH_300)) {
		hnow_v = hpte_new_to_old_v(hnow_v, hnow_r);
		hnow_r = hpte_new_to_old_r(hnow_r);
	}

	/*
	 * If the HPT is being resized, don't update the HPTE,
	 * instead let the guest retry after the resize operation is complete.
	 * The synchronization for mmu_ready test vs. set is provided
	 * by the HPTE lock.
	 */
	if (!kvm->arch.mmu_ready)
		goto out_unlock;

	if ((hnow_v & ~HPTE_V_HVLOCK) != hpte[0] || hnow_r != hpte[1] ||
	    rev->guest_rpte != hpte[2])
		/* HPTE has been changed under us; let the guest retry */
		goto out_unlock;
	hpte[0] = (hpte[0] & ~HPTE_V_ABSENT) | HPTE_V_VALID;

	/* Always put the HPTE in the rmap chain for the page base address */
	rmap = &memslot->arch.rmap[gfn_base - memslot->base_gfn];
	lock_rmap(rmap);

	/* Check if we might have been invalidated; let the guest retry if so */
	ret = RESUME_GUEST;
	if (mmu_notifier_retry(vcpu->kvm, mmu_seq)) {
		unlock_rmap(rmap);
		goto out_unlock;
	}

	/* Only set R/C in real HPTE if set in both *rmap and guest_rpte */
	rcbits = *rmap >> KVMPPC_RMAP_RC_SHIFT;
	r &= rcbits | ~(HPTE_R_R | HPTE_R_C);

	if (be64_to_cpu(hptep[0]) & HPTE_V_VALID) {
		/* HPTE was previously valid, so we need to invalidate it */
		unlock_rmap(rmap);
		hptep[0] |= cpu_to_be64(HPTE_V_ABSENT);
		kvmppc_invalidate_hpte(kvm, hptep, index);
		/* don't lose previous R and C bits */
		r |= be64_to_cpu(hptep[1]) & (HPTE_R_R | HPTE_R_C);
	} else {
		kvmppc_add_revmap_chain(kvm, rev, rmap, index, 0);
	}

	if (cpu_has_feature(CPU_FTR_ARCH_300)) {
		r = hpte_old_to_new_r(hpte[0], r);
		hpte[0] = hpte_old_to_new_v(hpte[0]);
	}
	hptep[1] = cpu_to_be64(r);
	eieio();
	__unlock_hpte(hptep, hpte[0]);
	asm volatile("ptesync" : : : "memory");
	preempt_enable();
	if (page && hpte_is_writable(r))
		SetPageDirty(page);

 out_put:
	trace_kvm_page_fault_exit(vcpu, hpte, ret);

	if (page) {
		/*
		 * We drop pages[0] here, not page because page might
		 * have been set to the head page of a compound, but
		 * we have to drop the reference on the correct tail
		 * page to match the get inside gup()
		 */
		put_page(pages[0]);
	}
	return ret;

 out_unlock:
	__unlock_hpte(hptep, be64_to_cpu(hptep[0]));
	preempt_enable();
	goto out_put;
}