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
typedef  int /*<<< orphan*/  pmap_t ;

/* Variables and functions */
 int /*<<< orphan*/  pmap_call_on_active_cpus (int /*<<< orphan*/ ,void (*) (void*),int /*<<< orphan*/ ) ; 
 scalar_t__ tlb_invalidate_all_user ; 

__attribute__((used)) static void
pmap_invalidate_all(pmap_t pmap)
{

	pmap_call_on_active_cpus(pmap,
	    (void (*)(void *))tlb_invalidate_all_user, pmap);
}