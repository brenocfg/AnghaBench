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
typedef  void* time_t ;
struct ub_packed_rrset_key {int dummy; } ;
struct rrset_ref {int dummy; } ;
struct reply_info {size_t qdcount; size_t an_numrrsets; size_t ns_numrrsets; size_t ar_numrrsets; size_t rrset_count; int security; struct ub_packed_rrset_key** ref; struct ub_packed_rrset_key** rrsets; scalar_t__ authoritative; void* serve_expired_ttl; void* prefetch_ttl; void* ttl; int /*<<< orphan*/  flags; } ;
struct regional {int dummy; } ;
typedef  enum sec_status { ____Placeholder_sec_status } sec_status ;

/* Variables and functions */
 size_t RR_COUNT_MAX ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memset (struct ub_packed_rrset_key**,int /*<<< orphan*/ ,int) ; 
 scalar_t__ regional_alloc (struct regional*,size_t) ; 

struct reply_info*
construct_reply_info_base(struct regional* region, uint16_t flags, size_t qd,
	time_t ttl, time_t prettl, time_t expttl, size_t an, size_t ns,
	size_t ar, size_t total, enum sec_status sec)
{
	struct reply_info* rep;
	/* rrset_count-1 because the first ref is part of the struct. */
	size_t s = sizeof(struct reply_info) - sizeof(struct rrset_ref) +
		sizeof(struct ub_packed_rrset_key*) * total;
	if(total >= RR_COUNT_MAX) return NULL; /* sanity check on numRRS*/
	if(region)
		rep = (struct reply_info*)regional_alloc(region, s);
	else	rep = (struct reply_info*)malloc(s + 
			sizeof(struct rrset_ref) * (total));
	if(!rep) 
		return NULL;
	rep->flags = flags;
	rep->qdcount = qd;
	rep->ttl = ttl;
	rep->prefetch_ttl = prettl;
	rep->serve_expired_ttl = expttl;
	rep->an_numrrsets = an;
	rep->ns_numrrsets = ns;
	rep->ar_numrrsets = ar;
	rep->rrset_count = total;
	rep->security = sec;
	rep->authoritative = 0;
	/* array starts after the refs */
	if(region)
		rep->rrsets = (struct ub_packed_rrset_key**)&(rep->ref[0]);
	else	rep->rrsets = (struct ub_packed_rrset_key**)&(rep->ref[total]);
	/* zero the arrays to assist cleanup in case of malloc failure */
	memset( rep->rrsets, 0, sizeof(struct ub_packed_rrset_key*) * total);
	if(!region)
		memset( &rep->ref[0], 0, sizeof(struct rrset_ref) * total);
	return rep;
}