#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct vmstate {int mapsz; uintptr_t dmphdrsz; TYPE_2__* eh; void* ph; TYPE_2__* map; } ;
struct kerneldumpheader {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  program; int /*<<< orphan*/  pmfd; struct vmstate* vmst; } ;
typedef  TYPE_1__ kvm_t ;
struct TYPE_9__ {int /*<<< orphan*/  e_phoff; int /*<<< orphan*/  e_phnum; int /*<<< orphan*/  e_phentsize; } ;

/* Variables and functions */
 TYPE_2__* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_PRIVATE ; 
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  _kvm_err (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 uintptr_t be16toh (int /*<<< orphan*/ ) ; 
 uintptr_t be32toh (int /*<<< orphan*/ ) ; 
 uintptr_t dump_header_size (TYPE_2__*) ; 
 void* mmap (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (TYPE_2__*,int) ; 
 int /*<<< orphan*/  valid_elf_header (TYPE_2__*) ; 

__attribute__((used)) static int
powerpc_maphdrs(kvm_t *kd)
{
	struct vmstate *vm;
	size_t mapsz;

	vm = kd->vmst;

	vm->mapsz = sizeof(*vm->eh) + sizeof(struct kerneldumpheader);
	vm->map = mmap(NULL, vm->mapsz, PROT_READ, MAP_PRIVATE, kd->pmfd, 0);
	if (vm->map == MAP_FAILED) {
		_kvm_err(kd, kd->program, "cannot map corefile");
		return (-1);
	}
	vm->dmphdrsz = 0;
	vm->eh = vm->map;
	if (!valid_elf_header(vm->eh)) {
		/*
		 * Hmmm, no ELF header. Maybe we still have a dump header.
		 * This is normal when the core file wasn't created by
		 * savecore(8), but instead was dumped over TFTP. We can
		 * easily skip the dump header...
		 */
		vm->dmphdrsz = dump_header_size(vm->map);
		if (vm->dmphdrsz == 0)
			goto inval;
		vm->eh = (void *)((uintptr_t)vm->map + vm->dmphdrsz);
		if (!valid_elf_header(vm->eh))
			goto inval;
	}
	mapsz = be16toh(vm->eh->e_phentsize) * be16toh(vm->eh->e_phnum) +
	    be32toh(vm->eh->e_phoff);
	munmap(vm->map, vm->mapsz);

	/* Map all headers. */
	vm->mapsz = vm->dmphdrsz + mapsz;
	vm->map = mmap(NULL, vm->mapsz, PROT_READ, MAP_PRIVATE, kd->pmfd, 0);
	if (vm->map == MAP_FAILED) {
		_kvm_err(kd, kd->program, "cannot map corefile headers");
		return (-1);
	}
	vm->eh = (void *)((uintptr_t)vm->map + vm->dmphdrsz);
	vm->ph = (void *)((uintptr_t)vm->eh + be32toh(vm->eh->e_phoff));
	return (0);

 inval:
	_kvm_err(kd, kd->program, "invalid corefile");
	return (-1);
}