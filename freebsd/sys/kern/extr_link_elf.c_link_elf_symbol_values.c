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
struct TYPE_5__ {int value; int /*<<< orphan*/  size; scalar_t__ name; } ;
typedef  TYPE_1__ linker_symval_t ;
typedef  scalar_t__ linker_file_t ;
typedef  TYPE_2__* elf_file_t ;
typedef  int caddr_t ;
typedef  scalar_t__ c_linker_sym_t ;
struct TYPE_7__ {int st_value; int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_info; scalar_t__ st_name; } ;
struct TYPE_6__ {int nchains; int ddbsymcnt; scalar_t__ address; scalar_t__ ddbstrtab; TYPE_3__ const* ddbsymtab; TYPE_3__ const* symtab; scalar_t__ strtab; } ;
typedef  TYPE_3__ Elf_Sym ;

/* Variables and functions */
 scalar_t__ ELF_ST_TYPE (int /*<<< orphan*/ ) ; 
 int ENOENT ; 
 scalar_t__ STT_GNU_IFUNC ; 
 int stub1 () ; 
 int stub2 () ; 

__attribute__((used)) static int
link_elf_symbol_values(linker_file_t lf, c_linker_sym_t sym,
    linker_symval_t *symval)
{
	elf_file_t ef;
	const Elf_Sym *es;
	caddr_t val;

	ef = (elf_file_t)lf;
	es = (const Elf_Sym *)sym;
	if (es >= ef->symtab && es < (ef->symtab + ef->nchains)) {
		symval->name = ef->strtab + es->st_name;
		val = (caddr_t)ef->address + es->st_value;
		if (ELF_ST_TYPE(es->st_info) == STT_GNU_IFUNC)
			val = ((caddr_t (*)(void))val)();
		symval->value = val;
		symval->size = es->st_size;
		return (0);
	}
	if (ef->symtab == ef->ddbsymtab)
		return (ENOENT);
	if (es >= ef->ddbsymtab && es < (ef->ddbsymtab + ef->ddbsymcnt)) {
		symval->name = ef->ddbstrtab + es->st_name;
		val = (caddr_t)ef->address + es->st_value;
		if (ELF_ST_TYPE(es->st_info) == STT_GNU_IFUNC)
			val = ((caddr_t (*)(void))val)();
		symval->value = val;
		symval->size = es->st_size;
		return (0);
	}
	return (ENOENT);
}