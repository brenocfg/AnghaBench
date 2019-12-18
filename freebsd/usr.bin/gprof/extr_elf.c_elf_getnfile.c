#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_size; } ;
struct TYPE_10__ {int value; char const* name; } ;
typedef  TYPE_1__ nltype ;
struct TYPE_13__ {int e_shoff; int e_shnum; } ;
struct TYPE_12__ {scalar_t__ sh_type; size_t sh_link; int sh_offset; int sh_size; int sh_entsize; } ;
struct TYPE_11__ {int st_value; int st_name; } ;
typedef  TYPE_2__ Elf_Sym ;
typedef  TYPE_3__ Elf_Shdr ;
typedef  TYPE_4__ Elf_Ehdr ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ELF (TYPE_4__) ; 
 void* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PROT_READ ; 
 scalar_t__ SHT_SYMTAB ; 
 scalar_t__ calloc (scalar_t__,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 char** excludes ; 
 int fstat (int,struct stat*) ; 
 void* mmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* nl ; 
 scalar_t__ nname ; 
 TYPE_1__* npe ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int read (int,TYPE_4__*,int) ; 
 scalar_t__ wantsym (TYPE_2__ const*,char const*) ; 

int
elf_getnfile(const char *filename, char ***defaultEs)
{
    int fd;
    Elf_Ehdr h;
    struct stat s;
    void *mapbase;
    const char *base;
    const Elf_Shdr *shdrs;
    const Elf_Shdr *sh_symtab;
    const Elf_Shdr *sh_strtab;
    const char *strtab;
    const Elf_Sym *symtab;
    int symtabct;
    int i;

    if ((fd = open(filename, O_RDONLY)) == -1)
	err(1, "%s", filename);
    if (read(fd, &h, sizeof h) != sizeof h || !IS_ELF(h)) {
	close(fd);
	return -1;
    }
    if (fstat(fd, &s) == -1)
	err(1, "cannot fstat %s", filename);
    if ((mapbase = mmap(0, s.st_size, PROT_READ, MAP_SHARED, fd, 0)) ==
      MAP_FAILED)
	err(1, "cannot mmap %s", filename);
    close(fd);

    base = (const char *)mapbase;
    shdrs = (const Elf_Shdr *)(base + h.e_shoff);

    /* Find the symbol table and associated string table section. */
    for (i = 1;  i < h.e_shnum;  i++)
	if (shdrs[i].sh_type == SHT_SYMTAB)
	    break;
    if (i == h.e_shnum)
	errx(1, "%s has no symbol table", filename);
    sh_symtab = &shdrs[i];
    sh_strtab = &shdrs[sh_symtab->sh_link];

    symtab = (const Elf_Sym *)(base + sh_symtab->sh_offset);
    symtabct = sh_symtab->sh_size / sh_symtab->sh_entsize;
    strtab = (const char *)(base + sh_strtab->sh_offset);

    /* Count the symbols that we're interested in. */
    nname = 0;
    for (i = 1;  i < symtabct;  i++)
	if (wantsym(&symtab[i], strtab))
	    nname++;

    /* Allocate memory for them, plus a terminating entry. */
    if ((nl = (nltype *)calloc(nname + 1, sizeof(nltype))) == NULL)
	errx(1, "insufficient memory for symbol table");

    /* Read them in. */
    npe = nl;
    for (i = 1;  i < symtabct;  i++) {
	const Elf_Sym *sym = &symtab[i];

	if (wantsym(sym, strtab)) {
	    npe->value = sym->st_value;
	    npe->name = strtab + sym->st_name;
	    npe++;
	}
    }
    npe->value = -1;

    *defaultEs = excludes;
    return 0;
}