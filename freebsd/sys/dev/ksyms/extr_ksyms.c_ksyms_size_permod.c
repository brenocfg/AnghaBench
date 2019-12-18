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
struct tsizes {long ts_symsz; int /*<<< orphan*/  ts_strsz; } ;
typedef  int /*<<< orphan*/  linker_file_t ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  Elf_Sym ;

/* Variables and functions */
 scalar_t__ LINKER_STRTAB_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 long LINKER_SYMTAB_GET (int /*<<< orphan*/ ,int /*<<< orphan*/  const**) ; 

__attribute__((used)) static int
ksyms_size_permod(linker_file_t lf, void *arg)
{
	struct tsizes *ts;
	const Elf_Sym *symtab;
	caddr_t strtab;
	long syms;

	ts = arg;

	syms = LINKER_SYMTAB_GET(lf, &symtab);
	ts->ts_symsz += syms * sizeof(Elf_Sym);
	ts->ts_strsz += LINKER_STRTAB_GET(lf, &strtab);

	return (0);
}