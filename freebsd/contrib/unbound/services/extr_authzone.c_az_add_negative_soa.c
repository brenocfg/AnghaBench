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
typedef  scalar_t__ uint32_t ;
typedef  void* time_t ;
struct regional {int dummy; } ;
struct packed_rrset_data {scalar_t__ count; int* rr_len; int* rr_data; void** rr_ttl; void* ttl; } ;
struct dns_msg {TYPE_2__* rep; } ;
struct auth_zone {int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; } ;
struct auth_rrset {int dummy; } ;
struct auth_data {int dummy; } ;
struct TYPE_4__ {scalar_t__ data; } ;
struct TYPE_6__ {TYPE_1__ entry; } ;
struct TYPE_5__ {int rrset_count; scalar_t__ ttl; scalar_t__ serve_expired_ttl; int /*<<< orphan*/  prefetch_ttl; TYPE_3__** rrsets; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_SOA ; 
 int /*<<< orphan*/  PREFETCH_TTL_CALC (scalar_t__) ; 
 scalar_t__ SERVE_EXPIRED_TTL ; 
 struct auth_rrset* az_domain_rrset (struct auth_data*,int /*<<< orphan*/ ) ; 
 struct auth_data* az_find_name (struct auth_zone*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_rrset_ttl (TYPE_3__*) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  msg_add_rrset_ns (struct auth_zone*,struct regional*,struct dns_msg*,struct auth_data*,struct auth_rrset*) ; 
 scalar_t__ sldns_read_uint32 (int) ; 

__attribute__((used)) static int
az_add_negative_soa(struct auth_zone* z, struct regional* region,
	struct dns_msg* msg)
{
	uint32_t minimum;
	struct packed_rrset_data* d;
	struct auth_rrset* soa;
	struct auth_data* apex = az_find_name(z, z->name, z->namelen);
	if(!apex) return 0;
	soa = az_domain_rrset(apex, LDNS_RR_TYPE_SOA);
	if(!soa) return 0;
	/* must be first to put in message; we want to fix the TTL with
	 * one RRset here, otherwise we'd need to loop over the RRs to get
	 * the resulting lower TTL */
	log_assert(msg->rep->rrset_count == 0);
	if(!msg_add_rrset_ns(z, region, msg, apex, soa)) return 0;
	/* fixup TTL */
	d = (struct packed_rrset_data*)msg->rep->rrsets[msg->rep->rrset_count-1]->entry.data;
	/* last 4 bytes are minimum ttl in network format */
	if(d->count == 0) return 0;
	if(d->rr_len[0] < 2+4) return 0;
	minimum = sldns_read_uint32(d->rr_data[0]+(d->rr_len[0]-4));
	d->ttl = (time_t)minimum;
	d->rr_ttl[0] = (time_t)minimum;
	msg->rep->ttl = get_rrset_ttl(msg->rep->rrsets[0]);
	msg->rep->prefetch_ttl = PREFETCH_TTL_CALC(msg->rep->ttl);
	msg->rep->serve_expired_ttl = msg->rep->ttl + SERVE_EXPIRED_TTL;
	return 1;
}