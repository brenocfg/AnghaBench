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
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
struct pt_block_cache {scalar_t__ nentries; } ;
struct pt_bcache_entry {int dummy; } ;

/* Variables and functions */
 int SIZE_MAX ; 
 int UINT32_MAX ; 
 struct pt_block_cache* malloc (size_t) ; 
 int /*<<< orphan*/  memset (struct pt_block_cache*,int /*<<< orphan*/ ,size_t) ; 

struct pt_block_cache *pt_bcache_alloc(uint64_t nentries)
{
	struct pt_block_cache *bcache;
	uint64_t size;

	if (!nentries || (UINT32_MAX < nentries))
		return NULL;

	size = sizeof(*bcache) + (nentries * sizeof(struct pt_bcache_entry));
	if (SIZE_MAX < size)
		return NULL;

	bcache = malloc((size_t) size);
	if (!bcache)
		return NULL;

	memset(bcache, 0, (size_t) size);
	bcache->nentries = (uint32_t) nentries;

	return bcache;
}