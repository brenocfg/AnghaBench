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
struct trust_anchor {scalar_t__ numDS; scalar_t__ numDNSKEY; void* dnskey_rrset; void* ds_rrset; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_DNSKEY ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_DS ; 
 void* assemble_it (struct trust_anchor*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
anchors_assemble(struct trust_anchor* ta)
{
	if(ta->numDS > 0) {
		ta->ds_rrset = assemble_it(ta, ta->numDS, LDNS_RR_TYPE_DS);
		if(!ta->ds_rrset)
			return 0;
	}
	if(ta->numDNSKEY > 0) {
		ta->dnskey_rrset = assemble_it(ta, ta->numDNSKEY,
			LDNS_RR_TYPE_DNSKEY);
		if(!ta->dnskey_rrset)
			return 0;
	}
	return 1;
}