#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct vmstate {scalar_t__* PML4; int /*<<< orphan*/  phdr; int /*<<< orphan*/  phnum; } ;
struct kvm_nlist {char* n_name; scalar_t__ n_value; } ;
typedef  int /*<<< orphan*/  pa ;
struct TYPE_8__ {scalar_t__ rawdump; struct vmstate* vmst; int /*<<< orphan*/  program; } ;
typedef  TYPE_1__ kvm_t ;
typedef  scalar_t__ kvaddr_t ;
typedef  scalar_t__ amd64_pml4e_t ;
typedef  scalar_t__ amd64_physaddr_t ;

/* Variables and functions */
 int AMD64_PAGE_SIZE ; 
 int /*<<< orphan*/  _kvm_err (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__* _kvm_malloc (TYPE_1__*,int) ; 
 int _kvm_read_core_phdrs (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 scalar_t__ kvm_nlist2 (TYPE_1__*,struct kvm_nlist*) ; 
 int kvm_read2 (TYPE_1__*,scalar_t__,scalar_t__*,int) ; 
 scalar_t__ le64toh (scalar_t__) ; 

__attribute__((used)) static int
_amd64_initvtop(kvm_t *kd)
{
	struct kvm_nlist nl[2];
	amd64_physaddr_t pa;
	kvaddr_t kernbase;
	amd64_pml4e_t *PML4;

	kd->vmst = (struct vmstate *)_kvm_malloc(kd, sizeof(*kd->vmst));
	if (kd->vmst == NULL) {
		_kvm_err(kd, kd->program, "cannot allocate vm");
		return (-1);
	}
	kd->vmst->PML4 = 0;

	if (kd->rawdump == 0) {
		if (_kvm_read_core_phdrs(kd, &kd->vmst->phnum,
		    &kd->vmst->phdr) == -1)
			return (-1);
	}

	nl[0].n_name = "kernbase";
	nl[1].n_name = 0;

	if (kvm_nlist2(kd, nl) != 0) {
		_kvm_err(kd, kd->program, "bad namelist - no kernbase");
		return (-1);
	}
	kernbase = nl[0].n_value;

	nl[0].n_name = "KPML4phys";
	nl[1].n_name = 0;

	if (kvm_nlist2(kd, nl) != 0) {
		_kvm_err(kd, kd->program, "bad namelist - no KPML4phys");
		return (-1);
	}
	if (kvm_read2(kd, (nl[0].n_value - kernbase), &pa, sizeof(pa)) !=
	    sizeof(pa)) {
		_kvm_err(kd, kd->program, "cannot read KPML4phys");
		return (-1);
	}
	pa = le64toh(pa);
	PML4 = _kvm_malloc(kd, AMD64_PAGE_SIZE);
	if (PML4 == NULL) {
		_kvm_err(kd, kd->program, "cannot allocate PML4");
		return (-1);
	}
	if (kvm_read2(kd, pa, PML4, AMD64_PAGE_SIZE) != AMD64_PAGE_SIZE) {
		_kvm_err(kd, kd->program, "cannot read KPML4phys");
		free(PML4);
		return (-1);
	}
	kd->vmst->PML4 = PML4;
	return (0);
}