#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  linker_file_t ;
typedef  TYPE_1__* elf_file_t ;
struct TYPE_2__ {scalar_t__ nchains; int /*<<< orphan*/  const* symtab; } ;
typedef  int /*<<< orphan*/  Elf_Sym ;
typedef  scalar_t__ Elf_Size ;

/* Variables and functions */

const Elf_Sym *
elf_get_sym(linker_file_t lf, Elf_Size symidx)
{
	elf_file_t ef = (elf_file_t)lf;

	if (symidx >= ef->nchains)
		return (NULL);
	return (ef->symtab + symidx);
}