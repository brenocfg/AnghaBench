#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct vmstate {size_t phnum; scalar_t__* l1pt; TYPE_5__* phdr; } ;
struct kvm_nlist {char* n_name; scalar_t__ n_value; } ;
typedef  int /*<<< orphan*/  pa ;
struct TYPE_9__ {int /*<<< orphan*/  program; struct vmstate* vmst; scalar_t__ rawdump; } ;
typedef  TYPE_1__ kvm_t ;
typedef  scalar_t__ kvaddr_t ;
typedef  scalar_t__ arm_physaddr_t ;
typedef  scalar_t__ arm_pd_entry_t ;
struct TYPE_10__ {scalar_t__ p_type; scalar_t__ p_paddr; scalar_t__ p_vaddr; } ;

/* Variables and functions */
 int ARM_L1_TABLE_SIZE ; 
 scalar_t__ KERNBASE ; 
 scalar_t__ PT_DUMP_DELTA ; 
 int /*<<< orphan*/  _kvm_err (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 void* _kvm_malloc (TYPE_1__*,int) ; 
 int _kvm_read_core_phdrs (TYPE_1__*,size_t*,TYPE_5__**) ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 scalar_t__ kvm_nlist2 (TYPE_1__*,struct kvm_nlist*) ; 
 int kvm_read2 (TYPE_1__*,scalar_t__,scalar_t__*,int) ; 

__attribute__((used)) static int
_arm_initvtop(kvm_t *kd)
{
	struct vmstate *vm;
	struct kvm_nlist nl[2];
	kvaddr_t kernbase;
	arm_physaddr_t physaddr, pa;
	arm_pd_entry_t *l1pt;
	size_t i;
	int found;

	if (kd->rawdump) {
		_kvm_err(kd, kd->program, "raw dumps not supported on arm");
		return (-1);
	}

	vm = _kvm_malloc(kd, sizeof(*vm));
	if (vm == NULL) {
		_kvm_err(kd, kd->program, "cannot allocate vm");
		return (-1);
	}
	kd->vmst = vm;
	vm->l1pt = NULL;

	if (_kvm_read_core_phdrs(kd, &vm->phnum, &vm->phdr) == -1)
		return (-1);

	found = 0;
	for (i = 0; i < vm->phnum; i++) {
		if (vm->phdr[i].p_type == PT_DUMP_DELTA) {
			kernbase = vm->phdr[i].p_vaddr;
			physaddr = vm->phdr[i].p_paddr;
			found = 1;
			break;
		}
	}

	nl[1].n_name = NULL;
	if (!found) {
		nl[0].n_name = "kernbase";
		if (kvm_nlist2(kd, nl) != 0) {
#ifdef __arm__
			kernbase = KERNBASE;
#else
		_kvm_err(kd, kd->program, "cannot resolve kernbase");
		return (-1);
#endif
		} else
			kernbase = nl[0].n_value;

		nl[0].n_name = "physaddr";
		if (kvm_nlist2(kd, nl) != 0) {
			_kvm_err(kd, kd->program, "couldn't get phys addr");
			return (-1);
		}
		physaddr = nl[0].n_value;
	}
	nl[0].n_name = "kernel_l1pa";
	if (kvm_nlist2(kd, nl) != 0) {
		_kvm_err(kd, kd->program, "bad namelist");
		return (-1);
	}
	if (kvm_read2(kd, (nl[0].n_value - kernbase + physaddr), &pa,
	    sizeof(pa)) != sizeof(pa)) {
		_kvm_err(kd, kd->program, "cannot read kernel_l1pa");
		return (-1);
	}
	l1pt = _kvm_malloc(kd, ARM_L1_TABLE_SIZE);
	if (l1pt == NULL) {
		_kvm_err(kd, kd->program, "cannot allocate l1pt");
		return (-1);
	}
	if (kvm_read2(kd, pa, l1pt, ARM_L1_TABLE_SIZE) != ARM_L1_TABLE_SIZE) {
		_kvm_err(kd, kd->program, "cannot read l1pt");
		free(l1pt);
		return (-1);
	}
	vm->l1pt = l1pt;
	return 0;
}