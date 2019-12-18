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
struct TYPE_4__ {scalar_t__ data; } ;
struct ub_packed_rrset_key {TYPE_2__ entry; } ;
struct packed_rrset_data {scalar_t__ security; } ;
struct dns_msg {TYPE_1__* rep; } ;
struct delegpt {scalar_t__ bogus; } ;
struct TYPE_3__ {size_t rrset_count; struct ub_packed_rrset_key** rrsets; } ;
typedef  int /*<<< orphan*/  RES ;

/* Variables and functions */
 int /*<<< orphan*/  delegpt_count_addr (struct delegpt*,size_t*,size_t*,size_t*) ; 
 int /*<<< orphan*/  delegpt_count_ns (struct delegpt*,size_t*,size_t*) ; 
 int /*<<< orphan*/  dump_rrset (int /*<<< orphan*/ *,struct ub_packed_rrset_key*,struct packed_rrset_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ sec_status_bogus ; 
 int /*<<< orphan*/  ssl_printf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void
print_dp_main(RES* ssl, struct delegpt* dp, struct dns_msg* msg)
{
	size_t i, n_ns, n_miss, n_addr, n_res, n_avail;

	/* print the dp */
	if(msg)
	    for(i=0; i<msg->rep->rrset_count; i++) {
		struct ub_packed_rrset_key* k = msg->rep->rrsets[i];
		struct packed_rrset_data* d = 
			(struct packed_rrset_data*)k->entry.data;
		if(d->security == sec_status_bogus) {
			if(!ssl_printf(ssl, "Address is BOGUS:\n"))
				return;
		}
		if(!dump_rrset(ssl, k, d, 0))
			return;
	    }
	delegpt_count_ns(dp, &n_ns, &n_miss);
	delegpt_count_addr(dp, &n_addr, &n_res, &n_avail);
	/* since dp has not been used by iterator, all are available*/
	if(!ssl_printf(ssl, "Delegation with %d names, of which %d "
		"can be examined to query further addresses.\n"
		"%sIt provides %d IP addresses.\n", 
		(int)n_ns, (int)n_miss, (dp->bogus?"It is BOGUS. ":""),
		(int)n_addr))
		return;
}