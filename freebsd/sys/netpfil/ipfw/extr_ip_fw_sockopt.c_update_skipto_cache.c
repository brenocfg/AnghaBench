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
struct ip_fw_chain {int* idxmap_back; } ;
struct ip_fw {int rulenum; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPFW_UH_WLOCK_ASSERT (struct ip_fw_chain*) ; 

__attribute__((used)) static void
update_skipto_cache(struct ip_fw_chain *chain, struct ip_fw **map)
{
	int *smap, rulenum;
	int i, mi;

	IPFW_UH_WLOCK_ASSERT(chain);

	mi = 0;
	rulenum = map[mi]->rulenum;
	smap = chain->idxmap_back;

	if (smap == NULL)
		return;

	for (i = 0; i < 65536; i++) {
		smap[i] = mi;
		/* Use the same rule index until i < rulenum */
		if (i != rulenum || i == 65535)
			continue;
		/* Find next rule with num > i */
		rulenum = map[++mi]->rulenum;
		while (rulenum == i)
			rulenum = map[++mi]->rulenum;
	}
}