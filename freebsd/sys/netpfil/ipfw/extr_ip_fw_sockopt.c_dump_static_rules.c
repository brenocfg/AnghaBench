#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockopt_data {int dummy; } ;
struct ip_fw_chain {struct ip_fw** map; } ;
struct ip_fw_bcounter {int dummy; } ;
struct ip_fw {int dummy; } ;
struct dump_args {int b; int e; int /*<<< orphan*/  rcounters; int /*<<< orphan*/  rcount; scalar_t__ rsize; } ;
typedef  int /*<<< orphan*/  ipfw_obj_tlv ;
struct TYPE_3__ {scalar_t__ length; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {int /*<<< orphan*/  count; TYPE_1__ head; } ;
typedef  TYPE_2__ ipfw_obj_ctlv ;
typedef  int /*<<< orphan*/ * caddr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IPFW_TLV_RULE_LIST ; 
 int RULEUSIZE1 (struct ip_fw*) ; 
 int /*<<< orphan*/  export_rule1 (struct ip_fw*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ipfw_get_sopt_space (struct sockopt_data*,int) ; 

__attribute__((used)) static int
dump_static_rules(struct ip_fw_chain *chain, struct dump_args *da,
    struct sockopt_data *sd)
{
	ipfw_obj_ctlv *ctlv;
	struct ip_fw *krule;
	caddr_t dst;
	int i, l;

	/* Dump rules */
	ctlv = (ipfw_obj_ctlv *)ipfw_get_sopt_space(sd, sizeof(*ctlv));
	if (ctlv == NULL)
		return (ENOMEM);
	ctlv->head.type = IPFW_TLV_RULE_LIST;
	ctlv->head.length = da->rsize + sizeof(*ctlv);
	ctlv->count = da->rcount;

	for (i = da->b; i < da->e; i++) {
		krule = chain->map[i];

		l = RULEUSIZE1(krule) + sizeof(ipfw_obj_tlv);
		if (da->rcounters != 0)
			l += sizeof(struct ip_fw_bcounter);
		dst = (caddr_t)ipfw_get_sopt_space(sd, l);
		if (dst == NULL)
			return (ENOMEM);

		export_rule1(krule, dst, l, da->rcounters);
	}

	return (0);
}