#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct plt_entry {int /*<<< orphan*/  adrp; } ;
struct mod_plt_sec {size_t plt_shndx; int plt_num_entries; int plt_max_entries; } ;
struct TYPE_8__ {struct mod_plt_sec init; struct mod_plt_sec core; } ;
struct module {TYPE_1__ arch; } ;
struct TYPE_11__ {scalar_t__ r_addend; } ;
struct TYPE_10__ {scalar_t__ sh_addr; } ;
struct TYPE_9__ {scalar_t__ st_value; } ;
typedef  TYPE_2__ Elf64_Sym ;
typedef  TYPE_3__ Elf64_Shdr ;
typedef  TYPE_4__ Elf64_Rela ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 struct plt_entry get_plt_entry (scalar_t__,struct plt_entry*) ; 
 int /*<<< orphan*/  in_init (struct module*,void*) ; 
 scalar_t__ is_forbidden_offset_for_adrp (int /*<<< orphan*/ *) ; 
 scalar_t__ plt_entries_equal (struct plt_entry*,struct plt_entry*) ; 

u64 module_emit_plt_entry(struct module *mod, Elf64_Shdr *sechdrs,
			  void *loc, const Elf64_Rela *rela,
			  Elf64_Sym *sym)
{
	struct mod_plt_sec *pltsec = !in_init(mod, loc) ? &mod->arch.core :
							  &mod->arch.init;
	struct plt_entry *plt = (struct plt_entry *)sechdrs[pltsec->plt_shndx].sh_addr;
	int i = pltsec->plt_num_entries;
	int j = i - 1;
	u64 val = sym->st_value + rela->r_addend;

	if (is_forbidden_offset_for_adrp(&plt[i].adrp))
		i++;

	plt[i] = get_plt_entry(val, &plt[i]);

	/*
	 * Check if the entry we just created is a duplicate. Given that the
	 * relocations are sorted, this will be the last entry we allocated.
	 * (if one exists).
	 */
	if (j >= 0 && plt_entries_equal(plt + i, plt + j))
		return (u64)&plt[j];

	pltsec->plt_num_entries += i - j;
	if (WARN_ON(pltsec->plt_num_entries > pltsec->plt_max_entries))
		return 0;

	return (u64)&plt[i];
}