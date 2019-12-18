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
typedef  int /*<<< orphan*/  linker_file_t ;
typedef  TYPE_1__* elf_file_t ;
struct TYPE_4__ {scalar_t__ st_shndx; scalar_t__ st_value; int st_name; int /*<<< orphan*/  st_info; } ;
struct TYPE_3__ {scalar_t__ nchains; char* strtab; scalar_t__ address; TYPE_2__* symtab; } ;
typedef  TYPE_2__ Elf_Sym ;
typedef  scalar_t__ Elf_Size ;
typedef  scalar_t__ Elf_Addr ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ELF_ST_BIND (int /*<<< orphan*/ ) ; 
 scalar_t__ SHN_UNDEF ; 
 scalar_t__ STB_LOCAL ; 
 scalar_t__ STB_WEAK ; 
 scalar_t__ elf_set_find (int /*<<< orphan*/ *,scalar_t__,scalar_t__*,scalar_t__*) ; 
 scalar_t__ linker_file_lookup_symbol (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  set_pcpu_list ; 
 int /*<<< orphan*/  set_vnet_list ; 

__attribute__((used)) static int
elf_lookup(linker_file_t lf, Elf_Size symidx, int deps, Elf_Addr *res)
{
	elf_file_t ef = (elf_file_t)lf;
	const Elf_Sym *sym;
	const char *symbol;
	Elf_Addr addr, start, base;

	/* Don't even try to lookup the symbol if the index is bogus. */
	if (symidx >= ef->nchains) {
		*res = 0;
		return (EINVAL);
	}

	sym = ef->symtab + symidx;

	/*
	 * Don't do a full lookup when the symbol is local. It may even
	 * fail because it may not be found through the hash table.
	 */
	if (ELF_ST_BIND(sym->st_info) == STB_LOCAL) {
		/* Force lookup failure when we have an insanity. */
		if (sym->st_shndx == SHN_UNDEF || sym->st_value == 0) {
			*res = 0;
			return (EINVAL);
		}
		*res = ((Elf_Addr)ef->address + sym->st_value);
		return (0);
	}

	/*
	 * XXX we can avoid doing a hash table based lookup for global
	 * symbols as well. This however is not always valid, so we'll
	 * just do it the hard way for now. Performance tweaks can
	 * always be added.
	 */

	symbol = ef->strtab + sym->st_name;

	/* Force a lookup failure if the symbol name is bogus. */
	if (*symbol == 0) {
		*res = 0;
		return (EINVAL);
	}

	addr = ((Elf_Addr)linker_file_lookup_symbol(lf, symbol, deps));
	if (addr == 0 && ELF_ST_BIND(sym->st_info) != STB_WEAK) {
		*res = 0;
		return (EINVAL);
	}

	if (elf_set_find(&set_pcpu_list, addr, &start, &base))
		addr = addr - start + base;
#ifdef VIMAGE
	else if (elf_set_find(&set_vnet_list, addr, &start, &base))
		addr = addr - start + base;
#endif
	*res = addr;
	return (0);
}