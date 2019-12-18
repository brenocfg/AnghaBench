#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct ub_packed_rrset_key {int dummy; } ;
struct regional {int dummy; } ;
struct dns_msg {TYPE_1__* rep; } ;
struct TYPE_2__ {size_t rrset_count; int /*<<< orphan*/  ar_numrrsets; int /*<<< orphan*/ * rrsets; } ;

/* Variables and functions */
 int /*<<< orphan*/  packed_rrset_copy_region (struct ub_packed_rrset_key*,struct regional*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
addr_to_additional(struct ub_packed_rrset_key* rrset, struct regional* region,
	struct dns_msg* msg, time_t now)
{
	if((msg->rep->rrsets[msg->rep->rrset_count] = 
		packed_rrset_copy_region(rrset, region, now))) {
		msg->rep->ar_numrrsets++;
		msg->rep->rrset_count++;
	}
}