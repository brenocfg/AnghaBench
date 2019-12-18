#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ip_fw_chain {int n_rules; struct ip_fw** map; } ;
struct ip_fw {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ ipfw_range_tlv ;

/* Variables and functions */
 int /*<<< orphan*/  IPFW_RCFLAG_DEFAULT ; 
 int /*<<< orphan*/  IPFW_UH_WLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_WUNLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  clear_counters (struct ip_fw*,int) ; 
 scalar_t__ ipfw_match_range (struct ip_fw*,TYPE_1__*) ; 

__attribute__((used)) static int
clear_range(struct ip_fw_chain *chain, ipfw_range_tlv *rt, int log_only)
{
	struct ip_fw *rule;
	int num;
	int i;

	num = 0;
	rt->flags |= IPFW_RCFLAG_DEFAULT;

	IPFW_UH_WLOCK(chain);	/* arbitrate writers */
	for (i = 0; i < chain->n_rules; i++) {
		rule = chain->map[i];
		if (ipfw_match_range(rule, rt) == 0)
			continue;
		clear_counters(rule, log_only);
		num++;
	}
	IPFW_UH_WUNLOCK(chain);

	return (num);
}