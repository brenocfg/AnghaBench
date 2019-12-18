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
struct reply_info {int /*<<< orphan*/  security; int /*<<< orphan*/  rrset_count; int /*<<< orphan*/  ar_numrrsets; int /*<<< orphan*/  ns_numrrsets; int /*<<< orphan*/  an_numrrsets; int /*<<< orphan*/  serve_expired_ttl; int /*<<< orphan*/  prefetch_ttl; int /*<<< orphan*/  ttl; int /*<<< orphan*/  qdcount; int /*<<< orphan*/  flags; } ;
struct regional {int dummy; } ;
struct alloc_cache {int dummy; } ;

/* Variables and functions */
 struct reply_info* construct_reply_info_base (struct regional*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repinfo_copy_rrsets (struct reply_info*,struct reply_info*,struct regional*) ; 
 int /*<<< orphan*/  reply_info_alloc_rrset_keys (struct reply_info*,struct alloc_cache*,struct regional*) ; 
 int /*<<< orphan*/  reply_info_parsedelete (struct reply_info*,struct alloc_cache*) ; 

struct reply_info* 
reply_info_copy(struct reply_info* rep, struct alloc_cache* alloc, 
	struct regional* region)
{
	struct reply_info* cp;
	cp = construct_reply_info_base(region, rep->flags, rep->qdcount, 
		rep->ttl, rep->prefetch_ttl, rep->serve_expired_ttl, 
		rep->an_numrrsets, rep->ns_numrrsets, rep->ar_numrrsets,
		rep->rrset_count, rep->security);
	if(!cp)
		return NULL;
	/* allocate ub_key structures special or not */
	if(!reply_info_alloc_rrset_keys(cp, alloc, region)) {
		if(!region)
			reply_info_parsedelete(cp, alloc);
		return NULL;
	}
	if(!repinfo_copy_rrsets(cp, rep, region)) {
		if(!region)
			reply_info_parsedelete(cp, alloc);
		return NULL;
	}
	return cp;
}