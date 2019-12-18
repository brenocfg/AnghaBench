#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* vm_offset_t ;
typedef  TYPE_1__* vm_map_entry_t ;
struct kinfo_vmentry {int kve_protection; int kve_flags; scalar_t__ kve_type; scalar_t__ kve_end; scalar_t__ kve_start; } ;
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_4__ {int protection; struct TYPE_4__* next; void* end; void* start; } ;

/* Variables and functions */
 int KVME_FLAG_NOCOREDUMP ; 
 int KVME_PROT_EXEC ; 
 int KVME_PROT_READ ; 
 scalar_t__ KVME_TYPE_DEAD ; 
 scalar_t__ KVME_TYPE_DEFAULT ; 
 scalar_t__ KVME_TYPE_PHYS ; 
 scalar_t__ KVME_TYPE_SWAP ; 
 scalar_t__ KVME_TYPE_UNKNOWN ; 
 scalar_t__ KVME_TYPE_VNODE ; 
 int PFLAGS_FULL ; 
 int VM_PROT_EXECUTE ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (struct kinfo_vmentry*) ; 
 struct kinfo_vmentry* kinfo_getvmmap (int /*<<< orphan*/ ,int*) ; 
 int pflags ; 

__attribute__((used)) static vm_map_entry_t
readmap(pid_t pid)
{
	vm_map_entry_t ent, *linkp, map;
	struct kinfo_vmentry *vmentl, *kve;
	int i, nitems;

	vmentl = kinfo_getvmmap(pid, &nitems);
	if (vmentl == NULL)
		err(1, "cannot retrieve mappings for %u process", pid);

	map = NULL;
	linkp = &map;
	for (i = 0; i < nitems; i++) {
		kve = &vmentl[i];

		/*
		 * Ignore 'malformed' segments or ones representing memory
		 * mapping with MAP_NOCORE on.
		 * If the 'full' support is disabled, just dump the most
		 * meaningful data segments.
		 */
		if ((kve->kve_protection & KVME_PROT_READ) == 0 ||
		    (kve->kve_flags & KVME_FLAG_NOCOREDUMP) != 0 ||
		    kve->kve_type == KVME_TYPE_DEAD ||
		    kve->kve_type == KVME_TYPE_UNKNOWN ||
		    ((pflags & PFLAGS_FULL) == 0 &&
		    kve->kve_type != KVME_TYPE_DEFAULT &&
		    kve->kve_type != KVME_TYPE_VNODE &&
		    kve->kve_type != KVME_TYPE_SWAP &&
		    kve->kve_type != KVME_TYPE_PHYS))
			continue;

		ent = calloc(1, sizeof(*ent));
		if (ent == NULL)
			errx(1, "out of memory");
		ent->start = (vm_offset_t)kve->kve_start;
		ent->end = (vm_offset_t)kve->kve_end;
		ent->protection = VM_PROT_READ | VM_PROT_WRITE;
		if ((kve->kve_protection & KVME_PROT_EXEC) != 0)
			ent->protection |= VM_PROT_EXECUTE;

		*linkp = ent;
		linkp = &ent->next;
	}
	free(vmentl);
	return (map);
}