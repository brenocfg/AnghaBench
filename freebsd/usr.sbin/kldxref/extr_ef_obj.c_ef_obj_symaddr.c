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
struct TYPE_5__ {scalar_t__ st_shndx; scalar_t__ st_value; } ;
struct TYPE_4__ {scalar_t__ address; TYPE_2__* ddbsymtab; scalar_t__ ddbsymcnt; } ;
typedef  TYPE_2__ Elf_Sym ;
typedef  size_t Elf_Size ;
typedef  scalar_t__ Elf_Addr ;

/* Variables and functions */
 scalar_t__ SHN_UNDEF ; 

__attribute__((used)) static Elf_Addr
ef_obj_symaddr(elf_file_t ef, Elf_Size symidx)
{
	const Elf_Sym *sym;

	if (symidx >= (size_t) ef->ddbsymcnt)
		return (0);
	sym = ef->ddbsymtab + symidx;

	if (sym->st_shndx != SHN_UNDEF)
		return (sym->st_value - (Elf_Addr)ef->address);
	return (0);
}