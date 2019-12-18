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
struct ip_fw_chain {int* idxmap; int* idxmap_back; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPFW_UH_WLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_WUNLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_WLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_WUNLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  M_IPFW ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  free (int*,int /*<<< orphan*/ ) ; 
 int* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  swap_skipto_cache (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  update_skipto_cache (struct ip_fw_chain*,int /*<<< orphan*/ ) ; 

void
ipfw_init_skipto_cache(struct ip_fw_chain *chain)
{
	int *idxmap, *idxmap_back;

	idxmap = malloc(65536 * sizeof(int), M_IPFW, M_WAITOK | M_ZERO);
	idxmap_back = malloc(65536 * sizeof(int), M_IPFW, M_WAITOK);

	/*
	 * Note we may be called at any time after initialization,
	 * for example, on first skipto rule, so we need to
	 * provide valid chain->idxmap on return
	 */

	IPFW_UH_WLOCK(chain);
	if (chain->idxmap != NULL) {
		IPFW_UH_WUNLOCK(chain);
		free(idxmap, M_IPFW);
		free(idxmap_back, M_IPFW);
		return;
	}

	/* Set backup pointer first to permit building cache */
	chain->idxmap_back = idxmap_back;
	update_skipto_cache(chain, chain->map);
	IPFW_WLOCK(chain);
	/* It is now safe to set chain->idxmap ptr */
	chain->idxmap = idxmap;
	swap_skipto_cache(chain);
	IPFW_WUNLOCK(chain);
	IPFW_UH_WUNLOCK(chain);
}