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
struct TYPE_3__ {scalar_t__ type; } ;
struct ub_packed_rrset_key {TYPE_1__ rk; } ;
struct regional {int dummy; } ;
struct query_info {scalar_t__ qtype; TYPE_2__* local_alias; } ;
struct local_rrset {int dummy; } ;
struct config_strlist {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  rrset; } ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_CNAME ; 
 scalar_t__ htons (scalar_t__) ; 
 int local_data_find_tag_datas (struct query_info*,struct config_strlist*,struct ub_packed_rrset_key*,struct regional*) ; 
 int /*<<< orphan*/  regional_alloc_init (struct regional*,struct ub_packed_rrset_key*,int) ; 
 TYPE_2__* regional_alloc_zero (struct regional*,int) ; 

__attribute__((used)) static int
find_tag_datas(struct query_info* qinfo, struct config_strlist* list,
	struct ub_packed_rrset_key* r, struct regional* temp)
{
	int result = local_data_find_tag_datas(qinfo, list, r, temp);

	/* If we've found a non-exact alias type of local data, make a shallow
	 * copy of the RRset and remember it in qinfo to complete the alias
	 * chain later. */
	if(result && qinfo->qtype != LDNS_RR_TYPE_CNAME &&
		r->rk.type == htons(LDNS_RR_TYPE_CNAME)) {
		qinfo->local_alias =
			regional_alloc_zero(temp, sizeof(struct local_rrset));
		if(!qinfo->local_alias)
			return 0; /* out of memory */
		qinfo->local_alias->rrset =
			regional_alloc_init(temp, r, sizeof(*r));
		if(!qinfo->local_alias->rrset)
			return 0; /* out of memory */
	}
	return result;
}