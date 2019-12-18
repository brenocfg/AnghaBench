#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * unwind; } ;
struct module {TYPE_1__ arch; } ;
struct mod_unwind_map {TYPE_2__ const* txt_sec; TYPE_2__ const* unw_sec; } ;
typedef  int /*<<< orphan*/  maps ;
struct TYPE_11__ {size_t e_shstrndx; int e_shnum; } ;
struct TYPE_10__ {int sh_offset; int sh_name; int sh_flags; int /*<<< orphan*/  sh_size; scalar_t__ sh_addr; } ;
typedef  TYPE_2__ Elf_Shdr ;
typedef  TYPE_3__ Elf32_Ehdr ;

/* Variables and functions */
 size_t ARM_SEC_CORE ; 
 size_t ARM_SEC_EXIT ; 
 size_t ARM_SEC_HOT ; 
 size_t ARM_SEC_INIT ; 
 int ARM_SEC_MAX ; 
 size_t ARM_SEC_UNLIKELY ; 
 int EINVAL ; 
 int SHF_ALLOC ; 
 TYPE_2__* find_mod_section (TYPE_3__ const*,TYPE_2__ const*,char*) ; 
 int /*<<< orphan*/  fixup_pv_table (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fixup_smp (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_smp () ; 
 int /*<<< orphan*/  memset (struct mod_unwind_map*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int /*<<< orphan*/  unwind_table_add (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

int module_finalize(const Elf32_Ehdr *hdr, const Elf_Shdr *sechdrs,
		    struct module *mod)
{
	const Elf_Shdr *s = NULL;
#ifdef CONFIG_ARM_UNWIND
	const char *secstrs = (void *)hdr + sechdrs[hdr->e_shstrndx].sh_offset;
	const Elf_Shdr *sechdrs_end = sechdrs + hdr->e_shnum;
	struct mod_unwind_map maps[ARM_SEC_MAX];
	int i;

	memset(maps, 0, sizeof(maps));

	for (s = sechdrs; s < sechdrs_end; s++) {
		const char *secname = secstrs + s->sh_name;

		if (!(s->sh_flags & SHF_ALLOC))
			continue;

		if (strcmp(".ARM.exidx.init.text", secname) == 0)
			maps[ARM_SEC_INIT].unw_sec = s;
		else if (strcmp(".ARM.exidx", secname) == 0)
			maps[ARM_SEC_CORE].unw_sec = s;
		else if (strcmp(".ARM.exidx.exit.text", secname) == 0)
			maps[ARM_SEC_EXIT].unw_sec = s;
		else if (strcmp(".ARM.exidx.text.unlikely", secname) == 0)
			maps[ARM_SEC_UNLIKELY].unw_sec = s;
		else if (strcmp(".ARM.exidx.text.hot", secname) == 0)
			maps[ARM_SEC_HOT].unw_sec = s;
		else if (strcmp(".init.text", secname) == 0)
			maps[ARM_SEC_INIT].txt_sec = s;
		else if (strcmp(".text", secname) == 0)
			maps[ARM_SEC_CORE].txt_sec = s;
		else if (strcmp(".exit.text", secname) == 0)
			maps[ARM_SEC_EXIT].txt_sec = s;
		else if (strcmp(".text.unlikely", secname) == 0)
			maps[ARM_SEC_UNLIKELY].txt_sec = s;
		else if (strcmp(".text.hot", secname) == 0)
			maps[ARM_SEC_HOT].txt_sec = s;
	}

	for (i = 0; i < ARM_SEC_MAX; i++)
		if (maps[i].unw_sec && maps[i].txt_sec)
			mod->arch.unwind[i] =
				unwind_table_add(maps[i].unw_sec->sh_addr,
					         maps[i].unw_sec->sh_size,
					         maps[i].txt_sec->sh_addr,
					         maps[i].txt_sec->sh_size);
#endif
#ifdef CONFIG_ARM_PATCH_PHYS_VIRT
	s = find_mod_section(hdr, sechdrs, ".pv_table");
	if (s)
		fixup_pv_table((void *)s->sh_addr, s->sh_size);
#endif
	s = find_mod_section(hdr, sechdrs, ".alt.smp.init");
	if (s && !is_smp())
#ifdef CONFIG_SMP_ON_UP
		fixup_smp((void *)s->sh_addr, s->sh_size);
#else
		return -EINVAL;
#endif
	return 0;
}