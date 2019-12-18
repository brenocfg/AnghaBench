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
typedef  scalar_t__ uint64_t ;
typedef  size_t uint32_t ;
struct pt_block_cache {scalar_t__ nentries; struct pt_bcache_entry* entry; } ;
struct pt_bcache_entry {int dummy; } ;

/* Variables and functions */
 int pte_internal ; 

int pt_bcache_add(struct pt_block_cache *bcache, uint64_t index,
		  struct pt_bcache_entry bce)
{
	if (!bcache)
		return -pte_internal;

	if (bcache->nentries <= index)
		return -pte_internal;

	/* We rely on guaranteed atomic operations as specified in section 8.1.1
	 * in Volume 3A of the Intel(R) Software Developer's Manual at
	 * http://www.intel.com/sdm.
	 */
	bcache->entry[(uint32_t) index] = bce;

	return 0;
}