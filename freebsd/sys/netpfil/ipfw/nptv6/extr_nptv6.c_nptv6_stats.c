#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct sockopt_data {int valsize; } ;
struct nptv6_cfg {int dummy; } ;
struct TYPE_5__ {size_t length; int /*<<< orphan*/  type; } ;
struct ipfw_nptv6_stats {int count; int objsize; int version; TYPE_2__ head; } ;
struct ip_fw_chain {int dummy; } ;
typedef  int /*<<< orphan*/  stats ;
struct TYPE_4__ {scalar_t__ set; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {TYPE_1__ ntlv; } ;
typedef  TYPE_3__ ipfw_obj_header ;
typedef  struct ipfw_nptv6_stats ipfw_obj_ctlv ;
typedef  int /*<<< orphan*/  ip_fw3_opheader ;

/* Variables and functions */
 int /*<<< orphan*/  CHAIN_TO_SRV (struct ip_fw_chain*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ESRCH ; 
 scalar_t__ IPFW_MAX_SETS ; 
 int /*<<< orphan*/  IPFW_TLV_COUNTERS ; 
 int /*<<< orphan*/  IPFW_UH_RLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_RUNLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  export_stats (struct ip_fw_chain*,struct nptv6_cfg*,struct ipfw_nptv6_stats*) ; 
 scalar_t__ ipfw_check_object_name_generic (int /*<<< orphan*/ ) ; 
 scalar_t__ ipfw_get_sopt_header (struct sockopt_data*,size_t) ; 
 int /*<<< orphan*/  memcpy (struct ipfw_nptv6_stats*,struct ipfw_nptv6_stats*,int) ; 
 int /*<<< orphan*/  memset (struct ipfw_nptv6_stats*,int /*<<< orphan*/ ,int) ; 
 struct nptv6_cfg* nptv6_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
nptv6_stats(struct ip_fw_chain *ch, ip_fw3_opheader *op,
    struct sockopt_data *sd)
{
	struct ipfw_nptv6_stats stats;
	struct nptv6_cfg *cfg;
	ipfw_obj_header *oh;
	ipfw_obj_ctlv *ctlv;
	size_t sz;

	sz = sizeof(ipfw_obj_header) + sizeof(ipfw_obj_ctlv) + sizeof(stats);
	if (sd->valsize % sizeof(uint64_t))
		return (EINVAL);
	if (sd->valsize < sz)
		return (ENOMEM);
	oh = (ipfw_obj_header *)ipfw_get_sopt_header(sd, sz);
	if (oh == NULL)
		return (EINVAL);
	if (ipfw_check_object_name_generic(oh->ntlv.name) != 0 ||
	    oh->ntlv.set >= IPFW_MAX_SETS)
		return (EINVAL);
	memset(&stats, 0, sizeof(stats));

	IPFW_UH_RLOCK(ch);
	cfg = nptv6_find(CHAIN_TO_SRV(ch), oh->ntlv.name, oh->ntlv.set);
	if (cfg == NULL) {
		IPFW_UH_RUNLOCK(ch);
		return (ESRCH);
	}
	export_stats(ch, cfg, &stats);
	IPFW_UH_RUNLOCK(ch);

	ctlv = (ipfw_obj_ctlv *)(oh + 1);
	memset(ctlv, 0, sizeof(*ctlv));
	ctlv->head.type = IPFW_TLV_COUNTERS;
	ctlv->head.length = sz - sizeof(ipfw_obj_header);
	ctlv->count = sizeof(stats) / sizeof(uint64_t);
	ctlv->objsize = sizeof(uint64_t);
	ctlv->version = 1;
	memcpy(ctlv + 1, &stats, sizeof(stats));
	return (0);
}