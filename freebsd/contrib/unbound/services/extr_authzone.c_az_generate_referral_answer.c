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
struct TYPE_4__ {int /*<<< orphan*/  qname_len; int /*<<< orphan*/  qname; } ;
struct dns_msg {TYPE_2__ qinfo; TYPE_1__* rep; } ;
struct auth_zone {int dummy; } ;
struct auth_rrset {int dummy; } ;
struct auth_data {int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_AA ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_DS ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_NSEC ; 
 int /*<<< orphan*/  az_add_additionals_from (struct auth_zone*,struct regional*,struct dns_msg*,struct auth_rrset*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  az_add_nsec3_proof (struct auth_zone*,struct regional*,struct dns_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct auth_rrset* az_domain_rrset (struct auth_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_assert (struct auth_data*) ; 
 int /*<<< orphan*/  msg_add_rrset_ns (struct auth_zone*,struct regional*,struct dns_msg*,struct auth_data*,struct auth_rrset*) ; 

__attribute__((used)) static int
az_generate_referral_answer(struct auth_zone* z, struct regional* region,
	struct dns_msg* msg, struct auth_data* ce, struct auth_rrset* rrset)
{
	struct auth_rrset* ds, *nsec;
	/* turn off AA flag, referral is nonAA because it leaves the zone */
	log_assert(ce);
	msg->rep->flags &= ~BIT_AA;
	if(!msg_add_rrset_ns(z, region, msg, ce, rrset)) return 0;
	/* add DS or deny it */
	if((ds=az_domain_rrset(ce, LDNS_RR_TYPE_DS))!=NULL) {
		if(!msg_add_rrset_ns(z, region, msg, ce, ds)) return 0;
	} else {
		/* deny the DS */
		if((nsec=az_domain_rrset(ce, LDNS_RR_TYPE_NSEC))!=NULL) {
			if(!msg_add_rrset_ns(z, region, msg, ce, nsec))
				return 0;
		} else {
			if(!az_add_nsec3_proof(z, region, msg, ce->name,
				ce->namelen, msg->qinfo.qname,
				msg->qinfo.qname_len, 1, 1, 0, 0))
				return 0;
		}
	}
	/* add additional rrs for type NS */
	if(!az_add_additionals_from(z, region, msg, rrset, 0)) return 0;
	return 1;
}