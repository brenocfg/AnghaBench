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

/* Variables and functions */
 int /*<<< orphan*/ * abd_chunk_cache ; 
 int /*<<< orphan*/ * abd_ksp ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kstat_delete (int /*<<< orphan*/ *) ; 

void
abd_fini(void)
{
	if (abd_ksp != NULL) {
		kstat_delete(abd_ksp);
		abd_ksp = NULL;
	}

	kmem_cache_destroy(abd_chunk_cache);
	abd_chunk_cache = NULL;
}