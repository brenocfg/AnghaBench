#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u64 ;
struct rmap_nested {unsigned long rmap; } ;
struct kvmppc_pte {unsigned int page_shift; unsigned long raddr; int rc; scalar_t__ may_execute; scalar_t__ may_write; scalar_t__ may_read; } ;
struct TYPE_4__ {unsigned long fault_dsisr; unsigned long fault_dar; int fault_gpa; } ;
struct kvm_vcpu {TYPE_1__ arch; struct kvm* kvm; } ;
struct kvm_run {int dummy; } ;
struct kvm_nested_guest {int /*<<< orphan*/  shadow_lpid; int /*<<< orphan*/  shadow_pgtable; scalar_t__ l1_lpid; int /*<<< orphan*/  l1_gr_to_hr; } ;
struct TYPE_6__ {unsigned long* rmap; } ;
struct kvm_memory_slot {int flags; unsigned long base_gfn; TYPE_3__ arch; } ;
struct TYPE_5__ {int /*<<< orphan*/  pgtable; } ;
struct kvm {unsigned long mmu_notifier_seq; int /*<<< orphan*/  mmu_lock; TYPE_2__ arch; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 unsigned long DSISR_BADACCESS ; 
 unsigned long DSISR_BAD_COPYPASTE ; 
 unsigned long DSISR_BAD_FAULT_64S ; 
 unsigned long DSISR_ISSTORE ; 
 unsigned long DSISR_NOEXEC_OR_G ; 
 unsigned long DSISR_NOHPTE ; 
 unsigned long DSISR_PROTFAULT ; 
 unsigned long DSISR_PRTABLE_FAULT ; 
 unsigned long DSISR_SET_RC ; 
 long EAGAIN ; 
 long EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int KVM_MEMSLOT_INVALID ; 
 int KVM_MEM_READONLY ; 
 unsigned int PAGE_SHIFT ; 
 unsigned int PMD_SHIFT ; 
 long RESUME_GUEST ; 
 long RESUME_HOST ; 
 unsigned long RMAP_NESTED_GPA_MASK ; 
 unsigned long RMAP_NESTED_LPID_SHIFT ; 
 int _PAGE_ACCESSED ; 
 unsigned long _PAGE_DIRTY ; 
 unsigned long _PAGE_EXEC ; 
 unsigned long _PAGE_READ ; 
 unsigned long _PAGE_WRITE ; 
 int /*<<< orphan*/ * __find_linux_pte (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  __pte (unsigned long) ; 
 struct kvm_memory_slot* gfn_to_memslot (struct kvm*,unsigned long) ; 
 int /*<<< orphan*/  kfree (struct rmap_nested*) ; 
 long kvmhv_handle_nested_set_rc (struct kvm_vcpu*,struct kvm_nested_guest*,unsigned long,struct kvmppc_pte,unsigned long) ; 
 int /*<<< orphan*/  kvmhv_invalidate_shadow_pte (struct kvm_vcpu*,struct kvm_nested_guest*,unsigned long,int /*<<< orphan*/ *) ; 
 long kvmhv_translate_addr_nested (struct kvm_vcpu*,struct kvm_nested_guest*,unsigned long,unsigned long,struct kvmppc_pte*) ; 
 int /*<<< orphan*/  kvmhv_update_ptbl_cache (struct kvm_nested_guest*) ; 
 long kvmppc_book3s_instantiate_page (struct kvm_vcpu*,unsigned long,struct kvm_memory_slot*,int,int,int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  kvmppc_core_queue_data_storage (struct kvm_vcpu*,unsigned long,unsigned long) ; 
 long kvmppc_create_pte (struct kvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,unsigned int,unsigned long,int /*<<< orphan*/ ,unsigned long*,struct rmap_nested**) ; 
 long kvmppc_hv_emulate_mmio (struct kvm_run*,struct kvm_vcpu*,unsigned long,unsigned long,int) ; 
 unsigned int kvmppc_radix_level_to_shift (unsigned int) ; 
 unsigned int kvmppc_radix_shift_to_level (unsigned int) ; 
 struct rmap_nested* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  pte_present (int /*<<< orphan*/ ) ; 
 unsigned long pte_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long int __kvmhv_nested_page_fault(struct kvm_run *run,
					  struct kvm_vcpu *vcpu,
					  struct kvm_nested_guest *gp)
{
	struct kvm *kvm = vcpu->kvm;
	struct kvm_memory_slot *memslot;
	struct rmap_nested *n_rmap;
	struct kvmppc_pte gpte;
	pte_t pte, *pte_p;
	unsigned long mmu_seq;
	unsigned long dsisr = vcpu->arch.fault_dsisr;
	unsigned long ea = vcpu->arch.fault_dar;
	unsigned long *rmapp;
	unsigned long n_gpa, gpa, gfn, perm = 0UL;
	unsigned int shift, l1_shift, level;
	bool writing = !!(dsisr & DSISR_ISSTORE);
	bool kvm_ro = false;
	long int ret;

	if (!gp->l1_gr_to_hr) {
		kvmhv_update_ptbl_cache(gp);
		if (!gp->l1_gr_to_hr)
			return RESUME_HOST;
	}

	/* Convert the nested guest real address into a L1 guest real address */

	n_gpa = vcpu->arch.fault_gpa & ~0xF000000000000FFFULL;
	if (!(dsisr & DSISR_PRTABLE_FAULT))
		n_gpa |= ea & 0xFFF;
	ret = kvmhv_translate_addr_nested(vcpu, gp, n_gpa, dsisr, &gpte);

	/*
	 * If the hardware found a translation but we don't now have a usable
	 * translation in the l1 partition-scoped tree, remove the shadow pte
	 * and let the guest retry.
	 */
	if (ret == RESUME_HOST &&
	    (dsisr & (DSISR_PROTFAULT | DSISR_BADACCESS | DSISR_NOEXEC_OR_G |
		      DSISR_BAD_COPYPASTE)))
		goto inval;
	if (ret)
		return ret;

	/* Failed to set the reference/change bits */
	if (dsisr & DSISR_SET_RC) {
		ret = kvmhv_handle_nested_set_rc(vcpu, gp, n_gpa, gpte, dsisr);
		if (ret == RESUME_HOST)
			return ret;
		if (ret)
			goto inval;
		dsisr &= ~DSISR_SET_RC;
		if (!(dsisr & (DSISR_BAD_FAULT_64S | DSISR_NOHPTE |
			       DSISR_PROTFAULT)))
			return RESUME_GUEST;
	}

	/*
	 * We took an HISI or HDSI while we were running a nested guest which
	 * means we have no partition scoped translation for that. This means
	 * we need to insert a pte for the mapping into our shadow_pgtable.
	 */

	l1_shift = gpte.page_shift;
	if (l1_shift < PAGE_SHIFT) {
		/* We don't support l1 using a page size smaller than our own */
		pr_err("KVM: L1 guest page shift (%d) less than our own (%d)\n",
			l1_shift, PAGE_SHIFT);
		return -EINVAL;
	}
	gpa = gpte.raddr;
	gfn = gpa >> PAGE_SHIFT;

	/* 1. Get the corresponding host memslot */

	memslot = gfn_to_memslot(kvm, gfn);
	if (!memslot || (memslot->flags & KVM_MEMSLOT_INVALID)) {
		if (dsisr & (DSISR_PRTABLE_FAULT | DSISR_BADACCESS)) {
			/* unusual error -> reflect to the guest as a DSI */
			kvmppc_core_queue_data_storage(vcpu, ea, dsisr);
			return RESUME_GUEST;
		}

		/* passthrough of emulated MMIO case */
		return kvmppc_hv_emulate_mmio(run, vcpu, gpa, ea, writing);
	}
	if (memslot->flags & KVM_MEM_READONLY) {
		if (writing) {
			/* Give the guest a DSI */
			kvmppc_core_queue_data_storage(vcpu, ea,
					DSISR_ISSTORE | DSISR_PROTFAULT);
			return RESUME_GUEST;
		}
		kvm_ro = true;
	}

	/* 2. Find the host pte for this L1 guest real address */

	/* Used to check for invalidations in progress */
	mmu_seq = kvm->mmu_notifier_seq;
	smp_rmb();

	/* See if can find translation in our partition scoped tables for L1 */
	pte = __pte(0);
	spin_lock(&kvm->mmu_lock);
	pte_p = __find_linux_pte(kvm->arch.pgtable, gpa, NULL, &shift);
	if (!shift)
		shift = PAGE_SHIFT;
	if (pte_p)
		pte = *pte_p;
	spin_unlock(&kvm->mmu_lock);

	if (!pte_present(pte) || (writing && !(pte_val(pte) & _PAGE_WRITE))) {
		/* No suitable pte found -> try to insert a mapping */
		ret = kvmppc_book3s_instantiate_page(vcpu, gpa, memslot,
					writing, kvm_ro, &pte, &level);
		if (ret == -EAGAIN)
			return RESUME_GUEST;
		else if (ret)
			return ret;
		shift = kvmppc_radix_level_to_shift(level);
	}
	/* Align gfn to the start of the page */
	gfn = (gpa & ~((1UL << shift) - 1)) >> PAGE_SHIFT;

	/* 3. Compute the pte we need to insert for nest_gpa -> host r_addr */

	/* The permissions is the combination of the host and l1 guest ptes */
	perm |= gpte.may_read ? 0UL : _PAGE_READ;
	perm |= gpte.may_write ? 0UL : _PAGE_WRITE;
	perm |= gpte.may_execute ? 0UL : _PAGE_EXEC;
	/* Only set accessed/dirty (rc) bits if set in host and l1 guest ptes */
	perm |= (gpte.rc & _PAGE_ACCESSED) ? 0UL : _PAGE_ACCESSED;
	perm |= ((gpte.rc & _PAGE_DIRTY) && writing) ? 0UL : _PAGE_DIRTY;
	pte = __pte(pte_val(pte) & ~perm);

	/* What size pte can we insert? */
	if (shift > l1_shift) {
		u64 mask;
		unsigned int actual_shift = PAGE_SHIFT;
		if (PMD_SHIFT < l1_shift)
			actual_shift = PMD_SHIFT;
		mask = (1UL << shift) - (1UL << actual_shift);
		pte = __pte(pte_val(pte) | (gpa & mask));
		shift = actual_shift;
	}
	level = kvmppc_radix_shift_to_level(shift);
	n_gpa &= ~((1UL << shift) - 1);

	/* 4. Insert the pte into our shadow_pgtable */

	n_rmap = kzalloc(sizeof(*n_rmap), GFP_KERNEL);
	if (!n_rmap)
		return RESUME_GUEST; /* Let the guest try again */
	n_rmap->rmap = (n_gpa & RMAP_NESTED_GPA_MASK) |
		(((unsigned long) gp->l1_lpid) << RMAP_NESTED_LPID_SHIFT);
	rmapp = &memslot->arch.rmap[gfn - memslot->base_gfn];
	ret = kvmppc_create_pte(kvm, gp->shadow_pgtable, pte, n_gpa, level,
				mmu_seq, gp->shadow_lpid, rmapp, &n_rmap);
	if (n_rmap)
		kfree(n_rmap);
	if (ret == -EAGAIN)
		ret = RESUME_GUEST;	/* Let the guest try again */

	return ret;

 inval:
	kvmhv_invalidate_shadow_pte(vcpu, gp, n_gpa, NULL);
	return RESUME_GUEST;
}