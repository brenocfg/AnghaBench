#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct symtab {int nsyms; int /*<<< orphan*/  stridx; int /*<<< orphan*/ * index; int /*<<< orphan*/ * data; } ;
struct TYPE_4__ {uintptr_t st_value; uintptr_t st_size; int /*<<< orphan*/  st_name; } ;
typedef  TYPE_1__ GElf_Sym ;
typedef  int /*<<< orphan*/  Elf_Data ;
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 int ENOENT ; 
 char* elf_strptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gelf_getsym (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int
lookup_symbol_by_addr(Elf *e, struct symtab *symtab, uintptr_t addr,
    const char **namep, GElf_Sym *symp)
{
	GElf_Sym sym;
	Elf_Data *data;
	const char *s;
	u_int i, min, max, mid;

	if (symtab->nsyms == 0)
		return (ENOENT);

	data = symtab->data;
	min = 0;
	max = symtab->nsyms - 1;

	while (min <= max) {
		mid = (max + min) / 2;
		(void)gelf_getsym(data, symtab->index[mid], &sym);
		if (addr >= sym.st_value && addr < sym.st_value + sym.st_size)
			break;

		if (addr < sym.st_value)
			max = mid - 1;
		else
			min = mid + 1;
	}
	if (min > max)
		return (ENOENT);

	/*
	 * Advance until we find the matching symbol with largest index.
	 */
	for (i = mid; i < symtab->nsyms; i++) {
		(void)gelf_getsym(data, symtab->index[i], &sym);
		if (addr < sym.st_value || addr >= sym.st_value + sym.st_size)
			break;
	}
	(void)gelf_getsym(data, symtab->index[i - 1], symp);
	s = elf_strptr(e, symtab->stridx, symp->st_name);
	if (s != NULL && namep != NULL)
		*namep = s;
	return (0);
}