#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
struct rwlock {int dummy; } ;
typedef  int pt_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int pd_entry_t ;
struct TYPE_4__ {scalar_t__ ref_count; int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ NPTEPG ; 
 int PG_FICTITIOUS ; 
 int PG_FRAME ; 
 int PG_PS ; 
 TYPE_1__* PHYS_TO_VM_PAGE (int) ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_MAXUSER_ADDRESS ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 int /*<<< orphan*/  ad_emulation_superpage_promotions ; 
 int /*<<< orphan*/  atomic_add_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  num_accessed_emulations ; 
 int /*<<< orphan*/  num_dirty_emulations ; 
 int /*<<< orphan*/  num_superpage_accessed_emulations ; 
 int pmap_accessed_bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_emulate_ad_bits (int /*<<< orphan*/ ) ; 
 int pmap_modified_bit (int /*<<< orphan*/ ) ; 
 int* pmap_pde (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* pmap_pde_to_pte (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_promote_pde (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,struct rwlock**) ; 
 scalar_t__ pmap_ps_enabled (int /*<<< orphan*/ ) ; 
 int pmap_rw_bit (int /*<<< orphan*/ ) ; 
 int pmap_valid_bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_wunlock (struct rwlock*) ; 
 scalar_t__ vm_reserv_level_iffullpop (TYPE_1__*) ; 

int
pmap_emulate_accessed_dirty(pmap_t pmap, vm_offset_t va, int ftype)
{
	int rv;
	struct rwlock *lock;
#if VM_NRESERVLEVEL > 0
	vm_page_t m, mpte;
#endif
	pd_entry_t *pde;
	pt_entry_t *pte, PG_A, PG_M, PG_RW, PG_V;

	KASSERT(ftype == VM_PROT_READ || ftype == VM_PROT_WRITE,
	    ("pmap_emulate_accessed_dirty: invalid fault type %d", ftype));

	if (!pmap_emulate_ad_bits(pmap))
		return (-1);

	PG_A = pmap_accessed_bit(pmap);
	PG_M = pmap_modified_bit(pmap);
	PG_V = pmap_valid_bit(pmap);
	PG_RW = pmap_rw_bit(pmap);

	rv = -1;
	lock = NULL;
	PMAP_LOCK(pmap);

	pde = pmap_pde(pmap, va);
	if (pde == NULL || (*pde & PG_V) == 0)
		goto done;

	if ((*pde & PG_PS) != 0) {
		if (ftype == VM_PROT_READ) {
#ifdef INVARIANTS
			atomic_add_long(&num_superpage_accessed_emulations, 1);
#endif
			*pde |= PG_A;
			rv = 0;
		}
		goto done;
	}

	pte = pmap_pde_to_pte(pde, va);
	if ((*pte & PG_V) == 0)
		goto done;

	if (ftype == VM_PROT_WRITE) {
		if ((*pte & PG_RW) == 0)
			goto done;
		/*
		 * Set the modified and accessed bits simultaneously.
		 *
		 * Intel EPT PTEs that do software emulation of A/D bits map
		 * PG_A and PG_M to EPT_PG_READ and EPT_PG_WRITE respectively.
		 * An EPT misconfiguration is triggered if the PTE is writable
		 * but not readable (WR=10). This is avoided by setting PG_A
		 * and PG_M simultaneously.
		 */
		*pte |= PG_M | PG_A;
	} else {
		*pte |= PG_A;
	}

#if VM_NRESERVLEVEL > 0
	/* try to promote the mapping */
	if (va < VM_MAXUSER_ADDRESS)
		mpte = PHYS_TO_VM_PAGE(*pde & PG_FRAME);
	else
		mpte = NULL;

	m = PHYS_TO_VM_PAGE(*pte & PG_FRAME);

	if ((mpte == NULL || mpte->ref_count == NPTEPG) &&
	    pmap_ps_enabled(pmap) &&
	    (m->flags & PG_FICTITIOUS) == 0 &&
	    vm_reserv_level_iffullpop(m) == 0) {
		pmap_promote_pde(pmap, pde, va, &lock);
#ifdef INVARIANTS
		atomic_add_long(&ad_emulation_superpage_promotions, 1);
#endif
	}
#endif

#ifdef INVARIANTS
	if (ftype == VM_PROT_WRITE)
		atomic_add_long(&num_dirty_emulations, 1);
	else
		atomic_add_long(&num_accessed_emulations, 1);
#endif
	rv = 0;		/* success */
done:
	if (lock != NULL)
		rw_wunlock(lock);
	PMAP_UNLOCK(pmap);
	return (rv);
}