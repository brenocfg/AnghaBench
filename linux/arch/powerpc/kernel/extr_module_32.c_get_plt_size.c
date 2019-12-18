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
struct ppc_plt_entry {int dummy; } ;
struct TYPE_6__ {unsigned int e_shnum; } ;
struct TYPE_5__ {int sh_name; scalar_t__ sh_type; int sh_offset; int sh_size; } ;
typedef  TYPE_1__ Elf32_Shdr ;
typedef  int /*<<< orphan*/  Elf32_Rela ;
typedef  TYPE_2__ Elf32_Ehdr ;

/* Variables and functions */
 scalar_t__ SHT_RELA ; 
 int count_relocs (void*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,void*,...) ; 
 int /*<<< orphan*/  relacmp ; 
 int /*<<< orphan*/  relaswap ; 
 int /*<<< orphan*/  sort (void*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strstr (char const*,char*) ; 

__attribute__((used)) static unsigned long get_plt_size(const Elf32_Ehdr *hdr,
				  const Elf32_Shdr *sechdrs,
				  const char *secstrings,
				  int is_init)
{
	unsigned long ret = 0;
	unsigned i;

	/* Everything marked ALLOC (this includes the exported
           symbols) */
	for (i = 1; i < hdr->e_shnum; i++) {
		/* If it's called *.init*, and we're not init, we're
                   not interested */
		if ((strstr(secstrings + sechdrs[i].sh_name, ".init") != NULL)
		    != is_init)
			continue;

		/* We don't want to look at debug sections. */
		if (strstr(secstrings + sechdrs[i].sh_name, ".debug"))
			continue;

		if (sechdrs[i].sh_type == SHT_RELA) {
			pr_debug("Found relocations in section %u\n", i);
			pr_debug("Ptr: %p.  Number: %u\n",
			       (void *)hdr + sechdrs[i].sh_offset,
			       sechdrs[i].sh_size / sizeof(Elf32_Rela));

			/* Sort the relocation information based on a symbol and
			 * addend key. This is a stable O(n*log n) complexity
			 * alogrithm but it will reduce the complexity of
			 * count_relocs() to linear complexity O(n)
			 */
			sort((void *)hdr + sechdrs[i].sh_offset,
			     sechdrs[i].sh_size / sizeof(Elf32_Rela),
			     sizeof(Elf32_Rela), relacmp, relaswap);

			ret += count_relocs((void *)hdr
					     + sechdrs[i].sh_offset,
					     sechdrs[i].sh_size
					     / sizeof(Elf32_Rela))
				* sizeof(struct ppc_plt_entry);
		}
	}

	return ret;
}