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
struct tables_config {int algo_count; struct table_algo** algo; } ;
struct table_algo {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct sockopt_data {int valsize; } ;
struct ip_fw_chain {int dummy; } ;
struct _ipfw_obj_lheader {int size; int count; int objsize; } ;
struct TYPE_2__ {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  type; int /*<<< orphan*/  algoname; } ;
typedef  TYPE_1__ ipfw_ta_info ;
typedef  int /*<<< orphan*/  ipfw_obj_lheader ;
typedef  int /*<<< orphan*/  ip_fw3_opheader ;

/* Variables and functions */
 struct tables_config* CHAIN_TO_TCFG (struct ip_fw_chain*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IPFW_UH_RLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_RUNLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ipfw_get_sopt_header (struct sockopt_data*,int) ; 
 scalar_t__ ipfw_get_sopt_space (struct sockopt_data*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
list_table_algo(struct ip_fw_chain *ch, ip_fw3_opheader *op3,
    struct sockopt_data *sd)
{
	struct _ipfw_obj_lheader *olh;
	struct tables_config *tcfg;
	ipfw_ta_info *i;
	struct table_algo *ta;
	uint32_t count, n, size;

	olh = (struct _ipfw_obj_lheader *)ipfw_get_sopt_header(sd,sizeof(*olh));
	if (olh == NULL)
		return (EINVAL);
	if (sd->valsize < olh->size)
		return (EINVAL);

	IPFW_UH_RLOCK(ch);
	tcfg = CHAIN_TO_TCFG(ch);
	count = tcfg->algo_count;
	size = count * sizeof(ipfw_ta_info) + sizeof(ipfw_obj_lheader);

	/* Fill in header regadless of buffer size */
	olh->count = count;
	olh->objsize = sizeof(ipfw_ta_info);

	if (size > olh->size) {
		olh->size = size;
		IPFW_UH_RUNLOCK(ch);
		return (ENOMEM);
	}
	olh->size = size;

	for (n = 1; n <= count; n++) {
		i = (ipfw_ta_info *)ipfw_get_sopt_space(sd, sizeof(*i));
		KASSERT(i != NULL, ("previously checked buffer is not enough"));
		ta = tcfg->algo[n];
		strlcpy(i->algoname, ta->name, sizeof(i->algoname));
		i->type = ta->type;
		i->refcnt = ta->refcnt;
	}

	IPFW_UH_RUNLOCK(ch);

	return (0);
}