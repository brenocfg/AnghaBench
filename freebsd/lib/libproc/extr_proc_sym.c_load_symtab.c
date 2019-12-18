#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_long ;
typedef  int u_int ;
struct symtab {int* index; int nsyms; int /*<<< orphan*/  stridx; int /*<<< orphan*/ * data; } ;
struct symsort_thunk {struct symtab* symtab; int /*<<< orphan*/ * e; } ;
struct TYPE_3__ {scalar_t__ sh_type; int sh_size; int sh_entsize; int /*<<< orphan*/  sh_link; } ;
typedef  TYPE_1__ GElf_Shdr ;
typedef  int /*<<< orphan*/  GElf_Ehdr ;
typedef  int /*<<< orphan*/  Elf_Scn ;
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 int* calloc (int,int) ; 
 int /*<<< orphan*/ * elf_getdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * elf_nextscn (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gelf_getehdr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gelf_getshdr (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  qsort_r (int*,int,int,struct symsort_thunk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symvalcmp ; 

__attribute__((used)) static int
load_symtab(Elf *e, struct symtab *symtab, u_long sh_type)
{
	GElf_Ehdr ehdr;
	GElf_Shdr shdr;
	struct symsort_thunk thunk;
	Elf_Scn *scn;
	u_int nsyms;

	if (gelf_getehdr(e, &ehdr) == NULL)
		return (-1);

	scn = NULL;
	while ((scn = elf_nextscn(e, scn)) != NULL) {
		(void)gelf_getshdr(scn, &shdr);
		if (shdr.sh_type == sh_type)
			break;
	}
	if (scn == NULL)
		return (-1);

	nsyms = shdr.sh_size / shdr.sh_entsize;
	if (nsyms > (1 << 20))
		return (-1);

	if ((symtab->data = elf_getdata(scn, NULL)) == NULL)
		return (-1);

	symtab->index = calloc(nsyms, sizeof(u_int));
	if (symtab->index == NULL)
		return (-1);
	for (u_int i = 0; i < nsyms; i++)
		symtab->index[i] = i;
	symtab->nsyms = nsyms;
	symtab->stridx = shdr.sh_link;

	thunk.e = e;
	thunk.symtab = symtab;
	qsort_r(symtab->index, nsyms, sizeof(u_int), &thunk, symvalcmp);

	return (0);
}