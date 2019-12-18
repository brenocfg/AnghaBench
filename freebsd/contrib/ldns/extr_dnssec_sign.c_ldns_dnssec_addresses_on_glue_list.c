#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
struct TYPE_4__ {scalar_t__ type; struct TYPE_4__* next; TYPE_2__* rrs; } ;
typedef  TYPE_1__ ldns_dnssec_rrsets ;
struct TYPE_5__ {scalar_t__ rr; struct TYPE_5__* next; } ;
typedef  TYPE_2__ ldns_dnssec_rrs ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_A ; 
 scalar_t__ LDNS_RR_TYPE_AAAA ; 
 int /*<<< orphan*/  LDNS_STATUS_MEM_ERR ; 
 int /*<<< orphan*/  LDNS_STATUS_OK ; 
 int /*<<< orphan*/  ldns_rr_list_push_rr (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static ldns_status
ldns_dnssec_addresses_on_glue_list(
		ldns_dnssec_rrsets *cur_rrset,
		ldns_rr_list *glue_list)
{
	ldns_dnssec_rrs *cur_rrs;
	while (cur_rrset) {
		if (cur_rrset->type == LDNS_RR_TYPE_A 
				|| cur_rrset->type == LDNS_RR_TYPE_AAAA) {
			for (cur_rrs = cur_rrset->rrs; 
					cur_rrs; 
					cur_rrs = cur_rrs->next) {
				if (cur_rrs->rr) {
					if (!ldns_rr_list_push_rr(glue_list, 
							cur_rrs->rr)) {
						return LDNS_STATUS_MEM_ERR; 
						/* ldns_rr_list_push_rr()
						 * returns false when unable
						 * to increase the capacity
						 * of the ldsn_rr_list
						 */
					}
				}
			}
		}
		cur_rrset = cur_rrset->next;
	}
	return LDNS_STATUS_OK;
}