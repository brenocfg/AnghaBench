#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  int u_long ;
struct TYPE_4__ {int kernbase; scalar_t__ paemode; } ;
struct vmstate {TYPE_1__ hdr; } ;
struct i386_iter {int pteindex; int nptes; TYPE_2__* kd; } ;
typedef  int i386_pte_t ;
typedef  int i386_pte_pae_t ;
struct TYPE_5__ {struct vmstate* vmst; } ;

/* Variables and functions */
 int I386_PAGE_SHIFT ; 
 int I386_PG_FRAME ; 
 int I386_PG_FRAME_PAE ; 
 int I386_PG_V ; 
 int /*<<< orphan*/  _i386_entry_to_prot (int) ; 
 int _i386_pte_get (TYPE_2__*,int) ; 
 int _i386_pte_pae_get (TYPE_2__*,int) ; 

__attribute__((used)) static int
_i386_iterator_next(struct i386_iter *it, u_long *pa, u_long *va, u_long *dva,
    vm_prot_t *prot)
{
	struct vmstate *vm = it->kd->vmst;
	i386_pte_t pte32;
	i386_pte_pae_t pte64;
	int found = 0;

	*dva = 0;
	*pa = 0;
	*va = 0;
	*dva = 0;
	*prot = 0;
	for (; it->pteindex < it->nptes && found == 0; it->pteindex++) {
		if (vm->hdr.paemode) {
			pte64 = _i386_pte_pae_get(it->kd, it->pteindex);
			if ((pte64 & I386_PG_V) == 0)
				continue;
			*prot = _i386_entry_to_prot(pte64);
			*pa = pte64 & I386_PG_FRAME_PAE;
		} else {
			pte32 = _i386_pte_get(it->kd, it->pteindex);
			if ((pte32 & I386_PG_V) == 0)
				continue;
			*prot = _i386_entry_to_prot(pte32);
			*pa = pte32 & I386_PG_FRAME;
		}
		*va = vm->hdr.kernbase + (it->pteindex << I386_PAGE_SHIFT);
		found = 1;
	}
	return found;
}