#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  sym ;
struct preloaded_file {int dummy; } ;
struct file_metadata {scalar_t__ md_data; } ;
struct TYPE_7__ {int e_shnum; } ;
struct TYPE_6__ {scalar_t__ sh_type; scalar_t__ sh_addr; int sh_size; } ;
struct TYPE_5__ {scalar_t__ st_name; scalar_t__ st_value; int /*<<< orphan*/  st_info; } ;
typedef  TYPE_1__ Elf_Sym ;
typedef  TYPE_2__ Elf_Shdr ;
typedef  TYPE_3__ Elf_Ehdr ;

/* Variables and functions */
 int /*<<< orphan*/  COPYOUT (scalar_t__,TYPE_1__*,int) ; 
 scalar_t__ ELF_ST_BIND (int /*<<< orphan*/ ) ; 
 scalar_t__ ELF_ST_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FDT_STATIC_DTB_SYMBOL ; 
 int /*<<< orphan*/  MODINFOMD_ELFHDR ; 
 int /*<<< orphan*/  MODINFOMD_SHDR ; 
 scalar_t__ SHT_DYNSYM ; 
 scalar_t__ SHT_STRTAB ; 
 scalar_t__ STB_GLOBAL ; 
 scalar_t__ STT_NOTYPE ; 
 scalar_t__ __elfN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugf (char*) ; 
 struct preloaded_file* file_findfile (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct file_metadata* file_findmetadata (struct preloaded_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  relocation_offset ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 char* strdupout (scalar_t__) ; 

__attribute__((used)) static vm_offset_t
fdt_find_static_dtb()
{
	Elf_Ehdr *ehdr;
	Elf_Shdr *shdr;
	Elf_Sym sym;
	vm_offset_t strtab, symtab, fdt_start;
	uint64_t offs;
	struct preloaded_file *kfp;
	struct file_metadata *md;
	char *strp;
	int i, sym_count;

	debugf("fdt_find_static_dtb()\n");

	sym_count = symtab = strtab = 0;
	strp = NULL;

	offs = __elfN(relocation_offset);

	kfp = file_findfile(NULL, NULL);
	if (kfp == NULL)
		return (0);

	/* Locate the dynamic symbols and strtab. */
	md = file_findmetadata(kfp, MODINFOMD_ELFHDR);
	if (md == NULL)
		return (0);
	ehdr = (Elf_Ehdr *)md->md_data;

	md = file_findmetadata(kfp, MODINFOMD_SHDR);
	if (md == NULL)
		return (0);
	shdr = (Elf_Shdr *)md->md_data;

	for (i = 0; i < ehdr->e_shnum; ++i) {
		if (shdr[i].sh_type == SHT_DYNSYM && symtab == 0) {
			symtab = shdr[i].sh_addr + offs;
			sym_count = shdr[i].sh_size / sizeof(Elf_Sym);
		} else if (shdr[i].sh_type == SHT_STRTAB && strtab == 0) {
			strtab = shdr[i].sh_addr + offs;
		}
	}

	/*
	 * The most efficient way to find a symbol would be to calculate a
	 * hash, find proper bucket and chain, and thus find a symbol.
	 * However, that would involve code duplication (e.g. for hash
	 * function). So we're using simpler and a bit slower way: we're
	 * iterating through symbols, searching for the one which name is
	 * 'equal' to 'fdt_static_dtb'. To speed up the process a little bit,
	 * we are eliminating symbols type of which is not STT_NOTYPE, or(and)
	 * those which binding attribute is not STB_GLOBAL.
	 */
	fdt_start = 0;
	while (sym_count > 0 && fdt_start == 0) {
		COPYOUT(symtab, &sym, sizeof(sym));
		symtab += sizeof(sym);
		--sym_count;
		if (ELF_ST_BIND(sym.st_info) != STB_GLOBAL ||
		    ELF_ST_TYPE(sym.st_info) != STT_NOTYPE)
			continue;
		strp = strdupout(strtab + sym.st_name);
		if (strcmp(strp, FDT_STATIC_DTB_SYMBOL) == 0)
			fdt_start = (vm_offset_t)sym.st_value + offs;
		free(strp);
	}
	return (fdt_start);
}