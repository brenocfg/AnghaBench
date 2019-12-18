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
struct elf_file {scalar_t__ address; int /*<<< orphan*/ * dynamic; int /*<<< orphan*/  modptr; } ;
typedef  struct elf_file* elf_file_t ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  Elf_Dyn ;

/* Variables and functions */
 int /*<<< orphan*/  _DYNAMIC ; 
 int /*<<< orphan*/  bzero_early (struct elf_file*,int) ; 
 int /*<<< orphan*/  elf_lookup_ifunc ; 
 int /*<<< orphan*/  elf_reloc ; 
 int /*<<< orphan*/  link_elf_preload_parse_symbols (struct elf_file*) ; 
 int /*<<< orphan*/  parse_dynamic (struct elf_file*) ; 
 int /*<<< orphan*/  relocate_file1 (struct elf_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
link_elf_ireloc(caddr_t kmdp)
{
	struct elf_file eff;
	elf_file_t ef;

	ef = &eff;

	bzero_early(ef, sizeof(*ef));

	ef->modptr = kmdp;
	ef->dynamic = (Elf_Dyn *)&_DYNAMIC;
	parse_dynamic(ef);
	ef->address = 0;
	link_elf_preload_parse_symbols(ef);
	relocate_file1(ef, elf_lookup_ifunc, elf_reloc, true);
}