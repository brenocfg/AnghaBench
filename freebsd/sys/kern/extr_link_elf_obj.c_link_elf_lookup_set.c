#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  linker_file_t ;
typedef  TYPE_2__* elf_file_t ;
struct TYPE_4__ {int nprogtab; TYPE_1__* progtab; } ;
struct TYPE_3__ {int size; scalar_t__ addr; scalar_t__ name; } ;

/* Variables and functions */
 int ESRCH ; 
 scalar_t__ strcmp (scalar_t__,char const*) ; 
 scalar_t__ strncmp (scalar_t__,char*,int) ; 

__attribute__((used)) static int
link_elf_lookup_set(linker_file_t lf, const char *name,
    void ***startp, void ***stopp, int *countp)
{
	elf_file_t ef = (elf_file_t)lf;
	void **start, **stop;
	int i, count;

	/* Relative to section number */
	for (i = 0; i < ef->nprogtab; i++) {
		if ((strncmp(ef->progtab[i].name, "set_", 4) == 0) &&
		    strcmp(ef->progtab[i].name + 4, name) == 0) {
			start  = (void **)ef->progtab[i].addr;
			stop = (void **)((char *)ef->progtab[i].addr +
			    ef->progtab[i].size);
			count = stop - start;
			if (startp)
				*startp = start;
			if (stopp)
				*stopp = stop;
			if (countp)
				*countp = count;
			return (0);
		}
	}
	return (ESRCH);
}