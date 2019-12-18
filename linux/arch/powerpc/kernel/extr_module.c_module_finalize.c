#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int start_opd; int end_opd; } ;
struct module {TYPE_1__ arch; } ;
struct TYPE_10__ {int /*<<< orphan*/  cpu_features; int /*<<< orphan*/  mmu_features; } ;
struct TYPE_9__ {int sh_addr; int sh_size; } ;
typedef  TYPE_2__ Elf_Shdr ;
typedef  int /*<<< orphan*/  Elf_Ehdr ;

/* Variables and functions */
 int /*<<< orphan*/  barrier_nospec_enabled ; 
 TYPE_7__* cur_cpu_spec ; 
 int /*<<< orphan*/  do_barrier_nospec_fixups_range (int /*<<< orphan*/ ,void*,void*) ; 
 int /*<<< orphan*/  do_feature_fixups (int /*<<< orphan*/ ,void*,void*) ; 
 int /*<<< orphan*/  do_lwsync_fixups (int /*<<< orphan*/ ,void*,void*) ; 
 TYPE_2__* find_section (int /*<<< orphan*/  const*,TYPE_2__ const*,char*) ; 
 int module_finalize_ftrace (struct module*,TYPE_2__ const*) ; 
 int /*<<< orphan*/  powerpc_firmware_features ; 

int module_finalize(const Elf_Ehdr *hdr,
		const Elf_Shdr *sechdrs, struct module *me)
{
	const Elf_Shdr *sect;
	int rc;

	rc = module_finalize_ftrace(me, sechdrs);
	if (rc)
		return rc;

	/* Apply feature fixups */
	sect = find_section(hdr, sechdrs, "__ftr_fixup");
	if (sect != NULL)
		do_feature_fixups(cur_cpu_spec->cpu_features,
				  (void *)sect->sh_addr,
				  (void *)sect->sh_addr + sect->sh_size);

	sect = find_section(hdr, sechdrs, "__mmu_ftr_fixup");
	if (sect != NULL)
		do_feature_fixups(cur_cpu_spec->mmu_features,
				  (void *)sect->sh_addr,
				  (void *)sect->sh_addr + sect->sh_size);

#ifdef CONFIG_PPC64
	sect = find_section(hdr, sechdrs, "__fw_ftr_fixup");
	if (sect != NULL)
		do_feature_fixups(powerpc_firmware_features,
				  (void *)sect->sh_addr,
				  (void *)sect->sh_addr + sect->sh_size);
#endif /* CONFIG_PPC64 */

#ifdef PPC64_ELF_ABI_v1
	sect = find_section(hdr, sechdrs, ".opd");
	if (sect != NULL) {
		me->arch.start_opd = sect->sh_addr;
		me->arch.end_opd = sect->sh_addr + sect->sh_size;
	}
#endif /* PPC64_ELF_ABI_v1 */

#ifdef CONFIG_PPC_BARRIER_NOSPEC
	sect = find_section(hdr, sechdrs, "__spec_barrier_fixup");
	if (sect != NULL)
		do_barrier_nospec_fixups_range(barrier_nospec_enabled,
				  (void *)sect->sh_addr,
				  (void *)sect->sh_addr + sect->sh_size);
#endif /* CONFIG_PPC_BARRIER_NOSPEC */

	sect = find_section(hdr, sechdrs, "__lwsync_fixup");
	if (sect != NULL)
		do_lwsync_fixups(cur_cpu_spec->cpu_features,
				 (void *)sect->sh_addr,
				 (void *)sect->sh_addr + sect->sh_size);

	return 0;
}