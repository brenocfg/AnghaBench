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
typedef  int /*<<< orphan*/  wc ;
typedef  int uint8_t ;
struct regional {int dummy; } ;
struct query_info {int* qname; size_t qname_len; scalar_t__ qclass; scalar_t__ qtype; } ;
struct dns_msg {int dummy; } ;
struct auth_zone {int dummy; } ;
struct auth_rrset {int dummy; } ;
struct auth_data {int dummy; } ;

/* Variables and functions */
 int LDNS_MAX_DOMAINLEN ; 
 int /*<<< orphan*/  az_find_domain (struct auth_zone*,struct query_info*,int*,struct auth_data**) ; 
 struct auth_rrset* az_find_nsec_cover (struct auth_zone*,struct auth_data**) ; 
 int /*<<< orphan*/  memmove (int*,int*,size_t) ; 
 int /*<<< orphan*/  msg_add_rrset_ns (struct auth_zone*,struct regional*,struct dns_msg*,struct auth_data*,struct auth_rrset*) ; 

__attribute__((used)) static int
az_nsec_wildcard_denial(struct auth_zone* z, struct regional* region,
	struct dns_msg* msg, uint8_t* cenm, size_t cenmlen)
{
	struct query_info qinfo;
	int node_exact;
	struct auth_data* node;
	struct auth_rrset* nsec;
	uint8_t wc[LDNS_MAX_DOMAINLEN];
	if(cenmlen+2 > sizeof(wc))
		return 0; /* result would be too long */
	wc[0] = 1; /* length of wildcard label */
	wc[1] = (uint8_t)'*'; /* wildcard label */
	memmove(wc+2, cenm, cenmlen);

	/* we have '*.ce' in wc wildcard name buffer */
	/* get nsec cover for that */
	qinfo.qname = wc;
	qinfo.qname_len = cenmlen+2;
	qinfo.qtype = 0;
	qinfo.qclass = 0;
	az_find_domain(z, &qinfo, &node_exact, &node);
	if((nsec=az_find_nsec_cover(z, &node)) != NULL) {
		if(!msg_add_rrset_ns(z, region, msg, node, nsec)) return 0;
	}
	return 1;
}