#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_prot_t ;
typedef  size_t u_long ;
struct TYPE_7__ {int pmapsize; int version; size_t kernbase; size_t dmapbase; size_t dmapend; int /*<<< orphan*/  bitmapsize; } ;
struct vmstate {TYPE_1__ hdr; } ;
struct kvm_bitmap {int dummy; } ;
typedef  int /*<<< orphan*/  kvm_walk_pages_cb_t ;
struct TYPE_8__ {struct vmstate* vmst; } ;
typedef  TYPE_2__ kvm_t ;
typedef  size_t amd64_pte_t ;
typedef  size_t amd64_pde_t ;

/* Variables and functions */
 unsigned int AMD64_NBPDR ; 
 size_t AMD64_NPTEPG ; 
 size_t AMD64_PAGE_SIZE ; 
 size_t AMD64_PDRMASK ; 
 size_t AMD64_PDRSHIFT ; 
 size_t AMD64_PG_FRAME ; 
 size_t AMD64_PG_PS ; 
 size_t AMD64_PG_PS_FRAME ; 
 size_t AMD64_PG_V ; 
 size_t VA_OFF (struct vmstate*,size_t) ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 int _amd64_entry_to_prot (size_t) ; 
 size_t* _amd64_pde_first_pte (TYPE_2__*,size_t) ; 
 size_t _amd64_pde_get (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  _kvm_bitmap_deinit (struct kvm_bitmap*) ; 
 int /*<<< orphan*/  _kvm_bitmap_init (struct kvm_bitmap*,int /*<<< orphan*/ ,size_t*) ; 
 scalar_t__ _kvm_bitmap_next (struct kvm_bitmap*,size_t*) ; 
 int /*<<< orphan*/  _kvm_bitmap_set (struct kvm_bitmap*,size_t,size_t) ; 
 int /*<<< orphan*/  _kvm_visit_cb (TYPE_2__*,int /*<<< orphan*/ *,void*,size_t,size_t,size_t,int,unsigned int,unsigned int) ; 

__attribute__((used)) static int
_amd64_minidump_walk_pages(kvm_t *kd, kvm_walk_pages_cb_t *cb, void *arg)
{
	struct vmstate *vm = kd->vmst;
	u_long npdes = vm->hdr.pmapsize / sizeof(amd64_pde_t);
	u_long bmindex, dva, pa, pdeindex, va;
	struct kvm_bitmap bm;
	int ret = 0;
	vm_prot_t prot;
	unsigned int pgsz = AMD64_PAGE_SIZE;

	if (vm->hdr.version < 2)
		return (0);

	if (!_kvm_bitmap_init(&bm, vm->hdr.bitmapsize, &bmindex))
		return (0);

	for (pdeindex = 0; pdeindex < npdes; pdeindex++) {
		amd64_pde_t pde = _amd64_pde_get(kd, pdeindex);
		amd64_pte_t *ptes;
		u_long i;

		va = vm->hdr.kernbase + (pdeindex << AMD64_PDRSHIFT);
		if ((pde & AMD64_PG_V) == 0)
			continue;

		if ((pde & AMD64_PG_PS) != 0) {
			/*
			 * Large page.  Iterate on each 4K page section
			 * within this page.  This differs from 4K pages in
			 * that every page here uses the same PDE to
			 * generate permissions.
			 */
			pa = (pde & AMD64_PG_PS_FRAME) +
			    ((va & AMD64_PDRMASK) ^ VA_OFF(vm, va));
			dva = vm->hdr.dmapbase + pa;
			_kvm_bitmap_set(&bm, pa, AMD64_PAGE_SIZE);
			if (!_kvm_visit_cb(kd, cb, arg, pa, va, dva,
			    _amd64_entry_to_prot(pde), AMD64_NBPDR, pgsz)) {
				goto out;
			}
			continue;
		}

		/* 4K pages: pde references another page of entries. */
		ptes = _amd64_pde_first_pte(kd, pdeindex);
		/* Ignore page directory pages that were not dumped. */
		if (ptes == NULL)
			continue;

		for (i = 0; i < AMD64_NPTEPG; i++) {
			amd64_pte_t pte = (u_long)ptes[i];

			pa = pte & AMD64_PG_FRAME;
			dva = vm->hdr.dmapbase + pa;
			if ((pte & AMD64_PG_V) != 0) {
				_kvm_bitmap_set(&bm, pa, AMD64_PAGE_SIZE);
				if (!_kvm_visit_cb(kd, cb, arg, pa, va, dva,
				    _amd64_entry_to_prot(pte), pgsz, 0)) {
					goto out;
				}
			}
			va += AMD64_PAGE_SIZE;
		}
	}

	while (_kvm_bitmap_next(&bm, &bmindex)) {
		pa = bmindex * AMD64_PAGE_SIZE;
		dva = vm->hdr.dmapbase + pa;
		if (vm->hdr.dmapend < (dva + pgsz))
			break;
		va = 0;
		/* amd64/pmap.c: create_pagetables(): dmap always R|W. */
		prot = VM_PROT_READ | VM_PROT_WRITE;
		if (!_kvm_visit_cb(kd, cb, arg, pa, va, dva, prot, pgsz, 0)) {
			goto out;
		}
	}

	ret = 1;

out:
	_kvm_bitmap_deinit(&bm);
	return (ret);
}