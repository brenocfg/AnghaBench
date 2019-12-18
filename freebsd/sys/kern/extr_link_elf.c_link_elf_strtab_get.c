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
typedef  int /*<<< orphan*/ * caddr_t ;
struct TYPE_2__ {long ddbstrcnt; int /*<<< orphan*/ * ddbstrtab; } ;

/* Variables and functions */

__attribute__((used)) static long
link_elf_strtab_get(linker_file_t lf, caddr_t *strtab)
{
	elf_file_t ef = (elf_file_t)lf;

	*strtab = ef->ddbstrtab;

	if (*strtab == NULL)
		return (0);

	return (ef->ddbstrcnt);
}