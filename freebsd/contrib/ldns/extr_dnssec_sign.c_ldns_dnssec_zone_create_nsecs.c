#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ ldns_status ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rr ;
struct TYPE_10__ {scalar_t__ data; } ;
typedef  TYPE_2__ ldns_rbnode_t ;
struct TYPE_11__ {int /*<<< orphan*/  names; int /*<<< orphan*/  soa; } ;
typedef  TYPE_3__ ldns_dnssec_zone ;
struct TYPE_12__ {TYPE_1__* rrs; } ;
typedef  TYPE_4__ ldns_dnssec_rrsets ;
typedef  int /*<<< orphan*/  ldns_dnssec_name ;
struct TYPE_9__ {scalar_t__ rr; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_DEFAULT_TTL ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_NSEC ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_SOA ; 
 scalar_t__ LDNS_STATUS_ERR ; 
 scalar_t__ LDNS_STATUS_OK ; 
 int /*<<< orphan*/ * ldns_dnssec_create_nsec (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_dnssec_name_add_rr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* ldns_dnssec_name_find_rrset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* ldns_dnssec_name_node_next_nonglue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rbtree_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rbtree_next (TYPE_2__*) ; 
 int /*<<< orphan*/  ldns_rdf2native_int32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_list_push_rr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_rdf (scalar_t__,int) ; 
 int /*<<< orphan*/  ldns_rr_set_ttl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

ldns_status
ldns_dnssec_zone_create_nsecs(ldns_dnssec_zone *zone,
                              ldns_rr_list *new_rrs)
{

	ldns_rbnode_t *first_node, *cur_node, *next_node;
	ldns_dnssec_name *cur_name, *next_name;
	ldns_rr *nsec_rr;
	uint32_t nsec_ttl;
	ldns_dnssec_rrsets *soa;

	/* the TTL of NSEC rrs should be set to the minimum TTL of
	 * the zone SOA (RFC4035 Section 2.3)
	 */
	soa = ldns_dnssec_name_find_rrset(zone->soa, LDNS_RR_TYPE_SOA);

	/* did the caller actually set it? if not,
	 * fall back to default ttl
	 */
	if (soa && soa->rrs && soa->rrs->rr
			&& (ldns_rr_rdf(soa->rrs->rr, 6) != NULL)) {
		nsec_ttl = ldns_rdf2native_int32(ldns_rr_rdf(soa->rrs->rr, 6));
	} else {
		nsec_ttl = LDNS_DEFAULT_TTL;
	}

	first_node = ldns_dnssec_name_node_next_nonglue(
			       ldns_rbtree_first(zone->names));
	cur_node = first_node;
	if (cur_node) {
		next_node = ldns_dnssec_name_node_next_nonglue(
			           ldns_rbtree_next(cur_node));
	} else {
		next_node = NULL;
	}

	while (cur_node && next_node) {
		cur_name = (ldns_dnssec_name *)cur_node->data;
		next_name = (ldns_dnssec_name *)next_node->data;
		nsec_rr = ldns_dnssec_create_nsec(cur_name,
		                                  next_name,
		                                  LDNS_RR_TYPE_NSEC);
		ldns_rr_set_ttl(nsec_rr, nsec_ttl);
		if(ldns_dnssec_name_add_rr(cur_name, nsec_rr)!=LDNS_STATUS_OK){
			ldns_rr_free(nsec_rr);
			return LDNS_STATUS_ERR;
		}
		ldns_rr_list_push_rr(new_rrs, nsec_rr);
		cur_node = next_node;
		if (cur_node) {
			next_node = ldns_dnssec_name_node_next_nonglue(
                               ldns_rbtree_next(cur_node));
		}
	}

	if (cur_node && !next_node) {
		cur_name = (ldns_dnssec_name *)cur_node->data;
		next_name = (ldns_dnssec_name *)first_node->data;
		nsec_rr = ldns_dnssec_create_nsec(cur_name,
		                                  next_name,
		                                  LDNS_RR_TYPE_NSEC);
		ldns_rr_set_ttl(nsec_rr, nsec_ttl);
		if(ldns_dnssec_name_add_rr(cur_name, nsec_rr)!=LDNS_STATUS_OK){
			ldns_rr_free(nsec_rr);
			return LDNS_STATUS_ERR;
		}
		ldns_rr_list_push_rr(new_rrs, nsec_rr);
	} else {
		printf("error\n");
	}

	return LDNS_STATUS_OK;
}