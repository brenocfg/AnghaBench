#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int* e_ident; } ;
struct TYPE_5__ {int /*<<< orphan*/  program; TYPE_2__ nlehdr; int /*<<< orphan*/  nlfd; } ;
typedef  TYPE_1__ kvm_t ;
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 size_t EI_DATA ; 
#define  ELFDATA2LSB 129 
#define  ELFDATA2MSB 128 
 int /*<<< orphan*/  ELF_C_READ ; 
 scalar_t__ ELF_K_ELF ; 
 int /*<<< orphan*/  EV_CURRENT ; 
 scalar_t__ EV_NONE ; 
 int /*<<< orphan*/  _kvm_err (TYPE_1__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * elf_begin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_errmsg (int /*<<< orphan*/ ) ; 
 scalar_t__ elf_kind (int /*<<< orphan*/ *) ; 
 scalar_t__ elf_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gelf_getehdr (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static int
_kvm_read_kernel_ehdr(kvm_t *kd)
{
	Elf *elf;

	if (elf_version(EV_CURRENT) == EV_NONE) {
		_kvm_err(kd, kd->program, "Unsupported libelf");
		return (-1);
	}
	elf = elf_begin(kd->nlfd, ELF_C_READ, NULL);
	if (elf == NULL) {
		_kvm_err(kd, kd->program, "%s", elf_errmsg(0));
		return (-1);
	}
	if (elf_kind(elf) != ELF_K_ELF) {
		_kvm_err(kd, kd->program, "kernel is not an ELF file");
		return (-1);
	}
	if (gelf_getehdr(elf, &kd->nlehdr) == NULL) {
		_kvm_err(kd, kd->program, "%s", elf_errmsg(0));
		elf_end(elf);
		return (-1);
	}
	elf_end(elf);

	switch (kd->nlehdr.e_ident[EI_DATA]) {
	case ELFDATA2LSB:
	case ELFDATA2MSB:
		return (0);
	default:
		_kvm_err(kd, kd->program,
		    "unsupported ELF data encoding for kernel");
		return (-1);
	}
}