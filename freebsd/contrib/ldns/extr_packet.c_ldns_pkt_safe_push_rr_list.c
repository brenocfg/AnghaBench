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
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_pkt_section ;
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
 int /*<<< orphan*/  ldns_pkt_safe_push_rr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_list_rr (int /*<<< orphan*/ *,size_t) ; 
 size_t ldns_rr_list_rr_count (int /*<<< orphan*/ *) ; 

bool
ldns_pkt_safe_push_rr_list(ldns_pkt *p, ldns_pkt_section s, ldns_rr_list *list)
{
	size_t i;
	for(i = 0; i < ldns_rr_list_rr_count(list); i++) {
		if (!ldns_pkt_safe_push_rr(p, s, ldns_rr_list_rr(list, i))) {
			return false;
		}
	}
	return true;
}