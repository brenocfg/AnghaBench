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
struct ip_fw_chain {int n_rules; int /*<<< orphan*/  static_len; struct ip_fw** map; } ;
struct ip_fw {int dummy; } ;
struct TYPE_5__ {int flags; scalar_t__ end_rule; scalar_t__ start_rule; } ;
typedef  TYPE_1__ ipfw_range_tlv ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IPFW_DEFAULT_RULE ; 
 int IPFW_RCFLAG_DYNAMIC ; 
 int IPFW_RCFLAG_RANGE ; 
 int /*<<< orphan*/  IPFW_UH_WLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_WUNLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  M_IPFW ; 
 scalar_t__ RULEUSIZE0 (struct ip_fw*) ; 
 int /*<<< orphan*/  UINT32_MAX ; 
 int /*<<< orphan*/  bcopy (struct ip_fw**,struct ip_fw**,int) ; 
 int /*<<< orphan*/  free (struct ip_fw**,int /*<<< orphan*/ ) ; 
 struct ip_fw** get_map (struct ip_fw_chain*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ipfw_expire_dyn_states (struct ip_fw_chain*,TYPE_1__*) ; 
 int ipfw_find_rule (struct ip_fw_chain*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ipfw_is_dyn_rule (struct ip_fw*) ; 
 scalar_t__ ipfw_match_range (struct ip_fw*,TYPE_1__*) ; 
 int /*<<< orphan*/  ipfw_reap_add (struct ip_fw_chain*,struct ip_fw**,struct ip_fw*) ; 
 int /*<<< orphan*/  ipfw_reap_rules (struct ip_fw*) ; 
 struct ip_fw** swap_map (struct ip_fw_chain*,struct ip_fw**,int) ; 
 int /*<<< orphan*/  update_skipto_cache (struct ip_fw_chain*,struct ip_fw**) ; 

__attribute__((used)) static int
delete_range(struct ip_fw_chain *chain, ipfw_range_tlv *rt, int *ndel)
{
	struct ip_fw *reap, *rule, **map;
	int end, start;
	int i, n, ndyn, ofs;

	reap = NULL;
	IPFW_UH_WLOCK(chain);	/* arbitrate writers */

	/*
	 * Stage 1: Determine range to inspect.
	 * Range is half-inclusive, e.g [start, end).
	 */
	start = 0;
	end = chain->n_rules - 1;

	if ((rt->flags & IPFW_RCFLAG_RANGE) != 0) {
		start = ipfw_find_rule(chain, rt->start_rule, 0);

		if (rt->end_rule >= IPFW_DEFAULT_RULE)
			rt->end_rule = IPFW_DEFAULT_RULE - 1;
		end = ipfw_find_rule(chain, rt->end_rule, UINT32_MAX);
	}

	if (rt->flags & IPFW_RCFLAG_DYNAMIC) {
		/*
		 * Requested deleting only for dynamic states.
		 */
		*ndel = 0;
		ipfw_expire_dyn_states(chain, rt);
		IPFW_UH_WUNLOCK(chain);
		return (0);
	}

	/* Allocate new map of the same size */
	map = get_map(chain, 0, 1 /* locked */);
	if (map == NULL) {
		IPFW_UH_WUNLOCK(chain);
		return (ENOMEM);
	}

	n = 0;
	ndyn = 0;
	ofs = start;
	/* 1. bcopy the initial part of the map */
	if (start > 0)
		bcopy(chain->map, map, start * sizeof(struct ip_fw *));
	/* 2. copy active rules between start and end */
	for (i = start; i < end; i++) {
		rule = chain->map[i];
		if (ipfw_match_range(rule, rt) == 0) {
			map[ofs++] = rule;
			continue;
		}

		n++;
		if (ipfw_is_dyn_rule(rule) != 0)
			ndyn++;
	}
	/* 3. copy the final part of the map */
	bcopy(chain->map + end, map + ofs,
		(chain->n_rules - end) * sizeof(struct ip_fw *));
	/* 4. recalculate skipto cache */
	update_skipto_cache(chain, map);
	/* 5. swap the maps (under UH_WLOCK + WHLOCK) */
	map = swap_map(chain, map, chain->n_rules - n);
	/* 6. Remove all dynamic states originated by deleted rules */
	if (ndyn > 0)
		ipfw_expire_dyn_states(chain, rt);
	/* 7. now remove the rules deleted from the old map */
	for (i = start; i < end; i++) {
		rule = map[i];
		if (ipfw_match_range(rule, rt) == 0)
			continue;
		chain->static_len -= RULEUSIZE0(rule);
		ipfw_reap_add(chain, &reap, rule);
	}
	IPFW_UH_WUNLOCK(chain);

	ipfw_reap_rules(reap);
	if (map != NULL)
		free(map, M_IPFW);
	*ndel = n;
	return (0);
}