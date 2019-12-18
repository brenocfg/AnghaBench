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
struct packed_rrset_data {scalar_t__ count; int* rr_len; int* rr_data; } ;
struct auth_zone {int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; } ;
struct auth_xfer {int have_zone; void* expiry; void* retry; void* refresh; void* serial; } ;
struct auth_rrset {struct packed_rrset_data* data; } ;
struct auth_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_SOA ; 
 struct auth_rrset* az_domain_rrset (struct auth_data*,int /*<<< orphan*/ ) ; 
 struct auth_data* az_find_name (struct auth_zone*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* sldns_read_uint32 (int) ; 

__attribute__((used)) static int
xfr_find_soa(struct auth_zone* z, struct auth_xfer* xfr)
{
	struct auth_data* apex;
	struct auth_rrset* soa;
	struct packed_rrset_data* d;
	apex = az_find_name(z, z->name, z->namelen);
	if(!apex) return 0;
	soa = az_domain_rrset(apex, LDNS_RR_TYPE_SOA);
	if(!soa || soa->data->count==0)
		return 0; /* no RRset or no RRs in rrset */
	if(soa->data->rr_len[0] < 2+4*5) return 0; /* SOA too short */
	/* SOA record ends with serial, refresh, retry, expiry, minimum,
	 * as 4 byte fields */
	d = soa->data;
	xfr->have_zone = 1;
	xfr->serial = sldns_read_uint32(d->rr_data[0]+(d->rr_len[0]-20));
	xfr->refresh = sldns_read_uint32(d->rr_data[0]+(d->rr_len[0]-16));
	xfr->retry = sldns_read_uint32(d->rr_data[0]+(d->rr_len[0]-12));
	xfr->expiry = sldns_read_uint32(d->rr_data[0]+(d->rr_len[0]-8));
	/* soa minimum at d->rr_len[0]-4 */
	return 1;
}