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
typedef  int /*<<< orphan*/  uint8_t ;
struct query_info {size_t qname_len; int /*<<< orphan*/ * qname; } ;
struct nsec3_filter {int /*<<< orphan*/  zone; } ;
struct module_env {int dummy; } ;
struct ce_response {size_t ce_len; int /*<<< orphan*/ * ce; int /*<<< orphan*/  ce_rr; int /*<<< orphan*/  ce_rrset; } ;
typedef  int /*<<< orphan*/  rbtree_type ;

/* Variables and functions */
 int /*<<< orphan*/  dname_remove_label (int /*<<< orphan*/ **,size_t*) ; 
 scalar_t__ dname_subdomain_c (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ find_matching_nsec3 (struct module_env*,struct nsec3_filter*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nsec3_find_closest_encloser(struct module_env* env, struct nsec3_filter* flt, 
	rbtree_type* ct, struct query_info* qinfo, struct ce_response* ce)
{
	uint8_t* nm = qinfo->qname;
	size_t nmlen = qinfo->qname_len;

	/* This scans from longest name to shortest, so the first match 
	 * we find is the only viable candidate. */

	/* (David:) FIXME: modify so that the NSEC3 matching the zone apex need 
	 * not be present. (Mark Andrews idea).
	 * (Wouter:) But make sure you check for DNAME bit in zone apex,
	 * if the NSEC3 you find is the only NSEC3 in the zone, then this
	 * may be the case. */

	while(dname_subdomain_c(nm, flt->zone)) {
		if(find_matching_nsec3(env, flt, ct, nm, nmlen, 
			&ce->ce_rrset, &ce->ce_rr)) {
			ce->ce = nm;
			ce->ce_len = nmlen;
			return 1;
		}
		dname_remove_label(&nm, &nmlen);
	}
	return 0;
}