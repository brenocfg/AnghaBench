#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct packed_rrset_data {scalar_t__ rrsig_count; } ;
struct dns_msg {TYPE_2__* rep; } ;
struct TYPE_6__ {scalar_t__ data; } ;
struct TYPE_5__ {size_t an_numrrsets; size_t ns_numrrsets; TYPE_1__** rrsets; } ;
struct TYPE_4__ {TYPE_3__ entry; } ;

/* Variables and functions */

int 
iter_msg_has_dnssec(struct dns_msg* msg)
{
	size_t i;
	if(!msg || !msg->rep)
		return 0;
	for(i=0; i<msg->rep->an_numrrsets + msg->rep->ns_numrrsets; i++) {
		if(((struct packed_rrset_data*)msg->rep->rrsets[i]->
			entry.data)->rrsig_count > 0)
			return 1;
	}
	/* empty message has no DNSSEC info, with DNSSEC the reply is
	 * not empty (NSEC) */
	return 0;
}