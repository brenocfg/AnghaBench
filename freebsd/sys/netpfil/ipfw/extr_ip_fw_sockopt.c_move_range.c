#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ip_fw_chain {int n_rules; struct ip_fw** map; } ;
struct ip_fw {int /*<<< orphan*/  set; } ;
struct TYPE_5__ {int /*<<< orphan*/  new_set; } ;
typedef  TYPE_1__ ipfw_range_tlv ;

/* Variables and functions */
 int /*<<< orphan*/  IPFW_UH_WLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_WUNLOCK (struct ip_fw_chain*) ; 
 scalar_t__ ipfw_match_range (struct ip_fw*,TYPE_1__*) ; 
 int move_objects (struct ip_fw_chain*,TYPE_1__*) ; 

__attribute__((used)) static int
move_range(struct ip_fw_chain *chain, ipfw_range_tlv *rt)
{
	struct ip_fw *rule;
	int i;

	IPFW_UH_WLOCK(chain);

	/*
	 * Move rules with matching paramenerts to a new set.
	 * This one is much more complex. We have to ensure
	 * that all referenced tables (if any) are referenced
	 * by given rule subset only. Otherwise, we can't move
	 * them to new set and have to return error.
	 */
	if ((i = move_objects(chain, rt)) != 0) {
		IPFW_UH_WUNLOCK(chain);
		return (i);
	}

	/* XXX: We have to do swap holding WLOCK */
	for (i = 0; i < chain->n_rules; i++) {
		rule = chain->map[i];
		if (ipfw_match_range(rule, rt) == 0)
			continue;
		rule->set = rt->new_set;
	}

	IPFW_UH_WUNLOCK(chain);

	return (0);
}