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
struct TYPE_4__ {int unw_sec_idx; void* unw_info; } ;
struct module {TYPE_1__ arch; } ;
struct TYPE_5__ {int /*<<< orphan*/  sh_size; scalar_t__ sh_addr; } ;
typedef  TYPE_2__ Elf_Shdr ;
typedef  int /*<<< orphan*/  Elf32_Ehdr ;

/* Variables and functions */
 void* unwind_add_table (struct module*,void*,int /*<<< orphan*/ ) ; 

int module_finalize(const Elf32_Ehdr *hdr, const Elf_Shdr *sechdrs,
		    struct module *mod)
{
#ifdef CONFIG_ARC_DW2_UNWIND
	void *unw;
	int unwsec = mod->arch.unw_sec_idx;

	if (unwsec) {
		unw = unwind_add_table(mod, (void *)sechdrs[unwsec].sh_addr,
				       sechdrs[unwsec].sh_size);
		mod->arch.unw_info = unw;
	}
#endif
	return 0;
}