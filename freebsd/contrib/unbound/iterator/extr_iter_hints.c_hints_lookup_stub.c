#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct iter_hints_stub {TYPE_1__* dp; scalar_t__ noprime; } ;
struct iter_hints {int /*<<< orphan*/  tree; } ;
struct delegpt {int /*<<< orphan*/  namelabs; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int namelabs; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int dname_count_size_labels (int /*<<< orphan*/ *,size_t*) ; 
 scalar_t__ dname_strict_subdomain (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ name_tree_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ) ; 
 scalar_t__ query_dname_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct iter_hints_stub* 
hints_lookup_stub(struct iter_hints* hints, uint8_t* qname, 
	uint16_t qclass, struct delegpt* cache_dp)
{
	size_t len;
	int labs;
	struct iter_hints_stub *r;

	/* first lookup the stub */
	labs = dname_count_size_labels(qname, &len);
	r = (struct iter_hints_stub*)name_tree_lookup(&hints->tree, qname,
		len, labs, qclass);
	if(!r) return NULL;

	/* If there is no cache (root prime situation) */
	if(cache_dp == NULL) {
		if(r->dp->namelabs != 1)
			return r; /* no cache dp, use any non-root stub */
		return NULL;
	}

	/*
	 * If the stub is same as the delegation we got
	 * And has noprime set, we need to 'prime' to use this stub instead.
	 */
	if(r->noprime && query_dname_compare(cache_dp->name, r->dp->name)==0)
		return r; /* use this stub instead of cached dp */
	
	/* 
	 * If our cached delegation point is above the hint, we need to prime.
	 */
	if(dname_strict_subdomain(r->dp->name, r->dp->namelabs,
		cache_dp->name, cache_dp->namelabs))
		return r; /* need to prime this stub */
	return NULL;
}