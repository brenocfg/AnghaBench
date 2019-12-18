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
typedef  int u_int64_t ;
typedef  int /*<<< orphan*/  Elf32_Ehdr ;

/* Variables and functions */
 int /*<<< orphan*/  SH_ADDRALIGN ; 
 int /*<<< orphan*/  SH_OFFSET ; 
 int /*<<< orphan*/  SH_SIZE ; 
 int elf_get_addr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int elf_get_off (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int elf_get_size (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  out ; 

__attribute__((used)) static void
elf_print_got(Elf32_Ehdr *e, void *sh)
{
	u_int64_t offset;
	u_int64_t addralign;
	u_int64_t size;
	u_int64_t addr;
	void *v;
	int i;

	offset = elf_get_off(e, sh, SH_OFFSET);
	addralign = elf_get_size(e, sh, SH_ADDRALIGN);
	size = elf_get_size(e, sh, SH_SIZE);
	v = (char *)e + offset;
	fprintf(out, "\nglobal offset table:\n");
	for (i = 0; (u_int64_t)i < size / addralign; i++) {
		addr = elf_get_addr(e, (char *)v + i * addralign, 0);
		fprintf(out, "\n");
		fprintf(out, "entry: %d\n", i);
		fprintf(out, "\t%#jx\n", addr);
	}
}