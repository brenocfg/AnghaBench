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
typedef  scalar_t__ time_t ;
struct TYPE_3__ {scalar_t__ data; } ;
struct ub_packed_rrset_key {TYPE_1__ entry; } ;
struct regional {int dummy; } ;
struct query_info {int dummy; } ;
struct packed_rrset_data {scalar_t__ ttl; } ;
struct dns_msg {TYPE_2__* rep; } ;
struct TYPE_4__ {int qdcount; int an_numrrsets; int rrset_count; int /*<<< orphan*/ * rrsets; scalar_t__ ar_numrrsets; scalar_t__ ns_numrrsets; int /*<<< orphan*/  security; scalar_t__ ttl; scalar_t__ serve_expired_ttl; int /*<<< orphan*/  prefetch_ttl; scalar_t__ authoritative; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_QR ; 
 int /*<<< orphan*/  PREFETCH_TTL_CALC (scalar_t__) ; 
 scalar_t__ SERVE_EXPIRED_TTL ; 
 struct dns_msg* gen_dns_msg (struct regional*,struct query_info*,int) ; 
 int /*<<< orphan*/  packed_rrset_copy_region (struct ub_packed_rrset_key*,struct regional*,scalar_t__) ; 
 int /*<<< orphan*/  sec_status_unchecked ; 

__attribute__((used)) static struct dns_msg*
rrset_msg(struct ub_packed_rrset_key* rrset, struct regional* region, 
	time_t now, struct query_info* q)
{
	struct dns_msg* msg;
	struct packed_rrset_data* d = (struct packed_rrset_data*)
		rrset->entry.data;
	if(now > d->ttl)
		return NULL;
	msg = gen_dns_msg(region, q, 1); /* only the CNAME (or other) RRset */
	if(!msg)
		return NULL;
	msg->rep->flags = BIT_QR; /* reply, no AA, no error */
        msg->rep->authoritative = 0; /* reply stored in cache can't be authoritative */
	msg->rep->qdcount = 1;
	msg->rep->ttl = d->ttl - now;
	msg->rep->prefetch_ttl = PREFETCH_TTL_CALC(msg->rep->ttl);
	msg->rep->serve_expired_ttl = msg->rep->ttl + SERVE_EXPIRED_TTL;
	msg->rep->security = sec_status_unchecked;
	msg->rep->an_numrrsets = 1;
	msg->rep->ns_numrrsets = 0;
	msg->rep->ar_numrrsets = 0;
	msg->rep->rrset_count = 1;
	msg->rep->rrsets[0] = packed_rrset_copy_region(rrset, region, now);
	if(!msg->rep->rrsets[0]) /* copy CNAME */
		return NULL;
	return msg;
}