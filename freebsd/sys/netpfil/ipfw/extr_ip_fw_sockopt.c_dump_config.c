#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct sockopt_data {size_t valsize; } ;
struct ip_fw_chain {int n_rules; struct ip_fw** map; } ;
struct ip_fw_bcounter {int dummy; } ;
struct ip_fw {int dummy; } ;
struct dump_args {int* bmask; int e; int b; int rcount; int rcounters; int tcount; scalar_t__ rsize; } ;
typedef  int /*<<< orphan*/  ipfw_obj_tlv ;
typedef  int /*<<< orphan*/  ipfw_obj_ntlv ;
typedef  int /*<<< orphan*/  ipfw_obj_dyntlv ;
typedef  int /*<<< orphan*/  ipfw_obj_ctlv ;
struct TYPE_2__ {int flags; size_t end_rule; size_t start_rule; size_t size; int /*<<< orphan*/  set_mask; } ;
typedef  TYPE_1__ ipfw_cfg_lheader ;
typedef  int /*<<< orphan*/  ip_fw3_opheader ;
typedef  int /*<<< orphan*/  da ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int IPFW_CFG_GET_COUNTERS ; 
 int IPFW_CFG_GET_STATES ; 
 int IPFW_CFG_GET_STATIC ; 
 size_t IPFW_DEFAULT_RULE ; 
 int IPFW_TABLES_MAX ; 
 int /*<<< orphan*/  IPFW_UH_RLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_RUNLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ RULEUSIZE1 (struct ip_fw*) ; 
 int /*<<< orphan*/  UINT32_MAX ; 
 int /*<<< orphan*/  V_set_disable ; 
 int dump_named_objects (struct ip_fw_chain*,struct dump_args*,struct sockopt_data*) ; 
 int dump_static_rules (struct ip_fw_chain*,struct dump_args*,struct sockopt_data*) ; 
 int /*<<< orphan*/  free (int*,int /*<<< orphan*/ ) ; 
 int ipfw_dump_states (struct ip_fw_chain*,struct sockopt_data*) ; 
 int ipfw_dyn_get_count (int*,int*) ; 
 int ipfw_find_rule (struct ip_fw_chain*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ ipfw_get_sopt_header (struct sockopt_data*,int) ; 
 int* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mark_rule_objects (struct ip_fw_chain*,struct ip_fw*,struct dump_args*) ; 
 int /*<<< orphan*/  memset (struct dump_args*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
dump_config(struct ip_fw_chain *chain, ip_fw3_opheader *op3,
    struct sockopt_data *sd)
{
	struct dump_args da;
	ipfw_cfg_lheader *hdr;
	struct ip_fw *rule;
	size_t sz, rnum;
	uint32_t hdr_flags, *bmask;
	int error, i;

	hdr = (ipfw_cfg_lheader *)ipfw_get_sopt_header(sd, sizeof(*hdr));
	if (hdr == NULL)
		return (EINVAL);

	error = 0;
	bmask = NULL;
	memset(&da, 0, sizeof(da));
	/*
	 * Allocate needed state.
	 * Note we allocate 2xspace mask, for table & srv
	 */
	if (hdr->flags & (IPFW_CFG_GET_STATIC | IPFW_CFG_GET_STATES))
		da.bmask = bmask = malloc(
		    sizeof(uint32_t) * IPFW_TABLES_MAX * 2 / 32, M_TEMP,
		    M_WAITOK | M_ZERO);
	IPFW_UH_RLOCK(chain);

	/*
	 * STAGE 1: Determine size/count for objects in range.
	 * Prepare used tables bitmask.
	 */
	sz = sizeof(ipfw_cfg_lheader);
	da.e = chain->n_rules;

	if (hdr->end_rule != 0) {
		/* Handle custom range */
		if ((rnum = hdr->start_rule) > IPFW_DEFAULT_RULE)
			rnum = IPFW_DEFAULT_RULE;
		da.b = ipfw_find_rule(chain, rnum, 0);
		rnum = (hdr->end_rule < IPFW_DEFAULT_RULE) ?
		    hdr->end_rule + 1: IPFW_DEFAULT_RULE;
		da.e = ipfw_find_rule(chain, rnum, UINT32_MAX) + 1;
	}

	if (hdr->flags & IPFW_CFG_GET_STATIC) {
		for (i = da.b; i < da.e; i++) {
			rule = chain->map[i];
			da.rsize += RULEUSIZE1(rule) + sizeof(ipfw_obj_tlv);
			da.rcount++;
			/* Update bitmask of used objects for given range */
			mark_rule_objects(chain, rule, &da);
		}
		/* Add counters if requested */
		if (hdr->flags & IPFW_CFG_GET_COUNTERS) {
			da.rsize += sizeof(struct ip_fw_bcounter) * da.rcount;
			da.rcounters = 1;
		}
		sz += da.rsize + sizeof(ipfw_obj_ctlv);
	}

	if (hdr->flags & IPFW_CFG_GET_STATES) {
		sz += sizeof(ipfw_obj_ctlv) +
		    ipfw_dyn_get_count(bmask, &i) * sizeof(ipfw_obj_dyntlv);
		da.tcount += i;
	}

	if (da.tcount > 0)
		sz += da.tcount * sizeof(ipfw_obj_ntlv) +
		    sizeof(ipfw_obj_ctlv);

	/*
	 * Fill header anyway.
	 * Note we have to save header fields to stable storage
	 * buffer inside @sd can be flushed after dumping rules
	 */
	hdr->size = sz;
	hdr->set_mask = ~V_set_disable;
	hdr_flags = hdr->flags;
	hdr = NULL;

	if (sd->valsize < sz) {
		error = ENOMEM;
		goto cleanup;
	}

	/* STAGE2: Store actual data */
	if (da.tcount > 0) {
		error = dump_named_objects(chain, &da, sd);
		if (error != 0)
			goto cleanup;
	}

	if (hdr_flags & IPFW_CFG_GET_STATIC) {
		error = dump_static_rules(chain, &da, sd);
		if (error != 0)
			goto cleanup;
	}

	if (hdr_flags & IPFW_CFG_GET_STATES)
		error = ipfw_dump_states(chain, sd);

cleanup:
	IPFW_UH_RUNLOCK(chain);

	if (bmask != NULL)
		free(bmask, M_TEMP);

	return (error);
}