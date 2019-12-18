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
struct ip_fw_chain {int /*<<< orphan*/ * idxmap_back; int /*<<< orphan*/ * idxmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_IPFW ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ipfw_destroy_skipto_cache(struct ip_fw_chain *chain)
{

	if (chain->idxmap != NULL)
		free(chain->idxmap, M_IPFW);
	if (chain->idxmap != NULL)
		free(chain->idxmap_back, M_IPFW);
}