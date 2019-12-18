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
typedef  int /*<<< orphan*/  uint8_t ;
struct reply_info {size_t an_numrrsets; size_t ns_numrrsets; size_t rrset_count; TYPE_2__** rrsets; } ;
struct query_info {int /*<<< orphan*/  qname; } ;
typedef  enum val_classification { ____Placeholder_val_classification } val_classification ;
struct TYPE_4__ {int /*<<< orphan*/  type; int /*<<< orphan*/  dname; } ;
struct TYPE_5__ {TYPE_1__ rk; } ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_DNAME ; 
 scalar_t__ LDNS_RR_TYPE_NSEC ; 
 scalar_t__ LDNS_RR_TYPE_NSEC3 ; 
 int VAL_CLASS_ANY ; 
 int VAL_CLASS_CNAME ; 
 int VAL_CLASS_CNAMENOANSWER ; 
 int VAL_CLASS_NAMEERROR ; 
 int VAL_CLASS_NODATA ; 
 int VAL_CLASS_POSITIVE ; 
 int VAL_CLASS_REFERRAL ; 
 int /*<<< orphan*/  VERB_QUERY ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ query_dname_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  val_find_best_signer (TYPE_2__*,struct query_info*,int /*<<< orphan*/ **,size_t*,int*) ; 
 int /*<<< orphan*/  val_find_rrset_signer (TYPE_2__*,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 

void 
val_find_signer(enum val_classification subtype, struct query_info* qinf, 
	struct reply_info* rep, size_t skip, uint8_t** signer_name, 
	size_t* signer_len)
{
	size_t i;
	
	if(subtype == VAL_CLASS_POSITIVE) {
		/* check for the answer rrset */
		for(i=skip; i<rep->an_numrrsets; i++) {
			if(query_dname_compare(qinf->qname, 
				rep->rrsets[i]->rk.dname) == 0) {
				val_find_rrset_signer(rep->rrsets[i], 
					signer_name, signer_len);
				return;
			}
		}
		*signer_name = NULL;
		*signer_len = 0;
	} else if(subtype == VAL_CLASS_CNAME) {
		/* check for the first signed cname/dname rrset */
		for(i=skip; i<rep->an_numrrsets; i++) {
			val_find_rrset_signer(rep->rrsets[i], 
				signer_name, signer_len);
			if(*signer_name)
				return;
			if(ntohs(rep->rrsets[i]->rk.type) != LDNS_RR_TYPE_DNAME)
				break; /* only check CNAME after a DNAME */
		}
		*signer_name = NULL;
		*signer_len = 0;
	} else if(subtype == VAL_CLASS_NAMEERROR 
		|| subtype == VAL_CLASS_NODATA) {
		/*Check to see if the AUTH section NSEC record(s) have rrsigs*/
		for(i=rep->an_numrrsets; i<
			rep->an_numrrsets+rep->ns_numrrsets; i++) {
			if(ntohs(rep->rrsets[i]->rk.type) == LDNS_RR_TYPE_NSEC
				|| ntohs(rep->rrsets[i]->rk.type) ==
				LDNS_RR_TYPE_NSEC3) {
				val_find_rrset_signer(rep->rrsets[i], 
					signer_name, signer_len);
				return;
			}
		}
	} else if(subtype == VAL_CLASS_CNAMENOANSWER) {
		/* find closest superdomain signer name in authority section
		 * NSEC and NSEC3s */
		int matchcount = 0;
		*signer_name = NULL;
		*signer_len = 0;
		for(i=rep->an_numrrsets; i<rep->an_numrrsets+rep->
			ns_numrrsets; i++) { 
			if(ntohs(rep->rrsets[i]->rk.type) == LDNS_RR_TYPE_NSEC
				|| ntohs(rep->rrsets[i]->rk.type) == 
				LDNS_RR_TYPE_NSEC3) {
				val_find_best_signer(rep->rrsets[i], qinf,
					signer_name, signer_len, &matchcount);
			}
		}
	} else if(subtype == VAL_CLASS_ANY) {
		/* check for one of the answer rrset that has signatures,
		 * or potentially a DNAME is in use with a different qname */
		for(i=skip; i<rep->an_numrrsets; i++) {
			if(query_dname_compare(qinf->qname, 
				rep->rrsets[i]->rk.dname) == 0) {
				val_find_rrset_signer(rep->rrsets[i], 
					signer_name, signer_len);
				if(*signer_name)
					return;
			}
		}
		/* no answer RRSIGs with qname, try a DNAME */
		if(skip < rep->an_numrrsets &&
			ntohs(rep->rrsets[skip]->rk.type) ==
			LDNS_RR_TYPE_DNAME) {
			val_find_rrset_signer(rep->rrsets[skip], 
				signer_name, signer_len);
			if(*signer_name)
				return;
		}
		*signer_name = NULL;
		*signer_len = 0;
	} else if(subtype == VAL_CLASS_REFERRAL) {
		/* find keys for the item at skip */
		if(skip < rep->rrset_count) {
			val_find_rrset_signer(rep->rrsets[skip], 
				signer_name, signer_len);
			return;
		}
		*signer_name = NULL;
		*signer_len = 0;
	} else {
		verbose(VERB_QUERY, "find_signer: could not find signer name"
			" for unknown type response");
		*signer_name = NULL;
		*signer_len = 0;
	}
}