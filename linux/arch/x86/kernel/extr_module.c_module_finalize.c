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
struct module {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {size_t e_shstrndx; int e_shnum; } ;
struct TYPE_5__ {int sh_offset; int sh_name; int sh_size; scalar_t__ sh_addr; } ;
typedef  TYPE_1__ Elf_Shdr ;
typedef  TYPE_2__ Elf_Ehdr ;

/* Variables and functions */
 int /*<<< orphan*/  alternatives_smp_module_add (struct module*,int /*<<< orphan*/ ,void*,void*,void*,void*) ; 
 int /*<<< orphan*/  apply_alternatives (void*,void*) ; 
 int /*<<< orphan*/  apply_paravirt (void*,void*) ; 
 int /*<<< orphan*/  jump_label_apply_nops (struct module*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  unwind_module_init (struct module*,void*,int,void*,int) ; 

int module_finalize(const Elf_Ehdr *hdr,
		    const Elf_Shdr *sechdrs,
		    struct module *me)
{
	const Elf_Shdr *s, *text = NULL, *alt = NULL, *locks = NULL,
		*para = NULL, *orc = NULL, *orc_ip = NULL;
	char *secstrings = (void *)hdr + sechdrs[hdr->e_shstrndx].sh_offset;

	for (s = sechdrs; s < sechdrs + hdr->e_shnum; s++) {
		if (!strcmp(".text", secstrings + s->sh_name))
			text = s;
		if (!strcmp(".altinstructions", secstrings + s->sh_name))
			alt = s;
		if (!strcmp(".smp_locks", secstrings + s->sh_name))
			locks = s;
		if (!strcmp(".parainstructions", secstrings + s->sh_name))
			para = s;
		if (!strcmp(".orc_unwind", secstrings + s->sh_name))
			orc = s;
		if (!strcmp(".orc_unwind_ip", secstrings + s->sh_name))
			orc_ip = s;
	}

	if (alt) {
		/* patch .altinstructions */
		void *aseg = (void *)alt->sh_addr;
		apply_alternatives(aseg, aseg + alt->sh_size);
	}
	if (locks && text) {
		void *lseg = (void *)locks->sh_addr;
		void *tseg = (void *)text->sh_addr;
		alternatives_smp_module_add(me, me->name,
					    lseg, lseg + locks->sh_size,
					    tseg, tseg + text->sh_size);
	}

	if (para) {
		void *pseg = (void *)para->sh_addr;
		apply_paravirt(pseg, pseg + para->sh_size);
	}

	/* make jump label nops */
	jump_label_apply_nops(me);

	if (orc && orc_ip)
		unwind_module_init(me, (void *)orc_ip->sh_addr, orc_ip->sh_size,
				   (void *)orc->sh_addr, orc->sh_size);

	return 0;
}