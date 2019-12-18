#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct pmcstat_symbol {scalar_t__ ps_start; scalar_t__ ps_end; int /*<<< orphan*/  ps_name; } ;
struct pmcstat_image {size_t pi_symcount; scalar_t__ pi_vaddr; struct pmcstat_symbol* pi_symbols; } ;
struct TYPE_7__ {size_t sh_size; size_t sh_entsize; int /*<<< orphan*/  sh_link; } ;
struct TYPE_6__ {scalar_t__ st_shndx; scalar_t__ st_value; scalar_t__ st_size; int /*<<< orphan*/  st_name; int /*<<< orphan*/  st_info; } ;
typedef  TYPE_1__ GElf_Sym ;
typedef  TYPE_2__ GElf_Shdr ;
typedef  int /*<<< orphan*/  Elf_Scn ;
typedef  int /*<<< orphan*/  Elf_Data ;
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 scalar_t__ GELF_ST_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ STN_UNDEF ; 
 scalar_t__ STT_FUNC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * elf_getdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* elf_strptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* gelf_getsym (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int /*<<< orphan*/  pmcstat_string_intern (char*) ; 
 int /*<<< orphan*/  pmcstat_symbol_compare ; 
 scalar_t__ pmcstat_symbol_search (struct pmcstat_image*,scalar_t__) ; 
 int /*<<< orphan*/  qsort (struct pmcstat_symbol*,size_t,int,int /*<<< orphan*/ ) ; 
 void* reallocarray (struct pmcstat_symbol*,size_t,int) ; 

void
pmcstat_image_add_symbols(struct pmcstat_image *image, Elf *e,
    Elf_Scn *scn, GElf_Shdr *sh)
{
	int firsttime;
	size_t n, newsyms, nshsyms, nfuncsyms;
	struct pmcstat_symbol *symptr;
	char *fnname;
	GElf_Sym sym;
	Elf_Data *data;

	if ((data = elf_getdata(scn, NULL)) == NULL)
		return;

	/*
	 * Determine the number of functions named in this
	 * section.
	 */

	nshsyms = sh->sh_size / sh->sh_entsize;
	for (n = nfuncsyms = 0; n < nshsyms; n++) {
		if (gelf_getsym(data, (int) n, &sym) != &sym)
			return;
		if (GELF_ST_TYPE(sym.st_info) == STT_FUNC)
			nfuncsyms++;
	}

	if (nfuncsyms == 0)
		return;

	/*
	 * Allocate space for the new entries.
	 */
	firsttime = image->pi_symbols == NULL;
	symptr = reallocarray(image->pi_symbols,
	    image->pi_symcount + nfuncsyms, sizeof(*symptr));
	if (symptr == image->pi_symbols) /* realloc() failed. */
		return;
	image->pi_symbols = symptr;

	/*
	 * Append new symbols to the end of the current table.
	 */
	symptr += image->pi_symcount;

	for (n = newsyms = 0; n < nshsyms; n++) {
		if (gelf_getsym(data, (int) n, &sym) != &sym)
			return;
		if (GELF_ST_TYPE(sym.st_info) != STT_FUNC)
			continue;

		if (sym.st_shndx == STN_UNDEF)
			continue;

		if (!firsttime && pmcstat_symbol_search(image, sym.st_value))
			continue; /* We've seen this symbol already. */

		if ((fnname = elf_strptr(e, sh->sh_link, sym.st_name))
		    == NULL)
			continue;
#ifdef __arm__
		/* Remove spurious ARM function name. */
		if (fnname[0] == '$' &&
		    (fnname[1] == 'a' || fnname[1] == 't' ||
		    fnname[1] == 'd') &&
		    fnname[2] == '\0')
			continue;
#endif

		symptr->ps_name  = pmcstat_string_intern(fnname);
		symptr->ps_start = sym.st_value - image->pi_vaddr;
		symptr->ps_end   = symptr->ps_start + sym.st_size;

		symptr++;
		newsyms++;
	}

	image->pi_symcount += newsyms;
	if (image->pi_symcount == 0)
		return;

	assert(newsyms <= nfuncsyms);

	/*
	 * Return space to the system if there were duplicates.
	 */
	if (newsyms < nfuncsyms)
		image->pi_symbols = reallocarray(image->pi_symbols,
		    image->pi_symcount, sizeof(*symptr));

	/*
	 * Keep the list of symbols sorted.
	 */
	qsort(image->pi_symbols, image->pi_symcount, sizeof(*symptr),
	    pmcstat_symbol_compare);

	/*
	 * Deal with function symbols that have a size of 'zero' by
	 * making them extend to the next higher address.  These
	 * symbols are usually defined in assembly code.
	 */
	for (symptr = image->pi_symbols;
	     symptr < image->pi_symbols + (image->pi_symcount - 1);
	     symptr++)
		if (symptr->ps_start == symptr->ps_end)
			symptr->ps_end = (symptr+1)->ps_start;
}