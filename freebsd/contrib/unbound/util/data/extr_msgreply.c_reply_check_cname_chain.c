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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
struct reply_info {size_t an_numrrsets; TYPE_2__** rrsets; } ;
struct query_info {size_t qname_len; int /*<<< orphan*/ * qname; } ;
struct TYPE_3__ {int /*<<< orphan*/  dname; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {TYPE_1__ rk; } ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_CNAME ; 
 scalar_t__ LDNS_RR_TYPE_DNAME ; 
 int /*<<< orphan*/  get_cname_target (TYPE_2__*,int /*<<< orphan*/ **,size_t*) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ query_dname_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
reply_check_cname_chain(struct query_info* qinfo, struct reply_info* rep) 
{
	/* check only answer section rrs for matching cname chain.
	 * the cache may return changed rdata, but owner names are untouched.*/
	size_t i;
	uint8_t* sname = qinfo->qname;
	size_t snamelen = qinfo->qname_len;
	for(i=0; i<rep->an_numrrsets; i++) {
		uint16_t t = ntohs(rep->rrsets[i]->rk.type);
		if(t == LDNS_RR_TYPE_DNAME)
			continue; /* skip dnames; note TTL 0 not cached */
		/* verify that owner matches current sname */
		if(query_dname_compare(sname, rep->rrsets[i]->rk.dname) != 0){
			/* cname chain broken */
			return 0;
		}
		/* if this is a cname; move on */
		if(t == LDNS_RR_TYPE_CNAME) {
			get_cname_target(rep->rrsets[i], &sname, &snamelen);
		}
	}
	return 1;
}