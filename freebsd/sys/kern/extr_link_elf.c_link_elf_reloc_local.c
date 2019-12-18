#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  linker_file_t ;
typedef  TYPE_1__* elf_file_t ;
struct TYPE_2__ {int relsize; int relasize; scalar_t__ address; int /*<<< orphan*/ * rela; int /*<<< orphan*/ * rel; } ;
typedef  int /*<<< orphan*/  Elf_Rela ;
typedef  int /*<<< orphan*/  Elf_Rel ;
typedef  int /*<<< orphan*/  Elf_Addr ;

/* Variables and functions */
 int /*<<< orphan*/  ELF_RELOC_REL ; 
 int /*<<< orphan*/  ELF_RELOC_RELA ; 
 int /*<<< orphan*/  elf_lookup ; 
 int /*<<< orphan*/  elf_reloc_local (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
link_elf_reloc_local(linker_file_t lf)
{
	const Elf_Rel *rellim;
	const Elf_Rel *rel;
	const Elf_Rela *relalim;
	const Elf_Rela *rela;
	elf_file_t ef = (elf_file_t)lf;

	/* Perform relocations without addend if there are any: */
	if ((rel = ef->rel) != NULL) {
		rellim = (const Elf_Rel *)((const char *)ef->rel + ef->relsize);
		while (rel < rellim) {
			elf_reloc_local(lf, (Elf_Addr)ef->address, rel,
			    ELF_RELOC_REL, elf_lookup);
			rel++;
		}
	}

	/* Perform relocations with addend if there are any: */
	if ((rela = ef->rela) != NULL) {
		relalim = (const Elf_Rela *)
		    ((const char *)ef->rela + ef->relasize);
		while (rela < relalim) {
			elf_reloc_local(lf, (Elf_Addr)ef->address, rela,
			    ELF_RELOC_RELA, elf_lookup);
			rela++;
		}
	}
}