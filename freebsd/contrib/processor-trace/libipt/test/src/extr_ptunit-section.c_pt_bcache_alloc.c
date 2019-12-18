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
typedef  scalar_t__ uint32_t ;
struct pt_block_cache {scalar_t__ nentries; } ;

/* Variables and functions */
 scalar_t__ UINT32_MAX ; 
 struct pt_block_cache* malloc (int) ; 

struct pt_block_cache *pt_bcache_alloc(uint64_t nentries)
{
	struct pt_block_cache *bcache;

	if (!nentries || (UINT32_MAX < nentries))
		return NULL;

	/* The cache is not really used by tests.  It suffices to allocate only
	 * the cache struct with the single default entry.
	 *
	 * We still set the number of entries to the requested size.
	 */
	bcache = malloc(sizeof(*bcache));
	if (bcache)
		bcache->nentries = (uint32_t) nentries;

	return bcache;
}