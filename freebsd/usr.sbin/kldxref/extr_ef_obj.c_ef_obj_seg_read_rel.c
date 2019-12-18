#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_4__* elf_file_t ;
struct TYPE_9__ {scalar_t__ size; char* address; int nprogtab; int nrel; int nrela; int /*<<< orphan*/  ef_efile; TYPE_3__* relatab; TYPE_2__* reltab; TYPE_1__* progtab; int /*<<< orphan*/  ef_name; scalar_t__ ef_verbose; } ;
struct TYPE_8__ {int sec; size_t nrela; int /*<<< orphan*/ * rela; } ;
struct TYPE_7__ {int sec; size_t nrel; int /*<<< orphan*/ * rel; } ;
struct TYPE_6__ {int size; int sec; int /*<<< orphan*/ * addr; } ;
typedef  int /*<<< orphan*/  Elf_Rela ;
typedef  int /*<<< orphan*/  Elf_Rel ;
typedef  scalar_t__ Elf_Off ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  EF_RELOC_REL ; 
 int /*<<< orphan*/  EF_RELOC_RELA ; 
 int /*<<< orphan*/  bcopy (char*,void*,size_t) ; 
 int ef_reloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,size_t,void*) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ,long,long) ; 

__attribute__((used)) static int
ef_obj_seg_read_rel(elf_file_t ef, Elf_Off offset, size_t len, void *dest)
{
	char *memaddr;
	Elf_Rel *r;
	Elf_Rela *a;
	Elf_Off secbase, dataoff;
	int error, i, sec;

	if (offset + len > ef->size) {
		if (ef->ef_verbose)
			warnx("ef_obj_seg_read_rel(%s): bad offset/len (%lx:%ld)",
			    ef->ef_name, (long)offset, (long)len);
		return (EFAULT);
	}
	bcopy(ef->address + offset, dest, len);

	/* Find out which section contains the data. */
	memaddr = ef->address + offset;
	sec = -1;
	secbase = dataoff = 0;
	for (i = 0; i < ef->nprogtab; i++) {
		if (ef->progtab[i].addr == NULL)
			continue;
		if (memaddr < (char *)ef->progtab[i].addr || memaddr + len >
		     (char *)ef->progtab[i].addr + ef->progtab[i].size)
			continue;
		sec = ef->progtab[i].sec;
		/* We relocate to address 0. */
		secbase = (char *)ef->progtab[i].addr - ef->address;
		dataoff = memaddr - ef->address;
		break;
	}

	if (sec == -1)
		return (EFAULT);

	/* Now do the relocations. */
	for (i = 0; i < ef->nrel; i++) {
		if (ef->reltab[i].sec != sec)
			continue;
		for (r = ef->reltab[i].rel;
		     r < &ef->reltab[i].rel[ef->reltab[i].nrel]; r++) {
			error = ef_reloc(ef->ef_efile, r, EF_RELOC_REL, secbase,
			    dataoff, len, dest);
			if (error != 0)
				return (error);
		}
	}
	for (i = 0; i < ef->nrela; i++) {
		if (ef->relatab[i].sec != sec)
			continue;
		for (a = ef->relatab[i].rela;
		     a < &ef->relatab[i].rela[ef->relatab[i].nrela]; a++) {
			error = ef_reloc(ef->ef_efile, a, EF_RELOC_RELA,
			    secbase, dataoff, len, dest);
			if (error != 0)
				return (error);
		}
	}
	return (0);
}