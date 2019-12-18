#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct module {int dummy; } ;
struct TYPE_5__ {unsigned long sh_addr; int sh_size; int sh_name; } ;
struct TYPE_4__ {int st_shndx; int st_value; int /*<<< orphan*/  st_name; } ;
typedef  TYPE_1__ Elf_Sym ;
typedef  TYPE_2__ Elf_Shdr ;

/* Variables and functions */
#define  SHN_ABS 131 
#define  SHN_COMMON 130 
#define  SHN_MIPS_SCOMMON 129 
#define  SHN_UNDEF 128 
 int /*<<< orphan*/  pr_debug (char*,char const*,int) ; 
 int /*<<< orphan*/  save_gp_address (unsigned long,unsigned long) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static void simplify_symbols(Elf_Shdr *sechdrs,
			    unsigned int symindex,
			    const char *strtab,
			    const char *secstrings,
			    unsigned int nsecs, struct module *mod)
{
	Elf_Sym *sym = (void *)sechdrs[symindex].sh_addr;
	unsigned long secbase, bssbase = 0;
	unsigned int i, n = sechdrs[symindex].sh_size / sizeof(Elf_Sym);
	int size;

	/* find the .bss section for COMMON symbols */
	for (i = 0; i < nsecs; i++) {
		if (strncmp(secstrings + sechdrs[i].sh_name, ".bss", 4) == 0) {
			bssbase = sechdrs[i].sh_addr;
			break;
		}
	}

	for (i = 1; i < n; i++) {
		switch (sym[i].st_shndx) {
		case SHN_COMMON:
			/* Allocate space for the symbol in the .bss section.
			   st_value is currently size.
			   We want it to have the address of the symbol. */

			size = sym[i].st_value;
			sym[i].st_value = bssbase;

			bssbase += size;
			break;

		case SHN_ABS:
			/* Don't need to do anything */
			break;

		case SHN_UNDEF:
			/* ret = -ENOENT; */
			break;

		case SHN_MIPS_SCOMMON:
			pr_debug("simplify_symbols: ignoring SHN_MIPS_SCOMMON symbol <%s> st_shndx %d\n",
				 strtab + sym[i].st_name, sym[i].st_shndx);
			/* .sbss section */
			break;

		default:
			secbase = sechdrs[sym[i].st_shndx].sh_addr;

			if (strncmp(strtab + sym[i].st_name, "_gp", 3) == 0)
				save_gp_address(secbase, sym[i].st_value);

			sym[i].st_value += secbase;
			break;
		}
	}
}