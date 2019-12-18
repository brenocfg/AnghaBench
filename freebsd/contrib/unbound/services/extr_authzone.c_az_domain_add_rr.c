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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ uint16_t ;
struct auth_rrset {int /*<<< orphan*/  data; } ;
struct auth_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_RRSIG ; 
 struct auth_rrset* az_domain_rrset (struct auth_data*,scalar_t__) ; 
 scalar_t__ rdata_duplicate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  rrset_add_rr (struct auth_rrset*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int) ; 
 struct auth_rrset* rrset_create (struct auth_data*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  rrset_moveover_rrsigs (struct auth_data*,scalar_t__,struct auth_rrset*,struct auth_rrset*) ; 
 scalar_t__ rrsig_rdata_get_type_covered (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int
az_domain_add_rr(struct auth_data* node, uint16_t rr_type, uint32_t rr_ttl,
	uint8_t* rdata, size_t rdatalen, int* duplicate)
{
	struct auth_rrset* rrset;
	/* packed rrsets have their rrsigs along with them, sort them out */
	if(rr_type == LDNS_RR_TYPE_RRSIG) {
		uint16_t ctype = rrsig_rdata_get_type_covered(rdata, rdatalen);
		if((rrset=az_domain_rrset(node, ctype))!= NULL) {
			/* a node of the correct type exists, add the RRSIG
			 * to the rrset of the covered data type */
			if(rdata_duplicate(rrset->data, rdata, rdatalen)) {
				if(duplicate) *duplicate = 1;
				return 1;
			}
			if(!rrset_add_rr(rrset, rr_ttl, rdata, rdatalen, 1))
				return 0;
		} else if((rrset=az_domain_rrset(node, rr_type))!= NULL) {
			/* add RRSIG to rrset of type RRSIG */
			if(rdata_duplicate(rrset->data, rdata, rdatalen)) {
				if(duplicate) *duplicate = 1;
				return 1;
			}
			if(!rrset_add_rr(rrset, rr_ttl, rdata, rdatalen, 0))
				return 0;
		} else {
			/* create rrset of type RRSIG */
			if(!rrset_create(node, rr_type, rr_ttl, rdata,
				rdatalen))
				return 0;
		}
	} else {
		/* normal RR type */
		if((rrset=az_domain_rrset(node, rr_type))!= NULL) {
			/* add data to existing node with data type */
			if(rdata_duplicate(rrset->data, rdata, rdatalen)) {
				if(duplicate) *duplicate = 1;
				return 1;
			}
			if(!rrset_add_rr(rrset, rr_ttl, rdata, rdatalen, 0))
				return 0;
		} else {
			struct auth_rrset* rrsig;
			/* create new node with data type */
			if(!(rrset=rrset_create(node, rr_type, rr_ttl, rdata,
				rdatalen)))
				return 0;

			/* see if node of type RRSIG has signatures that
			 * cover the data type, and move them over */
			/* and then make the RRSIG type smaller */
			if((rrsig=az_domain_rrset(node, LDNS_RR_TYPE_RRSIG))
				!= NULL) {
				if(!rrset_moveover_rrsigs(node, rr_type,
					rrset, rrsig))
					return 0;
			}
		}
	}
	return 1;
}