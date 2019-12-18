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
struct sockopt_data {int valsize; } ;
struct nat64clat_dump_arg {struct sockopt_data* sd; struct ip_fw_chain* ch; } ;
struct ip_fw_chain {int dummy; } ;
struct TYPE_2__ {int count; int objsize; int size; } ;
typedef  TYPE_1__ ipfw_obj_lheader ;
typedef  int /*<<< orphan*/  ipfw_nat64clat_cfg ;
typedef  int /*<<< orphan*/  ip_fw3_opheader ;
typedef  int /*<<< orphan*/  da ;

/* Variables and functions */
 int /*<<< orphan*/  CHAIN_TO_SRV (struct ip_fw_chain*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IPFW_TLV_NAT64CLAT_NAME ; 
 int /*<<< orphan*/  IPFW_UH_RLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_RUNLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  export_config_cb ; 
 scalar_t__ ipfw_get_sopt_header (struct sockopt_data*,int) ; 
 int ipfw_objhash_count_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipfw_objhash_foreach_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nat64clat_dump_arg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct nat64clat_dump_arg*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
nat64clat_list(struct ip_fw_chain *ch, ip_fw3_opheader *op3,
    struct sockopt_data *sd)
{
	ipfw_obj_lheader *olh;
	struct nat64clat_dump_arg da;

	/* Check minimum header size */
	if (sd->valsize < sizeof(ipfw_obj_lheader))
		return (EINVAL);

	olh = (ipfw_obj_lheader *)ipfw_get_sopt_header(sd, sizeof(*olh));

	IPFW_UH_RLOCK(ch);
	olh->count = ipfw_objhash_count_type(CHAIN_TO_SRV(ch),
	    IPFW_TLV_NAT64CLAT_NAME);
	olh->objsize = sizeof(ipfw_nat64clat_cfg);
	olh->size = sizeof(*olh) + olh->count * olh->objsize;

	if (sd->valsize < olh->size) {
		IPFW_UH_RUNLOCK(ch);
		return (ENOMEM);
	}
	memset(&da, 0, sizeof(da));
	da.ch = ch;
	da.sd = sd;
	ipfw_objhash_foreach_type(CHAIN_TO_SRV(ch), export_config_cb,
	    &da, IPFW_TLV_NAT64CLAT_NAME);
	IPFW_UH_RUNLOCK(ch);

	return (0);
}