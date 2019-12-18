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
typedef  int /*<<< orphan*/ * vm_page_t ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/ * pmap_large_map_getptp_unlocked () ; 
 int /*<<< orphan*/  vm_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static vm_page_t
pmap_large_map_getptp(void)
{
	vm_page_t m;

	PMAP_LOCK_ASSERT(kernel_pmap, MA_OWNED);
	m = pmap_large_map_getptp_unlocked();
	if (m == NULL) {
		PMAP_UNLOCK(kernel_pmap);
		vm_wait(NULL);
		PMAP_LOCK(kernel_pmap);
		/* Callers retry. */
	}
	return (m);
}