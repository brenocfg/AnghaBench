#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct reply_info {scalar_t__ an_numrrsets; size_t ns_numrrsets; TYPE_2__** rrsets; int /*<<< orphan*/  flags; } ;
struct query_info {int /*<<< orphan*/  qname; } ;
struct TYPE_6__ {int /*<<< orphan*/  type; int /*<<< orphan*/  dname; } ;
struct TYPE_7__ {TYPE_1__ rk; } ;

/* Variables and functions */
 scalar_t__ FLAGS_GET_RCODE (int /*<<< orphan*/ ) ; 
 scalar_t__ LDNS_RCODE_NOERROR ; 
 scalar_t__ LDNS_RCODE_NXDOMAIN ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_DLV ; 
 scalar_t__ LDNS_RR_TYPE_NSEC ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  dlv_topdomain (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t*) ; 
 int dname_canonical_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dname_remove_label (int /*<<< orphan*/ **,size_t*) ; 
 scalar_t__ dname_strict_subdomain_c (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_nametypeclass (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsec_get_next (TYPE_2__*,int /*<<< orphan*/ **,size_t*) ; 
 scalar_t__ nsec_has_type (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ val_nsec_proves_name_error (TYPE_2__*,int /*<<< orphan*/ ) ; 

int val_nsec_check_dlv(struct query_info* qinfo,
        struct reply_info* rep, uint8_t** nm, size_t* nm_len)
{
	uint8_t* next;
	size_t i, nlen;
	int c;
	/* we should now have a NOERROR/NODATA or NXDOMAIN message */
	if(rep->an_numrrsets != 0) {
		return 0;
	}
	/* is this NOERROR ? */
	if(FLAGS_GET_RCODE(rep->flags) == LDNS_RCODE_NOERROR) {
		/* it can be a plain NSEC match - go up one more level. */
		/* or its an empty nonterminal - go up to nonempty level */
		for(i=0; i<rep->ns_numrrsets; i++) {
			if(htons(rep->rrsets[i]->rk.type)!=LDNS_RR_TYPE_NSEC ||
				!nsec_get_next(rep->rrsets[i], &next, &nlen))
				continue;
			c = dname_canonical_compare(
				rep->rrsets[i]->rk.dname, qinfo->qname);
			if(c == 0) {
				/* plain match */
				if(nsec_has_type(rep->rrsets[i],
					LDNS_RR_TYPE_DLV))
					return 0;
				dname_remove_label(nm, nm_len);
				return 1;
			} else if(c < 0 && 
				dname_strict_subdomain_c(next, qinfo->qname)) {
				/* ENT */
				dlv_topdomain(rep->rrsets[i], qinfo->qname,
					nm, nm_len);
				return 1;
			}
		}
		return 0;
	}

	/* is this NXDOMAIN ? */
	if(FLAGS_GET_RCODE(rep->flags) == LDNS_RCODE_NXDOMAIN) {
		/* find the qname denial NSEC record. It can tell us
		 * a closest encloser name; or that we not need bother */
		for(i=0; i<rep->ns_numrrsets; i++) {
			if(htons(rep->rrsets[i]->rk.type) != LDNS_RR_TYPE_NSEC)
				continue;
			if(val_nsec_proves_name_error(rep->rrsets[i], 
				qinfo->qname)) {
				log_nametypeclass(VERB_ALGO, "topdomain on",
					rep->rrsets[i]->rk.dname, 
					ntohs(rep->rrsets[i]->rk.type), 0);
				dlv_topdomain(rep->rrsets[i], qinfo->qname,
					nm, nm_len);
				return 1;
			}
		}
		return 0;
	}
	return 0;
}