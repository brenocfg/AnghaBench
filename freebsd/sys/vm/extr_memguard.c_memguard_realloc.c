#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct malloc_type {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (void*,void*,int /*<<< orphan*/ ) ; 
 void* memguard_alloc (unsigned long,int) ; 
 int /*<<< orphan*/  memguard_free (void*) ; 
 int /*<<< orphan*/  min (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trunc_page (uintptr_t) ; 
 int /*<<< orphan*/ * v2sizep (int /*<<< orphan*/ ) ; 

void *
memguard_realloc(void *addr, unsigned long size, struct malloc_type *mtp,
    int flags)
{
	void *newaddr;
	u_long old_size;

	/*
	 * Allocate the new block.  Force the allocation to be guarded
	 * as the original may have been guarded through random
	 * chance, and that should be preserved.
	 */
	if ((newaddr = memguard_alloc(size, flags)) == NULL)
		return (NULL);

	/* Copy over original contents. */
	old_size = *v2sizep(trunc_page((uintptr_t)addr));
	bcopy(addr, newaddr, min(size, old_size));
	memguard_free(addr);
	return (newaddr);
}