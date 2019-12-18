#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned int stubs_section; unsigned int toc_section; } ;
struct module {TYPE_1__ arch; int /*<<< orphan*/  name; } ;
struct TYPE_10__ {unsigned int e_shnum; } ;
struct TYPE_9__ {int sh_name; int sh_addralign; int sh_offset; int sh_size; scalar_t__ sh_type; size_t sh_link; } ;
typedef  int /*<<< orphan*/  Elf64_Sym ;
typedef  TYPE_2__ Elf64_Shdr ;
typedef  TYPE_3__ Elf64_Ehdr ;

/* Variables and functions */
 int ENOEXEC ; 
 scalar_t__ SHT_SYMTAB ; 
 int /*<<< orphan*/  dedotify (void*,int,void*) ; 
 int /*<<< orphan*/  dedotify_versions (void*,int) ; 
 int get_stubs_size (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strstr (char*,char*) ; 

int module_frob_arch_sections(Elf64_Ehdr *hdr,
			      Elf64_Shdr *sechdrs,
			      char *secstrings,
			      struct module *me)
{
	unsigned int i;

	/* Find .toc and .stubs sections, symtab and strtab */
	for (i = 1; i < hdr->e_shnum; i++) {
		char *p;
		if (strcmp(secstrings + sechdrs[i].sh_name, ".stubs") == 0)
			me->arch.stubs_section = i;
		else if (strcmp(secstrings + sechdrs[i].sh_name, ".toc") == 0) {
			me->arch.toc_section = i;
			if (sechdrs[i].sh_addralign < 8)
				sechdrs[i].sh_addralign = 8;
		}
		else if (strcmp(secstrings+sechdrs[i].sh_name,"__versions")==0)
			dedotify_versions((void *)hdr + sechdrs[i].sh_offset,
					  sechdrs[i].sh_size);

		/* We don't handle .init for the moment: rename to _init */
		while ((p = strstr(secstrings + sechdrs[i].sh_name, ".init")))
			p[0] = '_';

		if (sechdrs[i].sh_type == SHT_SYMTAB)
			dedotify((void *)hdr + sechdrs[i].sh_offset,
				 sechdrs[i].sh_size / sizeof(Elf64_Sym),
				 (void *)hdr
				 + sechdrs[sechdrs[i].sh_link].sh_offset);
	}

	if (!me->arch.stubs_section) {
		pr_err("%s: doesn't contain .stubs.\n", me->name);
		return -ENOEXEC;
	}

	/* If we don't have a .toc, just use .stubs.  We need to set r2
	   to some reasonable value in case the module calls out to
	   other functions via a stub, or if a function pointer escapes
	   the module by some means.  */
	if (!me->arch.toc_section)
		me->arch.toc_section = me->arch.stubs_section;

	/* Override the stubs size */
	sechdrs[me->arch.stubs_section].sh_size = get_stubs_size(hdr, sechdrs);
	return 0;
}