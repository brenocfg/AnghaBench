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
struct reply_info {int /*<<< orphan*/ * rrsets; int /*<<< orphan*/  serve_expired_ttl; int /*<<< orphan*/  prefetch_ttl; int /*<<< orphan*/  ttl; int /*<<< orphan*/  qdcount; int /*<<< orphan*/  flags; } ;
struct regional {int dummy; } ;

/* Variables and functions */
 struct reply_info* construct_reply_info_base (struct regional*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reply_info_alloc_rrset_keys (struct reply_info*,int /*<<< orphan*/ *,struct regional*) ; 
 int /*<<< orphan*/  sec_status_insecure ; 

__attribute__((used)) static struct reply_info *
make_new_reply_info(const struct reply_info* rep, struct regional* region,
	size_t an_numrrsets, size_t copy_rrsets)
{
	struct reply_info* new_rep;
	size_t i;

	/* create a base struct.  we specify 'insecure' security status as
	 * the modified response won't be DNSSEC-valid.  In our faked response
	 * the authority and additional sections will be empty (except possible
	 * EDNS0 OPT RR in the additional section appended on sending it out),
	 * so the total number of RRsets is an_numrrsets. */
	new_rep = construct_reply_info_base(region, rep->flags,
		rep->qdcount, rep->ttl, rep->prefetch_ttl,
		rep->serve_expired_ttl, an_numrrsets, 0, 0, an_numrrsets,
		sec_status_insecure);
	if(!new_rep)
		return NULL;
	if(!reply_info_alloc_rrset_keys(new_rep, NULL, region))
		return NULL;
	for(i=0; i<copy_rrsets; i++)
		new_rep->rrsets[i] = rep->rrsets[i];

	return new_rep;
}