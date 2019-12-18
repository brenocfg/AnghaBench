#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  linker_file_t ;
typedef  TYPE_4__* elf_file_t ;
struct TYPE_16__ {int /*<<< orphan*/  r_info; } ;
struct TYPE_15__ {int /*<<< orphan*/  st_info; } ;
struct TYPE_13__ {int /*<<< orphan*/  filename; } ;
struct TYPE_14__ {int nreltab; scalar_t__ ddbsymcnt; int nrelatab; TYPE_5__* ddbsymtab; TYPE_3__ lf; TYPE_2__* relatab; TYPE_1__* reltab; } ;
struct TYPE_12__ {int nrela; int /*<<< orphan*/  sec; TYPE_6__* rela; } ;
struct TYPE_11__ {int nrel; int /*<<< orphan*/  sec; TYPE_6__* rel; } ;
typedef  TYPE_5__ Elf_Sym ;
typedef  scalar_t__ Elf_Size ;
typedef  TYPE_6__ Elf_Rela ;
typedef  TYPE_6__ Elf_Rel ;
typedef  scalar_t__ Elf_Addr ;

/* Variables and functions */
 int /*<<< orphan*/  ELF_RELOC_REL ; 
 int /*<<< orphan*/  ELF_RELOC_RELA ; 
 scalar_t__ ELF_R_SYM (int /*<<< orphan*/ ) ; 
 scalar_t__ ELF_ST_BIND (int /*<<< orphan*/ ) ; 
 scalar_t__ ELF_ST_TYPE (int /*<<< orphan*/ ) ; 
 int ENOEXEC ; 
 scalar_t__ STB_LOCAL ; 
 scalar_t__ STT_GNU_IFUNC ; 
 scalar_t__ elf_is_ifunc_reloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elf_obj_lookup ; 
 int /*<<< orphan*/  elf_reloc_local (int /*<<< orphan*/ ,scalar_t__,TYPE_6__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ findbase (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_elf_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  link_elf_fix_link_set (TYPE_4__*) ; 

__attribute__((used)) static int
link_elf_reloc_local(linker_file_t lf, bool ifuncs)
{
	elf_file_t ef = (elf_file_t)lf;
	const Elf_Rel *rellim;
	const Elf_Rel *rel;
	const Elf_Rela *relalim;
	const Elf_Rela *rela;
	const Elf_Sym *sym;
	Elf_Addr base;
	int i;
	Elf_Size symidx;

	link_elf_fix_link_set(ef);

	/* Perform relocations without addend if there are any: */
	for (i = 0; i < ef->nreltab; i++) {
		rel = ef->reltab[i].rel;
		if (rel == NULL) {
			link_elf_error(ef->lf.filename, "lost a reltab");
			return (ENOEXEC);
		}
		rellim = rel + ef->reltab[i].nrel;
		base = findbase(ef, ef->reltab[i].sec);
		if (base == 0) {
			link_elf_error(ef->lf.filename, "lost base for reltab");
			return (ENOEXEC);
		}
		for ( ; rel < rellim; rel++) {
			symidx = ELF_R_SYM(rel->r_info);
			if (symidx >= ef->ddbsymcnt)
				continue;
			sym = ef->ddbsymtab + symidx;
			/* Only do local relocs */
			if (ELF_ST_BIND(sym->st_info) != STB_LOCAL)
				continue;
			if ((ELF_ST_TYPE(sym->st_info) == STT_GNU_IFUNC ||
			    elf_is_ifunc_reloc(rel->r_info)) == ifuncs)
				elf_reloc_local(lf, base, rel, ELF_RELOC_REL,
				    elf_obj_lookup);
		}
	}

	/* Perform relocations with addend if there are any: */
	for (i = 0; i < ef->nrelatab; i++) {
		rela = ef->relatab[i].rela;
		if (rela == NULL) {
			link_elf_error(ef->lf.filename, "lost a relatab!");
			return (ENOEXEC);
		}
		relalim = rela + ef->relatab[i].nrela;
		base = findbase(ef, ef->relatab[i].sec);
		if (base == 0) {
			link_elf_error(ef->lf.filename, "lost base for reltab");
			return (ENOEXEC);
		}
		for ( ; rela < relalim; rela++) {
			symidx = ELF_R_SYM(rela->r_info);
			if (symidx >= ef->ddbsymcnt)
				continue;
			sym = ef->ddbsymtab + symidx;
			/* Only do local relocs */
			if (ELF_ST_BIND(sym->st_info) != STB_LOCAL)
				continue;
			if ((ELF_ST_TYPE(sym->st_info) == STT_GNU_IFUNC ||
			    elf_is_ifunc_reloc(rela->r_info)) == ifuncs)
				elf_reloc_local(lf, base, rela, ELF_RELOC_RELA,
				    elf_obj_lookup);
		}
	}
	return (0);
}