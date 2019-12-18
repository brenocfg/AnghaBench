#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__* e_ident; scalar_t__ e_machine; } ;
struct TYPE_8__ {int /*<<< orphan*/  program; TYPE_1__ nlehdr; int /*<<< orphan*/  pmfd; } ;
typedef  TYPE_2__ kvm_t ;
struct TYPE_9__ {scalar_t__ e_type; scalar_t__ e_machine; } ;
typedef  int /*<<< orphan*/  GElf_Phdr ;
typedef  TYPE_3__ GElf_Ehdr ;
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 size_t EI_CLASS ; 
 int /*<<< orphan*/  ELF_C_READ ; 
 scalar_t__ ELF_K_ELF ; 
 scalar_t__ ET_CORE ; 
 int /*<<< orphan*/  _kvm_err (TYPE_2__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * calloc (size_t,int) ; 
 int /*<<< orphan*/ * elf_begin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elf_errmsg (int /*<<< orphan*/ ) ; 
 int elf_getphdrnum (int /*<<< orphan*/ *,size_t*) ; 
 scalar_t__ elf_kind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ gelf_getclass (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gelf_getehdr (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/ * gelf_getphdr (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 

int
_kvm_read_core_phdrs(kvm_t *kd, size_t *phnump, GElf_Phdr **phdrp)
{
	GElf_Ehdr ehdr;
	GElf_Phdr *phdr;
	Elf *elf;
	size_t i, phnum;

	elf = elf_begin(kd->pmfd, ELF_C_READ, NULL);
	if (elf == NULL) {
		_kvm_err(kd, kd->program, "%s", elf_errmsg(0));
		return (-1);
	}
	if (elf_kind(elf) != ELF_K_ELF) {
		_kvm_err(kd, kd->program, "invalid core");
		goto bad;
	}
	if (gelf_getclass(elf) != kd->nlehdr.e_ident[EI_CLASS]) {
		_kvm_err(kd, kd->program, "invalid core");
		goto bad;
	}
	if (gelf_getehdr(elf, &ehdr) == NULL) {
		_kvm_err(kd, kd->program, "%s", elf_errmsg(0));
		goto bad;
	}
	if (ehdr.e_type != ET_CORE) {
		_kvm_err(kd, kd->program, "invalid core");
		goto bad;
	}
	if (ehdr.e_machine != kd->nlehdr.e_machine) {
		_kvm_err(kd, kd->program, "invalid core");
		goto bad;
	}

	if (elf_getphdrnum(elf, &phnum) == -1) {
		_kvm_err(kd, kd->program, "%s", elf_errmsg(0));
		goto bad;
	}

	phdr = calloc(phnum, sizeof(*phdr));
	if (phdr == NULL) {
		_kvm_err(kd, kd->program, "failed to allocate phdrs");
		goto bad;
	}

	for (i = 0; i < phnum; i++) {
		if (gelf_getphdr(elf, i, &phdr[i]) == NULL) {
			free(phdr);
			_kvm_err(kd, kd->program, "%s", elf_errmsg(0));
			goto bad;
		}
	}
	elf_end(elf);
	*phnump = phnum;
	*phdrp = phdr;
	return (0);

bad:
	elf_end(elf);
	return (-1);
}