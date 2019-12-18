#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vmstate {int dh_nregions; int vm_nregions; scalar_t__ vm_tsb_off; void* dh_tsb_size; void* dh_tsb_pa; struct vmstate* vm_regions; void* dh_tsb_mask; void* vm_tsb_mask; void* dr_offs; void* dr_size; void* dr_pa; void* dh_hdr_size; } ;
struct sparc64_dump_reg {int dh_nregions; int vm_nregions; scalar_t__ vm_tsb_off; void* dh_tsb_size; void* dh_tsb_pa; struct sparc64_dump_reg* vm_regions; void* dh_tsb_mask; void* vm_tsb_mask; void* dr_offs; void* dr_size; void* dr_pa; void* dh_hdr_size; } ;
struct sparc64_dump_hdr {int dh_nregions; int vm_nregions; scalar_t__ vm_tsb_off; void* dh_tsb_size; void* dh_tsb_pa; struct sparc64_dump_hdr* vm_regions; void* dh_tsb_mask; void* vm_tsb_mask; void* dr_offs; void* dr_size; void* dr_pa; void* dh_hdr_size; } ;
struct TYPE_6__ {int /*<<< orphan*/  program; struct vmstate* vmst; } ;
typedef  TYPE_1__ kvm_t ;
typedef  int /*<<< orphan*/  hdr ;

/* Variables and functions */
 scalar_t__ KVM_OFF_NOTFOUND ; 
 int /*<<< orphan*/  _kvm_err (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 struct vmstate* _kvm_malloc (TYPE_1__*,size_t) ; 
 scalar_t__ _sparc64_find_off (struct vmstate*,void*,void*) ; 
 int /*<<< orphan*/  _sparc64_read_phys (TYPE_1__*,int,struct vmstate*,size_t) ; 
 int /*<<< orphan*/  _sparc64_reg_cmp ; 
 int be32toh (int) ; 
 void* be64toh (void*) ; 
 int /*<<< orphan*/  free (struct vmstate*) ; 
 int /*<<< orphan*/  qsort (struct vmstate*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
_sparc64_initvtop(kvm_t *kd)
{
	struct sparc64_dump_hdr hdr;
	struct sparc64_dump_reg	*regs;
	struct vmstate *vm;
	size_t regsz;
	int i;

	vm = (struct vmstate *)_kvm_malloc(kd, sizeof(*vm));
	if (vm == NULL) {
		_kvm_err(kd, kd->program, "cannot allocate vm");
		return (-1);
	}
	kd->vmst = vm;

	if (!_sparc64_read_phys(kd, 0, &hdr, sizeof(hdr)))
		goto fail_vm;
	hdr.dh_hdr_size = be64toh(hdr.dh_hdr_size);
	hdr.dh_tsb_pa = be64toh(hdr.dh_tsb_pa);
	hdr.dh_tsb_size = be64toh(hdr.dh_tsb_size);
	hdr.dh_tsb_mask = be64toh(hdr.dh_tsb_mask);
	hdr.dh_nregions = be32toh(hdr.dh_nregions);

	regsz = hdr.dh_nregions * sizeof(*regs);
	regs = _kvm_malloc(kd, regsz);
	if (regs == NULL) {
		_kvm_err(kd, kd->program, "cannot allocate regions");
		goto fail_vm;
	}
	if (!_sparc64_read_phys(kd, sizeof(hdr), regs, regsz))
		goto fail_regs;
	for (i = 0; i < hdr.dh_nregions; i++) {
		regs[i].dr_pa = be64toh(regs[i].dr_pa);
		regs[i].dr_size = be64toh(regs[i].dr_size);
		regs[i].dr_offs = be64toh(regs[i].dr_offs);
	}
	qsort(regs, hdr.dh_nregions, sizeof(*regs), _sparc64_reg_cmp);

	vm->vm_tsb_mask = hdr.dh_tsb_mask;
	vm->vm_regions = regs;
	vm->vm_nregions = hdr.dh_nregions;
	vm->vm_tsb_off = _sparc64_find_off(vm, hdr.dh_tsb_pa, hdr.dh_tsb_size);
	if (vm->vm_tsb_off == KVM_OFF_NOTFOUND) {
		_kvm_err(kd, kd->program, "tsb not found in dump");
		goto fail_regs;
	}
	return (0);

fail_regs:
	free(regs);
fail_vm:
	free(vm);
	return (-1);
}