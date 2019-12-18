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
typedef  int uint16_t ;
struct rule_check_info {scalar_t__ object_opcodes; scalar_t__ urule_numoff; scalar_t__ urule; struct ip_fw* krule; } ;
struct ip_fw_chain {int n_rules; int /*<<< orphan*/  static_len; scalar_t__ id; int /*<<< orphan*/  map; } ;
struct ip_fw {int rulenum; scalar_t__ id; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int ENOSPC ; 
 int IPFW_DEFAULT_RULE ; 
 int /*<<< orphan*/  IPFW_UH_WLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_WUNLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  M_IPFW ; 
 scalar_t__ RULEUSIZE0 (struct ip_fw*) ; 
 int V_autoinc_step ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,struct ip_fw**,int) ; 
 int /*<<< orphan*/  free (struct ip_fw**,int /*<<< orphan*/ ) ; 
 struct ip_fw** get_map (struct ip_fw_chain*,int,int /*<<< orphan*/ ) ; 
 int ipfw_find_rule (struct ip_fw_chain*,int,int /*<<< orphan*/ ) ; 
 int rewrite_rule_uidx (struct ip_fw_chain*,struct rule_check_info*) ; 
 struct ip_fw** swap_map (struct ip_fw_chain*,struct ip_fw**,int) ; 
 int /*<<< orphan*/  unref_rule_objects (struct ip_fw_chain*,struct ip_fw*) ; 
 int /*<<< orphan*/  update_skipto_cache (struct ip_fw_chain*,struct ip_fw**) ; 

__attribute__((used)) static int
commit_rules(struct ip_fw_chain *chain, struct rule_check_info *rci, int count)
{
	int error, i, insert_before, tcount;
	uint16_t rulenum, *pnum;
	struct rule_check_info *ci;
	struct ip_fw *krule;
	struct ip_fw **map;	/* the new array of pointers */

	/* Check if we need to do table/obj index remap */
	tcount = 0;
	for (ci = rci, i = 0; i < count; ci++, i++) {
		if (ci->object_opcodes == 0)
			continue;

		/*
		 * Rule has some object opcodes.
		 * We need to find (and create non-existing)
		 * kernel objects, and reference existing ones.
		 */
		error = rewrite_rule_uidx(chain, ci);
		if (error != 0) {

			/*
			 * rewrite failed, state for current rule
			 * has been reverted. Check if we need to
			 * revert more.
			 */
			if (tcount > 0) {

				/*
				 * We have some more table rules
				 * we need to rollback.
				 */

				IPFW_UH_WLOCK(chain);
				while (ci != rci) {
					ci--;
					if (ci->object_opcodes == 0)
						continue;
					unref_rule_objects(chain,ci->krule);

				}
				IPFW_UH_WUNLOCK(chain);

			}

			return (error);
		}

		tcount++;
	}

	/* get_map returns with IPFW_UH_WLOCK if successful */
	map = get_map(chain, count, 0 /* not locked */);
	if (map == NULL) {
		if (tcount > 0) {
			/* Unbind tables */
			IPFW_UH_WLOCK(chain);
			for (ci = rci, i = 0; i < count; ci++, i++) {
				if (ci->object_opcodes == 0)
					continue;

				unref_rule_objects(chain, ci->krule);
			}
			IPFW_UH_WUNLOCK(chain);
		}

		return (ENOSPC);
	}

	if (V_autoinc_step < 1)
		V_autoinc_step = 1;
	else if (V_autoinc_step > 1000)
		V_autoinc_step = 1000;

	/* FIXME: Handle count > 1 */
	ci = rci;
	krule = ci->krule;
	rulenum = krule->rulenum;

	/* find the insertion point, we will insert before */
	insert_before = rulenum ? rulenum + 1 : IPFW_DEFAULT_RULE;
	i = ipfw_find_rule(chain, insert_before, 0);
	/* duplicate first part */
	if (i > 0)
		bcopy(chain->map, map, i * sizeof(struct ip_fw *));
	map[i] = krule;
	/* duplicate remaining part, we always have the default rule */
	bcopy(chain->map + i, map + i + 1,
		sizeof(struct ip_fw *) *(chain->n_rules - i));
	if (rulenum == 0) {
		/* Compute rule number and write it back */
		rulenum = i > 0 ? map[i-1]->rulenum : 0;
		if (rulenum < IPFW_DEFAULT_RULE - V_autoinc_step)
			rulenum += V_autoinc_step;
		krule->rulenum = rulenum;
		/* Save number to userland rule */
		pnum = (uint16_t *)((caddr_t)ci->urule + ci->urule_numoff);
		*pnum = rulenum;
	}

	krule->id = chain->id + 1;
	update_skipto_cache(chain, map);
	map = swap_map(chain, map, chain->n_rules + 1);
	chain->static_len += RULEUSIZE0(krule);
	IPFW_UH_WUNLOCK(chain);
	if (map)
		free(map, M_IPFW);
	return (0);
}