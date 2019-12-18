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
typedef  scalar_t__ uint16_t ;
typedef  scalar_t__ ldns_rr_type ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_pkt_section ;
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
 int /*<<< orphan*/ * ldns_pkt_get_section_clone (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_clone (int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_rr_get_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_list_deep_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_list_new () ; 
 int /*<<< orphan*/  ldns_rr_list_push_rr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_list_rr (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ldns_rr_list_rr_count (int /*<<< orphan*/ *) ; 

ldns_rr_list *
ldns_pkt_rr_list_by_type(const ldns_pkt *packet,
                         ldns_rr_type type,
                         ldns_pkt_section sec)
{
	ldns_rr_list *rrs;
	ldns_rr_list *new;
	uint16_t i;

	if(!packet) {
		return NULL;
	}
	
	rrs = ldns_pkt_get_section_clone(packet, sec);
	new = ldns_rr_list_new();
	
	for(i = 0; i < ldns_rr_list_rr_count(rrs); i++) {
		if (type == ldns_rr_get_type(ldns_rr_list_rr(rrs, i))) {
			/* types match */
			ldns_rr_list_push_rr(new, 
			                     ldns_rr_clone(
			                     	ldns_rr_list_rr(rrs, i))
					     );
		}
	}
	ldns_rr_list_deep_free(rrs);

	if (ldns_rr_list_rr_count(new) == 0) {
		ldns_rr_list_free(new);
		return NULL;
	} else {
		return new;
	}
}