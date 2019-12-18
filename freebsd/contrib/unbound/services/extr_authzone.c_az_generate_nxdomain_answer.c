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
struct regional {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  qname_len; int /*<<< orphan*/  qname; } ;
struct dns_msg {TYPE_1__ qinfo; TYPE_2__* rep; } ;
struct auth_zone {int dummy; } ;
struct auth_rrset {int dummy; } ;
struct auth_data {int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RCODE_NXDOMAIN ; 
 int /*<<< orphan*/  az_add_negative_soa (struct auth_zone*,struct regional*,struct dns_msg*) ; 
 int /*<<< orphan*/  az_add_nsec3_proof (struct auth_zone*,struct regional*,struct dns_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 struct auth_rrset* az_find_nsec_cover (struct auth_zone*,struct auth_data**) ; 
 int /*<<< orphan*/  az_nsec_wildcard_denial (struct auth_zone*,struct regional*,struct dns_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_add_rrset_ns (struct auth_zone*,struct regional*,struct dns_msg*,struct auth_data*,struct auth_rrset*) ; 

__attribute__((used)) static int
az_generate_nxdomain_answer(struct auth_zone* z, struct regional* region,
	struct dns_msg* msg, struct auth_data* ce, struct auth_data* node)
{
	struct auth_rrset* nsec;
	msg->rep->flags |= LDNS_RCODE_NXDOMAIN;
	if(!az_add_negative_soa(z, region, msg)) return 0;
	if((nsec=az_find_nsec_cover(z, &node)) != NULL) {
		if(!msg_add_rrset_ns(z, region, msg, node, nsec)) return 0;
		if(ce && !az_nsec_wildcard_denial(z, region, msg, ce->name,
			ce->namelen)) return 0;
	} else if(ce) {
		if(!az_add_nsec3_proof(z, region, msg, ce->name,
			ce->namelen, msg->qinfo.qname,
			msg->qinfo.qname_len, 0, 1, 1, 1))
			return 0;
	}
	return 1;
}