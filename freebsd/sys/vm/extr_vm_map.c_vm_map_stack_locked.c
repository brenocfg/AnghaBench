#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_size_t ;
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  TYPE_1__* vm_map_entry_t ;
struct TYPE_10__ {int p_flag2; int p_fctl0; } ;
struct TYPE_9__ {scalar_t__ next_read; } ;
struct TYPE_8__ {scalar_t__ start; scalar_t__ end; int eflags; scalar_t__ next_read; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int KERN_INVALID_ADDRESS ; 
 int KERN_INVALID_ARGUMENT ; 
 int KERN_NO_SPACE ; 
 int KERN_SUCCESS ; 
 int MAP_CREATE_GUARD ; 
 int MAP_CREATE_STACK_GAP_DN ; 
 int MAP_CREATE_STACK_GAP_UP ; 
 int MAP_ENTRY_GROWS_DOWN ; 
 int MAP_ENTRY_GROWS_UP ; 
 int MAP_STACK_GROWS_DOWN ; 
 int MAP_STACK_GROWS_UP ; 
 int NT_FREEBSD_FCTL_STKGAP_DISABLE ; 
 int P2_STKGAP_DISABLE ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  VM_PROT_NONE ; 
 TYPE_7__* curproc ; 
 scalar_t__ stack_guard_page ; 
 int /*<<< orphan*/  vm_map_delete (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 TYPE_5__* vm_map_entry_pred (TYPE_1__*) ; 
 TYPE_1__* vm_map_entry_succ (TYPE_1__*) ; 
 int vm_map_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ vm_map_lookup_entry (int /*<<< orphan*/ ,scalar_t__,TYPE_1__**) ; 
 scalar_t__ vm_map_max (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_min (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vm_map_stack_locked(vm_map_t map, vm_offset_t addrbos, vm_size_t max_ssize,
    vm_size_t growsize, vm_prot_t prot, vm_prot_t max, int cow)
{
	vm_map_entry_t new_entry, prev_entry;
	vm_offset_t bot, gap_bot, gap_top, top;
	vm_size_t init_ssize, sgp;
	int orient, rv;

	/*
	 * The stack orientation is piggybacked with the cow argument.
	 * Extract it into orient and mask the cow argument so that we
	 * don't pass it around further.
	 */
	orient = cow & (MAP_STACK_GROWS_DOWN | MAP_STACK_GROWS_UP);
	KASSERT(orient != 0, ("No stack grow direction"));
	KASSERT(orient != (MAP_STACK_GROWS_DOWN | MAP_STACK_GROWS_UP),
	    ("bi-dir stack"));

	if (addrbos < vm_map_min(map) ||
	    addrbos + max_ssize > vm_map_max(map) ||
	    addrbos + max_ssize <= addrbos)
		return (KERN_INVALID_ADDRESS);
	sgp = ((curproc->p_flag2 & P2_STKGAP_DISABLE) != 0 ||
	    (curproc->p_fctl0 & NT_FREEBSD_FCTL_STKGAP_DISABLE) != 0) ? 0 :
	    (vm_size_t)stack_guard_page * PAGE_SIZE;
	if (sgp >= max_ssize)
		return (KERN_INVALID_ARGUMENT);

	init_ssize = growsize;
	if (max_ssize < init_ssize + sgp)
		init_ssize = max_ssize - sgp;

	/* If addr is already mapped, no go */
	if (vm_map_lookup_entry(map, addrbos, &prev_entry))
		return (KERN_NO_SPACE);

	/*
	 * If we can't accommodate max_ssize in the current mapping, no go.
	 */
	if (vm_map_entry_succ(prev_entry)->start < addrbos + max_ssize)
		return (KERN_NO_SPACE);

	/*
	 * We initially map a stack of only init_ssize.  We will grow as
	 * needed later.  Depending on the orientation of the stack (i.e.
	 * the grow direction) we either map at the top of the range, the
	 * bottom of the range or in the middle.
	 *
	 * Note: we would normally expect prot and max to be VM_PROT_ALL,
	 * and cow to be 0.  Possibly we should eliminate these as input
	 * parameters, and just pass these values here in the insert call.
	 */
	if (orient == MAP_STACK_GROWS_DOWN) {
		bot = addrbos + max_ssize - init_ssize;
		top = bot + init_ssize;
		gap_bot = addrbos;
		gap_top = bot;
	} else /* if (orient == MAP_STACK_GROWS_UP) */ {
		bot = addrbos;
		top = bot + init_ssize;
		gap_bot = top;
		gap_top = addrbos + max_ssize;
	}
	rv = vm_map_insert(map, NULL, 0, bot, top, prot, max, cow);
	if (rv != KERN_SUCCESS)
		return (rv);
	new_entry = vm_map_entry_succ(prev_entry);
	KASSERT(new_entry->end == top || new_entry->start == bot,
	    ("Bad entry start/end for new stack entry"));
	KASSERT((orient & MAP_STACK_GROWS_DOWN) == 0 ||
	    (new_entry->eflags & MAP_ENTRY_GROWS_DOWN) != 0,
	    ("new entry lacks MAP_ENTRY_GROWS_DOWN"));
	KASSERT((orient & MAP_STACK_GROWS_UP) == 0 ||
	    (new_entry->eflags & MAP_ENTRY_GROWS_UP) != 0,
	    ("new entry lacks MAP_ENTRY_GROWS_UP"));
	if (gap_bot == gap_top)
		return (KERN_SUCCESS);
	rv = vm_map_insert(map, NULL, 0, gap_bot, gap_top, VM_PROT_NONE,
	    VM_PROT_NONE, MAP_CREATE_GUARD | (orient == MAP_STACK_GROWS_DOWN ?
	    MAP_CREATE_STACK_GAP_DN : MAP_CREATE_STACK_GAP_UP));
	if (rv == KERN_SUCCESS) {
		/*
		 * Gap can never successfully handle a fault, so
		 * read-ahead logic is never used for it.  Re-use
		 * next_read of the gap entry to store
		 * stack_guard_page for vm_map_growstack().
		 */
		if (orient == MAP_STACK_GROWS_DOWN)
			vm_map_entry_pred(new_entry)->next_read = sgp;
		else
			vm_map_entry_succ(new_entry)->next_read = sgp;
	} else {
		(void)vm_map_delete(map, bot, top);
	}
	return (rv);
}