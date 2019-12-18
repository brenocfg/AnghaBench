#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct cache_policy_ {int dummy; } ;
struct TYPE_11__ {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_12__ {TYPE_5__ max_lifetime; } ;
struct TYPE_10__ {scalar_t__ tv_sec; } ;
struct cache_mp_entry_ {TYPE_6__ mp_params; TYPE_4__ last_request_time; } ;
struct cache_entry_ {TYPE_1__* params; } ;
struct TYPE_8__ {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_9__ {scalar_t__ max_elemsize; TYPE_2__ max_lifetime; } ;
struct cache_common_entry_ {int policies_size; scalar_t__ items_size; struct cache_policy_** policies; TYPE_3__ common_params; } ;
struct TYPE_7__ {scalar_t__ entry_type; } ;

/* Variables and functions */
 scalar_t__ CET_COMMON ; 
 int /*<<< orphan*/  cache_elemsize_common_continue_func ; 
 int /*<<< orphan*/  cache_lifetime_common_continue_func ; 
 int /*<<< orphan*/  clear_cache_entry (struct cache_entry_*) ; 
 int /*<<< orphan*/  flush_cache_policy (struct cache_common_entry_*,struct cache_policy_*,struct cache_policy_*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
flush_cache_entry(struct cache_entry_ *entry)
{
	struct cache_mp_entry_		*mp_entry;
	struct cache_common_entry_	*common_entry;
	struct cache_policy_ *policy, *connected_policy;

	connected_policy = NULL;
	if (entry->params->entry_type == CET_COMMON) {
		common_entry = (struct cache_common_entry_ *)entry;
		if ((common_entry->common_params.max_lifetime.tv_sec != 0) ||
		    (common_entry->common_params.max_lifetime.tv_usec != 0)) {

			policy = common_entry->policies[0];
			if (common_entry->policies_size > 1)
				connected_policy = common_entry->policies[1];

			flush_cache_policy(common_entry, policy,
				connected_policy,
				cache_lifetime_common_continue_func);
		}


		if ((common_entry->common_params.max_elemsize != 0) &&
			common_entry->items_size >
			common_entry->common_params.max_elemsize) {

			if (common_entry->policies_size > 1) {
				policy = common_entry->policies[1];
				connected_policy = common_entry->policies[0];
			} else {
				policy = common_entry->policies[0];
				connected_policy = NULL;
			}

			flush_cache_policy(common_entry, policy,
				connected_policy,
				cache_elemsize_common_continue_func);
		}
	} else {
		mp_entry = (struct cache_mp_entry_ *)entry;

		if ((mp_entry->mp_params.max_lifetime.tv_sec != 0)
			|| (mp_entry->mp_params.max_lifetime.tv_usec != 0)) {

			if (mp_entry->last_request_time.tv_sec -
				mp_entry->last_request_time.tv_sec >
				mp_entry->mp_params.max_lifetime.tv_sec)
				clear_cache_entry(entry);
		}
	}
}