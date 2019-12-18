#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct toffsets {size_t to_resid; size_t to_symoff; size_t to_stroff; scalar_t__ to_stridx; struct ksyms_softc* to_sc; } ;
struct ksyms_softc {int dummy; } ;
struct TYPE_11__ {scalar_t__ value; } ;
typedef  TYPE_1__ linker_symval_t ;
typedef  TYPE_2__* linker_file_t ;
typedef  char* caddr_t ;
typedef  int /*<<< orphan*/  c_linker_sym_t ;
struct TYPE_13__ {uintptr_t st_value; int /*<<< orphan*/  st_name; } ;
struct TYPE_12__ {int id; } ;
typedef  TYPE_3__ Elf_Sym ;

/* Variables and functions */
 int ENXIO ; 
 size_t LINKER_STRTAB_GET (TYPE_2__*,char**) ; 
 scalar_t__ LINKER_SYMBOL_VALUES (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 size_t LINKER_SYMTAB_GET (TYPE_2__*,TYPE_3__ const**) ; 
 int /*<<< orphan*/  MOD_SLOCK ; 
 int /*<<< orphan*/  MOD_SUNLOCK ; 
 int /*<<< orphan*/  M_KSYMS ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  SYMBLKSZ ; 
 int /*<<< orphan*/  bcopy (TYPE_3__ const*,char*,size_t) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int ksyms_emit (struct ksyms_softc*,char*,size_t,size_t) ; 
 char* malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t min (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int
ksyms_add(linker_file_t lf, void *arg)
{
	char *buf;
	struct ksyms_softc *sc;
	struct toffsets *to;
	const Elf_Sym *symtab;
	Elf_Sym *symp;
	caddr_t strtab;
	size_t len, numsyms, strsz, symsz;
	linker_symval_t symval;
	int error, i, nsyms;
	bool fixup;

	buf = malloc(SYMBLKSZ, M_KSYMS, M_WAITOK);
	to = arg;
	sc = to->to_sc;

	MOD_SLOCK;
	numsyms =  LINKER_SYMTAB_GET(lf, &symtab);
	strsz = LINKER_STRTAB_GET(lf, &strtab);
	symsz = numsyms * sizeof(Elf_Sym);

#ifdef __powerpc__
	fixup = true;
#else
	fixup = lf->id > 1;
#endif

	while (symsz > 0) {
		len = min(SYMBLKSZ, symsz);
		bcopy(symtab, buf, len);

		/*
		 * Fix up symbol table for kernel modules:
		 *   string offsets need adjusted
		 *   symbol values made absolute
		 */
		symp = (Elf_Sym *) buf;
		nsyms = len / sizeof(Elf_Sym);
		for (i = 0; i < nsyms; i++) {
			symp[i].st_name += to->to_stridx;
			if (fixup && LINKER_SYMBOL_VALUES(lf,
			    (c_linker_sym_t)&symtab[i], &symval) == 0) {
				symp[i].st_value = (uintptr_t)symval.value;
			}
		}

		if (len > to->to_resid) {
			MOD_SUNLOCK;
			free(buf, M_KSYMS);
			return (ENXIO);
		}
		to->to_resid -= len;
		error = ksyms_emit(sc, buf, to->to_symoff, len);
		to->to_symoff += len;
		if (error != 0) {
			MOD_SUNLOCK;
			free(buf, M_KSYMS);
			return (error);
		}

		symtab += nsyms;
		symsz -= len;
	}
	free(buf, M_KSYMS);
	MOD_SUNLOCK;

	if (strsz > to->to_resid)
		return (ENXIO);
	to->to_resid -= strsz;
	error = ksyms_emit(sc, strtab, to->to_stroff, strsz);
	to->to_stroff += strsz;
	to->to_stridx += strsz;

	return (error);
}