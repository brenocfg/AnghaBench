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
typedef  int /*<<< orphan*/  uint8_t ;
struct ub_packed_rrset_key {int dummy; } ;
struct regional {int dummy; } ;
struct dns_msg {TYPE_1__* rep; } ;
struct auth_zone {int /*<<< orphan*/  dclass; } ;
struct auth_rrset {int dummy; } ;
struct auth_data {int dummy; } ;
struct TYPE_2__ {size_t rrset_count; int /*<<< orphan*/  an_numrrsets; struct ub_packed_rrset_key** rrsets; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RCODE_YXDOMAIN ; 
 int /*<<< orphan*/  create_synth_cname (int /*<<< orphan*/ *,size_t,struct regional*,struct auth_data*,struct auth_rrset*,int /*<<< orphan*/ ,struct ub_packed_rrset_key**) ; 
 int /*<<< orphan*/  msg_grow_array (struct regional*,struct dns_msg*) ; 
 int /*<<< orphan*/  msg_ttl (struct dns_msg*) ; 

__attribute__((used)) static int
add_synth_cname(struct auth_zone* z, uint8_t* qname, size_t qname_len,
	struct regional* region, struct dns_msg* msg, struct auth_data* dname,
	struct auth_rrset* rrset)
{
	struct ub_packed_rrset_key* cname;
	/* synthesize a CNAME */
	if(!create_synth_cname(qname, qname_len, region, dname, rrset,
		z->dclass, &cname)) {
		/* out of memory */
		return 0;
	}
	if(!cname) {
		/* cname cannot be create because of YXDOMAIN */
		msg->rep->flags |= LDNS_RCODE_YXDOMAIN;
		return 1;
	}
	/* add cname to message */
	if(!msg_grow_array(region, msg))
		return 0;
	msg->rep->rrsets[msg->rep->rrset_count] = cname;
	msg->rep->rrset_count++;
	msg->rep->an_numrrsets++;
	msg_ttl(msg);
	return 1;
}