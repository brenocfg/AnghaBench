#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int relsize; int /*<<< orphan*/ * rel; int /*<<< orphan*/  dynsymcount; } ;
typedef  int /*<<< orphan*/  SymCache ;
typedef  int /*<<< orphan*/  RtldLockState ;
typedef  TYPE_1__ Obj_Entry ;
typedef  int /*<<< orphan*/  Elf_Rel ;

/* Variables and functions */
 int SYMLOOK_IFUNC ; 
 int /*<<< orphan*/ * calloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ reloc_nonplt_object (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

int
reloc_non_plt(Obj_Entry *obj, Obj_Entry *obj_rtld, int flags,
    RtldLockState *lockstate)
{
	const Elf_Rel *rellim;
	const Elf_Rel *rel;
	SymCache *cache;
	int r = -1;
	
	/* The relocation for the dynamic loader has already been done. */
	if (obj == obj_rtld)
		return (0);
	if ((flags & SYMLOOK_IFUNC) != 0)
		/* XXX not implemented */
		return (0);

	/*
 	 * The dynamic loader may be called from a thread, we have
	 * limited amounts of stack available so we cannot use alloca().
	 */
	cache = calloc(obj->dynsymcount, sizeof(SymCache));
	/* No need to check for NULL here */

	rellim = (const Elf_Rel *)((const char *)obj->rel + obj->relsize);
	for (rel = obj->rel; rel < rellim; rel++) {
		if (reloc_nonplt_object(obj, rel, cache, flags, lockstate) < 0)
			goto done;
	}
	r = 0;
done:
	if (cache != NULL)
		free(cache);
	return (r);
}