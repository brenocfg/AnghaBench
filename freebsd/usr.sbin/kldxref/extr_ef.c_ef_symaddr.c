#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* elf_file_t ;
struct TYPE_5__ {scalar_t__ st_shndx; scalar_t__ st_value; int /*<<< orphan*/  st_info; } ;
struct TYPE_4__ {scalar_t__ ef_nchains; TYPE_2__* ef_symtab; } ;
typedef  TYPE_2__ Elf_Sym ;
typedef  scalar_t__ Elf_Size ;
typedef  scalar_t__ Elf_Addr ;

/* Variables and functions */
 scalar_t__ ELF_ST_BIND (int /*<<< orphan*/ ) ; 
 scalar_t__ SHN_UNDEF ; 
 scalar_t__ STB_LOCAL ; 

__attribute__((used)) static Elf_Addr
ef_symaddr(elf_file_t ef, Elf_Size symidx)
{
	const Elf_Sym *sym;

	if (symidx >= ef->ef_nchains)
		return (0);
	sym = ef->ef_symtab + symidx;

	if (ELF_ST_BIND(sym->st_info) == STB_LOCAL &&
	    sym->st_shndx != SHN_UNDEF && sym->st_value != 0)
		return (sym->st_value);
	return (0);
}