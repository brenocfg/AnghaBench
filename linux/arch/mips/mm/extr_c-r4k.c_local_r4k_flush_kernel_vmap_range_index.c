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
 int /*<<< orphan*/  r4k_blast_dcache () ; 

__attribute__((used)) static inline void local_r4k_flush_kernel_vmap_range_index(void *args)
{
	/*
	 * Aliases only affect the primary caches so don't bother with
	 * S-caches or T-caches.
	 */
	r4k_blast_dcache();
}