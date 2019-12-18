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
struct regional {int dummy; } ;
struct delegpt_ns {int /*<<< orphan*/  done_pside6; int /*<<< orphan*/  done_pside4; int /*<<< orphan*/  got6; int /*<<< orphan*/  got4; int /*<<< orphan*/  resolved; int /*<<< orphan*/  lame; int /*<<< orphan*/  name; struct delegpt_ns* next; } ;
struct delegpt_addr {int /*<<< orphan*/  tls_auth_name; int /*<<< orphan*/  lame; int /*<<< orphan*/  bogus; int /*<<< orphan*/  addrlen; int /*<<< orphan*/  addr; struct delegpt_addr* next_target; } ;
struct delegpt {struct delegpt_addr* target_list; struct delegpt_ns* nslist; int /*<<< orphan*/  ssl_upstream; int /*<<< orphan*/  has_parent_side_NS; int /*<<< orphan*/  bogus; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  delegpt_add_addr (struct delegpt*,struct regional*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delegpt_add_ns (struct delegpt*,struct regional*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct delegpt* delegpt_create (struct regional*) ; 
 int /*<<< orphan*/  delegpt_set_name (struct delegpt*,struct regional*,int /*<<< orphan*/ ) ; 

struct delegpt* delegpt_copy(struct delegpt* dp, struct regional* region)
{
	struct delegpt* copy = delegpt_create(region);
	struct delegpt_ns* ns;
	struct delegpt_addr* a;
	if(!copy) 
		return NULL;
	if(!delegpt_set_name(copy, region, dp->name))
		return NULL;
	copy->bogus = dp->bogus;
	copy->has_parent_side_NS = dp->has_parent_side_NS;
	copy->ssl_upstream = dp->ssl_upstream;
	for(ns = dp->nslist; ns; ns = ns->next) {
		if(!delegpt_add_ns(copy, region, ns->name, ns->lame))
			return NULL;
		copy->nslist->resolved = ns->resolved;
		copy->nslist->got4 = ns->got4;
		copy->nslist->got6 = ns->got6;
		copy->nslist->done_pside4 = ns->done_pside4;
		copy->nslist->done_pside6 = ns->done_pside6;
	}
	for(a = dp->target_list; a; a = a->next_target) {
		if(!delegpt_add_addr(copy, region, &a->addr, a->addrlen, 
			a->bogus, a->lame, a->tls_auth_name))
			return NULL;
	}
	return copy;
}