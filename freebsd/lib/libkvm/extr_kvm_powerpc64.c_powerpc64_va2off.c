#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vmstate {scalar_t__ dmphdrsz; TYPE_1__* eh; TYPE_3__* ph; } ;
typedef  scalar_t__ off_t ;
struct TYPE_6__ {struct vmstate* vmst; } ;
typedef  TYPE_2__ kvm_t ;
typedef  scalar_t__ kvaddr_t ;
struct TYPE_7__ {int /*<<< orphan*/  p_vaddr; int /*<<< orphan*/  p_memsz; int /*<<< orphan*/  p_offset; } ;
struct TYPE_5__ {int /*<<< orphan*/  e_phentsize; int /*<<< orphan*/  e_phnum; } ;
typedef  TYPE_3__ Elf64_Phdr ;

/* Variables and functions */
 uintptr_t be16toh (int /*<<< orphan*/ ) ; 
 scalar_t__ be64toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
powerpc64_va2off(kvm_t *kd, kvaddr_t va, off_t *ofs)
{
	struct vmstate *vm = kd->vmst;
	Elf64_Phdr *ph;
	int nph;

	ph = vm->ph;
	nph = be16toh(vm->eh->e_phnum);
	while (nph && (va < be64toh(ph->p_vaddr) ||
	    va >= be64toh(ph->p_vaddr) + be64toh(ph->p_memsz))) {
		nph--;
		ph = (void *)((uintptr_t)ph + be16toh(vm->eh->e_phentsize));
	}
	if (nph == 0)
		return (0);

	/* Segment found. Return file offset and range. */
	*ofs = vm->dmphdrsz + be64toh(ph->p_offset) +
	    (va - be64toh(ph->p_vaddr));
	return (be64toh(ph->p_memsz) - (va - be64toh(ph->p_vaddr)));
}