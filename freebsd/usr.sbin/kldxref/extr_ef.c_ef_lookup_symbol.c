#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* elf_file_t ;
struct TYPE_6__ {scalar_t__ st_name; scalar_t__ st_shndx; scalar_t__ st_value; int /*<<< orphan*/  st_info; } ;
struct TYPE_5__ {unsigned long* ef_buckets; unsigned long ef_nbuckets; unsigned long ef_nchains; char* ef_strtab; unsigned long* ef_chains; int /*<<< orphan*/  ef_name; TYPE_2__* ef_symtab; } ;
typedef  TYPE_2__ Elf_Sym ;

/* Variables and functions */
 scalar_t__ ELF_ST_TYPE (int /*<<< orphan*/ ) ; 
 int ENOENT ; 
 scalar_t__ SHN_UNDEF ; 
 unsigned long STN_UNDEF ; 
 scalar_t__ STT_FUNC ; 
 unsigned long elf_hash (char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ef_lookup_symbol(elf_file_t ef, const char *name, Elf_Sym **sym)
{
	unsigned long hash, symnum;
	Elf_Sym *symp;
	char *strp;

	/* First, search hashed global symbols */
	hash = elf_hash(name);
	symnum = ef->ef_buckets[hash % ef->ef_nbuckets];

	while (symnum != STN_UNDEF) {
		if (symnum >= ef->ef_nchains) {
			warnx("ef_lookup_symbol: file %s have corrupted symbol table\n",
			    ef->ef_name);
			return (ENOENT);
		}

		symp = ef->ef_symtab + symnum;
		if (symp->st_name == 0) {
			warnx("ef_lookup_symbol: file %s have corrupted symbol table\n",
			    ef->ef_name);
			return (ENOENT);
		}

		strp = ef->ef_strtab + symp->st_name;

		if (strcmp(name, strp) == 0) {
			if (symp->st_shndx != SHN_UNDEF ||
			    (symp->st_value != 0 &&
				ELF_ST_TYPE(symp->st_info) == STT_FUNC)) {
				*sym = symp;
				return (0);
			} else
				return (ENOENT);
		}

		symnum = ef->ef_chains[symnum];
	}

	return (ENOENT);
}