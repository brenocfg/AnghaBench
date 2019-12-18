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
struct ipv6_entry_scope {scalar_t__ status; int* res; unsigned int scope; scalar_t__ addr; } ;
struct in6_addr {scalar_t__* s6_addr; } ;
typedef  int ev_uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 scalar_t__ BAD ; 
 int /*<<< orphan*/  TT_BLATHER (char*) ; 
 int /*<<< orphan*/  TT_FAIL (char*) ; 
 int evutil_inet_pton_scope (int /*<<< orphan*/ ,scalar_t__,struct in6_addr*,unsigned int*) ; 
 struct ipv6_entry_scope* ipv6_entries_scope ; 

__attribute__((used)) static void
regress_ipv6_parse_scope(void *ptr)
{
#ifdef AF_INET6
	int i, j;
	unsigned if_scope;

	for (i = 0; ipv6_entries_scope[i].addr; ++i) {
		struct ipv6_entry_scope *ent = &ipv6_entries_scope[i];
		struct in6_addr in6;
		int r;
		r = evutil_inet_pton_scope(AF_INET6, ent->addr, &in6,
			&if_scope);
		if (r == 0) {
			if (ent->status != BAD)
				TT_FAIL(("%s did not parse, but it's a good address!",
					ent->addr));
			continue;
		}
		if (ent->status == BAD) {
			TT_FAIL(("%s parsed, but we expected an error", ent->addr));
			continue;
		}
		for (j = 0; j < 4; ++j) {
			/* Can't use s6_addr32 here; some don't have it. */
			ev_uint32_t u =
			    ((ev_uint32_t)in6.s6_addr[j*4  ] << 24) |
			    ((ev_uint32_t)in6.s6_addr[j*4+1] << 16) |
			    ((ev_uint32_t)in6.s6_addr[j*4+2] << 8) |
			    ((ev_uint32_t)in6.s6_addr[j*4+3]);
			if (u != ent->res[j]) {
				TT_FAIL(("%s did not parse as expected.", ent->addr));
				continue;
			}
		}
		if (if_scope != ent->scope) {
			TT_FAIL(("%s did not parse as expected.", ent->addr));
			continue;
		}
	}
#else
	TT_BLATHER(("Skipping IPv6 address parsing."));
#endif
}