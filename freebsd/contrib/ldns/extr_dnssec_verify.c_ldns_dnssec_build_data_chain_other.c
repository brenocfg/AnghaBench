#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rr_class ;
typedef  int /*<<< orphan*/  ldns_resolver ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  int /*<<< orphan*/  ldns_pkt ;
struct TYPE_4__ {int parent_type; int /*<<< orphan*/ * signatures; TYPE_3__* parent; } ;
typedef  TYPE_1__ ldns_dnssec_data_chain ;
struct TYPE_5__ {int /*<<< orphan*/  packet_qtype; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_DNSKEY ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_DS ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_RRSIG ; 
 int /*<<< orphan*/  LDNS_SECTION_ANSWER ; 
 int /*<<< orphan*/  LDNS_SECTION_ANY_NOQUESTION ; 
 TYPE_3__* ldns_dnssec_build_data_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_pkt_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_pkt_rr_list_by_name_and_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ldns_resolver_query (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_list_deep_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
ldns_dnssec_build_data_chain_other(ldns_resolver *res,
					    uint16_t qflags,
						ldns_dnssec_data_chain *new_chain,
						ldns_rdf *key_name,
						ldns_rr_class c,
						ldns_rr_list *dss)
{
	/* 'self-signed', parent is a DS */
	
	/* okay, either we have other keys signing the current one,
	 * or the current
	 * one should have a DS record in the parent zone.
	 * How do we find this out? Try both?
	 *
	 * request DNSKEYS for current zone,
	 * add all signatures to current level
	 */
	ldns_pkt *my_pkt;
	ldns_rr_list *signatures2;
	
	new_chain->parent_type = 1;

	my_pkt = ldns_resolver_query(res,
							key_name,
							LDNS_RR_TYPE_DS,
							c,
							qflags);
	if (my_pkt) {
	dss = ldns_pkt_rr_list_by_name_and_type(my_pkt,
									key_name,
									LDNS_RR_TYPE_DS,
									LDNS_SECTION_ANY_NOQUESTION
									);
	if (dss) {
		new_chain->parent = ldns_dnssec_build_data_chain(res,
												qflags,
												dss,
												my_pkt,
												NULL);
		new_chain->parent->packet_qtype = LDNS_RR_TYPE_DS;
		ldns_rr_list_deep_free(dss);
	}
	ldns_pkt_free(my_pkt);
	}

	my_pkt = ldns_resolver_query(res,
							key_name,
							LDNS_RR_TYPE_DNSKEY,
							c,
							qflags);
	if (my_pkt) {
	signatures2 = ldns_pkt_rr_list_by_name_and_type(my_pkt,
										   key_name,
										   LDNS_RR_TYPE_RRSIG,
										   LDNS_SECTION_ANSWER);
	if (signatures2) {
		if (new_chain->signatures) {
			printf("There were already sigs!\n");
			ldns_rr_list_deep_free(new_chain->signatures);
			printf("replacing the old sigs\n");
		}
		new_chain->signatures = signatures2;
	}
	ldns_pkt_free(my_pkt);
	}
}