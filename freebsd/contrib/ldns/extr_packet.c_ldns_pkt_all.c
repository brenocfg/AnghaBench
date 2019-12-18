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
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
 int /*<<< orphan*/  ldns_pkt_additional (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_pkt_answer (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_pkt_authority (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ldns_pkt_question (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ldns_rr_list_cat_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_list_deep_free (int /*<<< orphan*/ *) ; 

ldns_rr_list *
ldns_pkt_all(const ldns_pkt *packet)
{
	ldns_rr_list *all, *prev_all;

	all = ldns_rr_list_cat_clone(
			ldns_pkt_question(packet),
			ldns_pkt_answer(packet));
	prev_all = all;
	all = ldns_rr_list_cat_clone(all,
			ldns_pkt_authority(packet));
	ldns_rr_list_deep_free(prev_all);
	prev_all = all;
	all = ldns_rr_list_cat_clone(all,
			ldns_pkt_additional(packet));
	ldns_rr_list_deep_free(prev_all);
	return all;
}