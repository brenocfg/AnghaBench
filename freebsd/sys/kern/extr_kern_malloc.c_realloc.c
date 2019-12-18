#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_offset_t ;
typedef  TYPE_2__* uma_slab_t ;
struct malloc_type {scalar_t__ ks_magic; } ;
struct TYPE_7__ {scalar_t__ td_critnest; } ;
struct TYPE_6__ {int us_flags; unsigned long us_size; TYPE_1__* us_keg; } ;
struct TYPE_5__ {unsigned long uk_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 unsigned long MINALLOCSIZE ; 
 scalar_t__ M_MAGIC ; 
 unsigned long REALLOC_FRACTION ; 
 scalar_t__ SCHEDULER_STOPPED () ; 
 int UMA_SLAB_MALLOC ; 
 int UMA_SLAB_MASK ; 
 int /*<<< orphan*/  bcopy (void*,void*,int /*<<< orphan*/ ) ; 
 TYPE_4__* curthread ; 
 int /*<<< orphan*/  free (void*,struct malloc_type*) ; 
 scalar_t__ is_memguard_addr (void*) ; 
 void* malloc (size_t,struct malloc_type*,int) ; 
 void* memguard_realloc (void*,size_t,struct malloc_type*,int) ; 
 int /*<<< orphan*/  min (size_t,unsigned long) ; 
 unsigned long redzone_get_size (void*) ; 
 TYPE_2__* vtoslab (int) ; 

void *
realloc(void *addr, size_t size, struct malloc_type *mtp, int flags)
{
	uma_slab_t slab;
	unsigned long alloc;
	void *newaddr;

	KASSERT(mtp->ks_magic == M_MAGIC,
	    ("realloc: bad malloc type magic"));
	KASSERT(curthread->td_critnest == 0 || SCHEDULER_STOPPED(),
	    ("realloc: called with spinlock or critical section held"));

	/* realloc(NULL, ...) is equivalent to malloc(...) */
	if (addr == NULL)
		return (malloc(size, mtp, flags));

	/*
	 * XXX: Should report free of old memory and alloc of new memory to
	 * per-CPU stats.
	 */

#ifdef DEBUG_MEMGUARD
	if (is_memguard_addr(addr))
		return (memguard_realloc(addr, size, mtp, flags));
#endif

#ifdef DEBUG_REDZONE
	slab = NULL;
	alloc = redzone_get_size(addr);
#else
	slab = vtoslab((vm_offset_t)addr & ~(UMA_SLAB_MASK));

	/* Sanity check */
	KASSERT(slab != NULL,
	    ("realloc: address %p out of range", (void *)addr));

	/* Get the size of the original block */
	if (!(slab->us_flags & UMA_SLAB_MALLOC))
		alloc = slab->us_keg->uk_size;
	else
		alloc = slab->us_size;

	/* Reuse the original block if appropriate */
	if (size <= alloc
	    && (size > (alloc >> REALLOC_FRACTION) || alloc == MINALLOCSIZE))
		return (addr);
#endif /* !DEBUG_REDZONE */

	/* Allocate a new, bigger (or smaller) block */
	if ((newaddr = malloc(size, mtp, flags)) == NULL)
		return (NULL);

	/* Copy over original contents */
	bcopy(addr, newaddr, min(size, alloc));
	free(addr, mtp);
	return (newaddr);
}