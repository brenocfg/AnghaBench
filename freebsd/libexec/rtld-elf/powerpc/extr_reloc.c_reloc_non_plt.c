#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ p_type; int p_flags; int /*<<< orphan*/  p_memsz; scalar_t__ p_vaddr; } ;
struct TYPE_7__ {int relasize; int phsize; scalar_t__ relocbase; TYPE_2__* phdr; int /*<<< orphan*/ * rela; int /*<<< orphan*/  dynsymcount; } ;
typedef  int /*<<< orphan*/  SymCache ;
typedef  int /*<<< orphan*/  RtldLockState ;
typedef  TYPE_1__ Obj_Entry ;
typedef  int /*<<< orphan*/  Elf_Rela ;
typedef  TYPE_2__ Elf_Phdr ;

/* Variables and functions */
 int PF_X ; 
 scalar_t__ PT_LOAD ; 
 int SYMLOOK_IFUNC ; 
 int /*<<< orphan*/  __syncicache (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * calloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ reloc_nonplt_object (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

int
reloc_non_plt(Obj_Entry *obj, Obj_Entry *obj_rtld, int flags,
    RtldLockState *lockstate)
{
	const Elf_Rela *relalim;
	const Elf_Rela *rela;
	const Elf_Phdr *phdr;
	SymCache *cache;
	int r = -1;

	if ((flags & SYMLOOK_IFUNC) != 0)
		/* XXX not implemented */
		return (0);

	/*
	 * The dynamic loader may be called from a thread, we have
	 * limited amounts of stack available so we cannot use alloca().
	 */
	if (obj != obj_rtld) {
		cache = calloc(obj->dynsymcount, sizeof(SymCache));
		/* No need to check for NULL here */
	} else
		cache = NULL;

	/*
	 * From the SVR4 PPC ABI:
	 * "The PowerPC family uses only the Elf32_Rela relocation
	 *  entries with explicit addends."
	 */
	relalim = (const Elf_Rela *)((const char *)obj->rela + obj->relasize);
	for (rela = obj->rela; rela < relalim; rela++) {
		if (reloc_nonplt_object(obj_rtld, obj, rela, cache, flags,
		    lockstate) < 0)
			goto done;
	}
	r = 0;
done:
	if (cache != NULL)
		free(cache);

	/*
	 * Synchronize icache for executable segments in case we made
	 * any changes.
	 */
	for (phdr = obj->phdr;
	    (const char *)phdr < (const char *)obj->phdr + obj->phsize;
	    phdr++) {
		if (phdr->p_type == PT_LOAD && (phdr->p_flags & PF_X) != 0) {
			__syncicache(obj->relocbase + phdr->p_vaddr,
			    phdr->p_memsz);
		}
	}

	return (r);
}