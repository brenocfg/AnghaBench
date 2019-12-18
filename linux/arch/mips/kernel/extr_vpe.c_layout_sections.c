#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ size; scalar_t__ text_size; } ;
struct module {TYPE_1__ core_layout; } ;
struct TYPE_9__ {unsigned int e_shnum; } ;
struct TYPE_8__ {unsigned long sh_entsize; unsigned long const sh_flags; } ;
typedef  TYPE_2__ Elf_Shdr ;
typedef  TYPE_3__ Elf_Ehdr ;

/* Variables and functions */
#define  ARCH_SHF_SMALL 131 
 unsigned int ARRAY_SIZE (unsigned long const**) ; 
#define  SHF_ALLOC 130 
#define  SHF_EXECINSTR 129 
#define  SHF_WRITE 128 
 unsigned long get_offset (unsigned long*,TYPE_2__*) ; 

__attribute__((used)) static void layout_sections(struct module *mod, const Elf_Ehdr *hdr,
			    Elf_Shdr *sechdrs, const char *secstrings)
{
	static unsigned long const masks[][2] = {
		/* NOTE: all executable code must be the first section
		 * in this array; otherwise modify the text_size
		 * finder in the two loops below */
		{SHF_EXECINSTR | SHF_ALLOC, ARCH_SHF_SMALL},
		{SHF_ALLOC, SHF_WRITE | ARCH_SHF_SMALL},
		{SHF_WRITE | SHF_ALLOC, ARCH_SHF_SMALL},
		{ARCH_SHF_SMALL | SHF_ALLOC, 0}
	};
	unsigned int m, i;

	for (i = 0; i < hdr->e_shnum; i++)
		sechdrs[i].sh_entsize = ~0UL;

	for (m = 0; m < ARRAY_SIZE(masks); ++m) {
		for (i = 0; i < hdr->e_shnum; ++i) {
			Elf_Shdr *s = &sechdrs[i];

			if ((s->sh_flags & masks[m][0]) != masks[m][0]
			    || (s->sh_flags & masks[m][1])
			    || s->sh_entsize != ~0UL)
				continue;
			s->sh_entsize =
				get_offset((unsigned long *)&mod->core_layout.size, s);
		}

		if (m == 0)
			mod->core_layout.text_size = mod->core_layout.size;

	}
}