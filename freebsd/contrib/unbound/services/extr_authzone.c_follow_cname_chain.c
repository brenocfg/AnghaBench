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
typedef  int /*<<< orphan*/  uint16_t ;
struct regional {int dummy; } ;
struct packed_rrset_data {scalar_t__ count; int* rr_len; scalar_t__* rr_data; } ;
struct dns_msg {int dummy; } ;
struct auth_zone {int /*<<< orphan*/  name; } ;
struct auth_rrset {struct packed_rrset_data* data; } ;
struct auth_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_CNAME ; 
 int /*<<< orphan*/  MAX_CNAME_CHAIN ; 
 struct auth_rrset* az_domain_rrset (struct auth_data*,int /*<<< orphan*/ ) ; 
 struct auth_data* az_find_name (struct auth_zone*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  dname_subdomain_c (scalar_t__,int /*<<< orphan*/ ) ; 
 size_t dname_valid (scalar_t__,int) ; 
 int /*<<< orphan*/  msg_add_rrset_an (struct auth_zone*,struct regional*,struct dns_msg*,struct auth_data*,struct auth_rrset*) ; 

__attribute__((used)) static int
follow_cname_chain(struct auth_zone* z, uint16_t qtype,
	struct regional* region, struct dns_msg* msg,
	struct packed_rrset_data* d)
{
	int maxchain = 0;
	/* see if we can add the target of the CNAME into the answer */
	while(maxchain++ < MAX_CNAME_CHAIN) {
		struct auth_data* node;
		struct auth_rrset* rrset;
		size_t clen;
		/* d has cname rdata */
		if(d->count == 0) break; /* no CNAME */
		if(d->rr_len[0] < 2+1) break; /* too small */
		if((clen=dname_valid(d->rr_data[0]+2, d->rr_len[0]-2))==0)
			break; /* malformed */
		if(!dname_subdomain_c(d->rr_data[0]+2, z->name))
			break; /* target out of zone */
		if((node = az_find_name(z, d->rr_data[0]+2, clen))==NULL)
			break; /* no such target name */
		if((rrset=az_domain_rrset(node, qtype))!=NULL) {
			/* done we found the target */
			if(!msg_add_rrset_an(z, region, msg, node, rrset))
				return 0;
			break;
		}
		if((rrset=az_domain_rrset(node, LDNS_RR_TYPE_CNAME))==NULL)
			break; /* no further CNAME chain, notype */
		if(!msg_add_rrset_an(z, region, msg, node, rrset)) return 0;
		d = rrset->data;
	}
	return 1;
}