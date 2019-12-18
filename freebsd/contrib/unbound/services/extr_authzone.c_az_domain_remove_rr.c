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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
struct auth_rrset {TYPE_1__* data; scalar_t__ type; } ;
struct auth_data {int dummy; } ;
struct TYPE_3__ {int count; int rrsig_count; } ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_RRSIG ; 
 struct auth_rrset* az_domain_rrset (struct auth_data*,scalar_t__) ; 
 scalar_t__ az_rrset_find_rr (TYPE_1__*,int /*<<< orphan*/ *,size_t,size_t*) ; 
 scalar_t__ az_rrset_find_rrsig (TYPE_1__*,int /*<<< orphan*/ *,size_t,size_t*) ; 
 int /*<<< orphan*/  domain_remove_rrset (struct auth_data*,scalar_t__) ; 
 int /*<<< orphan*/  rrset_remove_rr (struct auth_rrset*,size_t) ; 
 scalar_t__ rrsig_rdata_get_type_covered (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  rrsigs_copy_from_rrset_to_rrsigset (struct auth_rrset*,struct auth_rrset*) ; 

__attribute__((used)) static int
az_domain_remove_rr(struct auth_data* node, uint16_t rr_type,
	uint8_t* rdata, size_t rdatalen, int* nonexist)
{
	struct auth_rrset* rrset;
	size_t index = 0;

	/* find the plain RR of the given type */
	if((rrset=az_domain_rrset(node, rr_type))!= NULL) {
		if(az_rrset_find_rr(rrset->data, rdata, rdatalen, &index)) {
			if(rrset->data->count == 1 &&
				rrset->data->rrsig_count == 0) {
				/* last RR, delete the rrset */
				domain_remove_rrset(node, rr_type);
			} else if(rrset->data->count == 1 &&
				rrset->data->rrsig_count != 0) {
				/* move RRSIGs to the RRSIG rrset, or
				 * this one becomes that RRset */
				struct auth_rrset* rrsigset = az_domain_rrset(
					node, LDNS_RR_TYPE_RRSIG);
				if(rrsigset) {
					/* move left over rrsigs to the
					 * existing rrset of type RRSIG */
					rrsigs_copy_from_rrset_to_rrsigset(
						rrset, rrsigset);
					/* and then delete the rrset */
					domain_remove_rrset(node, rr_type);
				} else {
					/* no rrset of type RRSIG, this
					 * set is now of that type,
					 * just remove the rr */
					if(!rrset_remove_rr(rrset, index))
						return 0;
					rrset->type = LDNS_RR_TYPE_RRSIG;
					rrset->data->count = rrset->data->rrsig_count;
					rrset->data->rrsig_count = 0;
				}
			} else {
				/* remove the RR from the rrset */
				if(!rrset_remove_rr(rrset, index))
					return 0;
			}
			return 1;
		}
		/* rr not found in rrset */
	}

	/* is it a type RRSIG, look under the covered type */
	if(rr_type == LDNS_RR_TYPE_RRSIG) {
		uint16_t ctype = rrsig_rdata_get_type_covered(rdata, rdatalen);
		if((rrset=az_domain_rrset(node, ctype))!= NULL) {
			if(az_rrset_find_rrsig(rrset->data, rdata, rdatalen,
				&index)) {
				/* rrsig should have d->count > 0, be
				 * over some rr of that type */
				/* remove the rrsig from the rrsigs list of the
				 * rrset */
				if(!rrset_remove_rr(rrset, index))
					return 0;
				return 1;
			}
		}
		/* also RRSIG not found */
	}

	/* nothing found to delete */
	if(nonexist) *nonexist = 1;
	return 1;
}