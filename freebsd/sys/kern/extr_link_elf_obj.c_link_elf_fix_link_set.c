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
typedef  int /*<<< orphan*/  stopn ;
typedef  int /*<<< orphan*/  startn ;
typedef  TYPE_2__* elf_file_t ;
struct TYPE_7__ {int st_shndx; int st_name; scalar_t__ st_value; } ;
struct TYPE_6__ {int ddbsymcnt; char* ddbstrtab; int nprogtab; TYPE_1__* progtab; TYPE_3__* ddbsymtab; } ;
struct TYPE_5__ {scalar_t__ size; scalar_t__ addr; int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ Elf_Sym ;
typedef  int Elf_Size ;
typedef  scalar_t__ Elf_Addr ;

/* Variables and functions */
 int SHN_UNDEF ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 

__attribute__((used)) static void
link_elf_fix_link_set(elf_file_t ef)
{
	static const char startn[] = "__start_";
	static const char stopn[] = "__stop_";
	Elf_Sym *sym;
	const char *sym_name, *linkset_name;
	Elf_Addr startp, stopp;
	Elf_Size symidx;
	int start, i;

	startp = stopp = 0;
	for (symidx = 1 /* zero entry is special */;
		symidx < ef->ddbsymcnt; symidx++) {
		sym = ef->ddbsymtab + symidx;
		if (sym->st_shndx != SHN_UNDEF)
			continue;

		sym_name = ef->ddbstrtab + sym->st_name;
		if (strncmp(sym_name, startn, sizeof(startn) - 1) == 0) {
			start = 1;
			linkset_name = sym_name + sizeof(startn) - 1;
		}
		else if (strncmp(sym_name, stopn, sizeof(stopn) - 1) == 0) {
			start = 0;
			linkset_name = sym_name + sizeof(stopn) - 1;
		}
		else
			continue;

		for (i = 0; i < ef->nprogtab; i++) {
			if (strcmp(ef->progtab[i].name, linkset_name) == 0) {
				startp = (Elf_Addr)ef->progtab[i].addr;
				stopp = (Elf_Addr)(startp + ef->progtab[i].size);
				break;
			}
		}
		if (i == ef->nprogtab)
			continue;

		sym->st_value = start ? startp : stopp;
		sym->st_shndx = i;
	}
}