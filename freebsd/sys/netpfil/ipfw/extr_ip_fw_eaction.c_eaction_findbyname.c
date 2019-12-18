#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tid_info {int /*<<< orphan*/  type; int /*<<< orphan*/  uidx; int /*<<< orphan*/  tlen; int /*<<< orphan*/ * tlvs; } ;
struct named_object {int dummy; } ;
struct ip_fw_chain {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ ipfw_obj_ntlv ;

/* Variables and functions */
 int /*<<< orphan*/  CHAIN_TO_SRV (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  EACTION_DEBUG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ESRCH ; 
 int /*<<< orphan*/  IPFW_TLV_EACTION ; 
 TYPE_1__* ipfw_find_name_tlv_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct named_object* ipfw_objhash_lookup_name_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
eaction_findbyname(struct ip_fw_chain *ch, struct tid_info *ti,
    struct named_object **pno)
{
	ipfw_obj_ntlv *ntlv;

	if (ti->tlvs == NULL)
		return (EINVAL);

	/* Search ntlv in the buffer provided by user */
	ntlv = ipfw_find_name_tlv_type(ti->tlvs, ti->tlen, ti->uidx,
	    IPFW_TLV_EACTION);
	if (ntlv == NULL)
		return (EINVAL);
	EACTION_DEBUG("name %s, uidx %u, type %u", ntlv->name,
	    ti->uidx, ti->type);
	/*
	 * Search named object with corresponding name.
	 * Since eaction objects are global - ignore the set value
	 * and use zero instead.
	 */
	*pno = ipfw_objhash_lookup_name_type(CHAIN_TO_SRV(ch),
	    0, IPFW_TLV_EACTION, ntlv->name);
	if (*pno == NULL)
		return (ESRCH);
	return (0);
}