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
struct TYPE_2__ {long ddbsymcnt; int /*<<< orphan*/ * ddbsymtab; } ;
typedef  int /*<<< orphan*/  Elf_Sym ;

/* Variables and functions */

__attribute__((used)) static long
link_elf_symtab_get(linker_file_t lf, const Elf_Sym **symtab)
{
	elf_file_t ef = (elf_file_t)lf;

	*symtab = ef->ddbsymtab;

	if (*symtab == NULL)
		return (0);

	return (ef->ddbsymcnt);
}