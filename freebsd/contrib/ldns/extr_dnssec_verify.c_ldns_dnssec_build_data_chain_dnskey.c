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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rr_class ;
typedef  int /*<<< orphan*/  ldns_resolver ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  int /*<<< orphan*/  const ldns_pkt ;
struct TYPE_5__ {TYPE_1__* parent; scalar_t__ parent_type; int /*<<< orphan*/  signatures; } ;
typedef  TYPE_2__ ldns_dnssec_data_chain ;
struct TYPE_4__ {void* packet_qtype; } ;

/* Variables and functions */
 void* LDNS_RR_TYPE_DNSKEY ; 
 int /*<<< orphan*/  LDNS_SECTION_ANY_NOQUESTION ; 
 void* ldns_dnssec_build_data_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_pkt_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ldns_pkt_rr_list_by_name_and_type (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* ldns_resolver_query (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_list_clone (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_list_deep_free (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_rr_list_rr_count (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ldns_dnssec_build_data_chain_dnskey(ldns_resolver *res,
					    uint16_t qflags,
					    const ldns_pkt *pkt,
					    ldns_rr_list *signatures,
						ldns_dnssec_data_chain *new_chain,
						ldns_rdf *key_name,
						ldns_rr_class c) {
	ldns_rr_list *keys;
	ldns_pkt *my_pkt;
	if (signatures && ldns_rr_list_rr_count(signatures) > 0) {
		new_chain->signatures = ldns_rr_list_clone(signatures);
		new_chain->parent_type = 0;

		keys = ldns_pkt_rr_list_by_name_and_type(
				  pkt,
				 key_name,
				 LDNS_RR_TYPE_DNSKEY,
				 LDNS_SECTION_ANY_NOQUESTION
			  );
		if (!keys) {
			my_pkt = ldns_resolver_query(res,
									key_name,
									LDNS_RR_TYPE_DNSKEY,
									c,
									qflags);
			if (my_pkt) {
			keys = ldns_pkt_rr_list_by_name_and_type(
					  my_pkt,
					 key_name,
					 LDNS_RR_TYPE_DNSKEY,
					 LDNS_SECTION_ANY_NOQUESTION
				  );
			new_chain->parent = ldns_dnssec_build_data_chain(res,
													qflags,
													keys,
													my_pkt,
													NULL);
			new_chain->parent->packet_qtype = LDNS_RR_TYPE_DNSKEY;
			ldns_pkt_free(my_pkt);
			}
		} else {
			new_chain->parent = ldns_dnssec_build_data_chain(res,
													qflags,
													keys,
													pkt,
													NULL);
			new_chain->parent->packet_qtype = LDNS_RR_TYPE_DNSKEY;
		}
		ldns_rr_list_deep_free(keys);
	}
}