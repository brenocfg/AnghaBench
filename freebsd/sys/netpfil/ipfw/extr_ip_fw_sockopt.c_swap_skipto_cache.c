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
struct ip_fw_chain {int* idxmap; int* idxmap_back; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPFW_UH_WLOCK_ASSERT (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_WLOCK_ASSERT (struct ip_fw_chain*) ; 

__attribute__((used)) static void
swap_skipto_cache(struct ip_fw_chain *chain)
{
	int *map;

	IPFW_UH_WLOCK_ASSERT(chain);
	IPFW_WLOCK_ASSERT(chain);

	map = chain->idxmap;
	chain->idxmap = chain->idxmap_back;
	chain->idxmap_back = map;
}