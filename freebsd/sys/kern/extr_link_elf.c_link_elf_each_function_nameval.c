#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  linker_symval_t ;
typedef  int (* linker_function_nameval_callback_t ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,void*) ;
typedef  int /*<<< orphan*/  linker_file_t ;
typedef  TYPE_1__* elf_file_t ;
typedef  int /*<<< orphan*/  c_linker_sym_t ;
struct TYPE_4__ {scalar_t__ st_value; int /*<<< orphan*/  st_info; } ;
struct TYPE_3__ {int ddbsymcnt; TYPE_2__* ddbsymtab; } ;
typedef  TYPE_2__ Elf_Sym ;

/* Variables and functions */
 scalar_t__ ELF_ST_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ STT_FUNC ; 
 scalar_t__ STT_GNU_IFUNC ; 
 int link_elf_symbol_values (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
link_elf_each_function_nameval(linker_file_t file,
    linker_function_nameval_callback_t callback, void *opaque)
{
	linker_symval_t symval;
	elf_file_t ef = (elf_file_t)file;
	const Elf_Sym* symp;
	int i, error;

	/* Exhaustive search */
	for (i = 0, symp = ef->ddbsymtab; i < ef->ddbsymcnt; i++, symp++) {
		if (symp->st_value != 0 &&
		    (ELF_ST_TYPE(symp->st_info) == STT_FUNC ||
		    ELF_ST_TYPE(symp->st_info) == STT_GNU_IFUNC)) {
			error = link_elf_symbol_values(file,
			    (c_linker_sym_t) symp, &symval);
			if (error != 0)
				return (error);
			error = callback(file, i, &symval, opaque);
			if (error != 0)
				return (error);
		}
	}
	return (0);
}