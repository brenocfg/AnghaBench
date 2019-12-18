#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u_int64_t ;
typedef  scalar_t__ intmax_t ;
typedef  int /*<<< orphan*/  Elf32_Ehdr ;

/* Variables and functions */
 int /*<<< orphan*/  E_MACHINE ; 
 int /*<<< orphan*/  E_SHENTSIZE ; 
 int /*<<< orphan*/  SH_ADDR ; 
 int /*<<< orphan*/  SH_ADDRALIGN ; 
 int /*<<< orphan*/  SH_ENTSIZE ; 
 int /*<<< orphan*/  SH_FLAGS ; 
 int /*<<< orphan*/  SH_INFO ; 
 int /*<<< orphan*/  SH_LINK ; 
 int /*<<< orphan*/  SH_NAME ; 
 int /*<<< orphan*/  SH_OFFSET ; 
 int /*<<< orphan*/  SH_SIZE ; 
 int /*<<< orphan*/  SH_TYPE ; 
 scalar_t__ elf_get_addr (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ elf_get_off (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ elf_get_quarter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ elf_get_shnum (int /*<<< orphan*/ *,void*) ; 
 scalar_t__ elf_get_size (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ elf_get_word (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  out ; 
 char** sh_flags ; 
 char* sh_types (scalar_t__,scalar_t__) ; 
 scalar_t__ shstrtab ; 

__attribute__((used)) static void
elf_print_shdr(Elf32_Ehdr *e, void *sh)
{
	u_int64_t shentsize;
	u_int64_t shnum;
	u_int64_t name;
	u_int64_t type;
	u_int64_t flags;
	u_int64_t addr;
	u_int64_t offset;
	u_int64_t size;
	u_int64_t shlink;
	u_int64_t info;
	u_int64_t addralign;
	u_int64_t entsize;
	u_int64_t machine;
	void *v;
	int i;

	if (sh == NULL) {
		fprintf(out, "\nNo section headers\n");
		return;
	}

	machine = elf_get_quarter(e, e, E_MACHINE);
	shentsize = elf_get_quarter(e, e, E_SHENTSIZE);
	shnum = elf_get_shnum(e, sh);
	fprintf(out, "\nsection header:\n");
	for (i = 0; (u_int64_t)i < shnum; i++) {
		v = (char *)sh + i * shentsize;
		name = elf_get_word(e, v, SH_NAME);
		type = elf_get_word(e, v, SH_TYPE);
		flags = elf_get_word(e, v, SH_FLAGS);
		addr = elf_get_addr(e, v, SH_ADDR);
		offset = elf_get_off(e, v, SH_OFFSET);
		size = elf_get_size(e, v, SH_SIZE);
		shlink = elf_get_word(e, v, SH_LINK);
		info = elf_get_word(e, v, SH_INFO);
		addralign = elf_get_size(e, v, SH_ADDRALIGN);
		entsize = elf_get_size(e, v, SH_ENTSIZE);
		fprintf(out, "\n");
		fprintf(out, "entry: %d\n", i);
		fprintf(out, "\tsh_name: %s\n", shstrtab + name);
		fprintf(out, "\tsh_type: %s\n", sh_types(machine, type));
		fprintf(out, "\tsh_flags: %s\n", sh_flags[flags & 0x7]);
		fprintf(out, "\tsh_addr: %#jx\n", addr);
		fprintf(out, "\tsh_offset: %jd\n", (intmax_t)offset);
		fprintf(out, "\tsh_size: %jd\n", (intmax_t)size);
		fprintf(out, "\tsh_link: %jd\n", (intmax_t)shlink);
		fprintf(out, "\tsh_info: %jd\n", (intmax_t)info);
		fprintf(out, "\tsh_addralign: %jd\n", (intmax_t)addralign);
		fprintf(out, "\tsh_entsize: %jd\n", (intmax_t)entsize);
	}
}