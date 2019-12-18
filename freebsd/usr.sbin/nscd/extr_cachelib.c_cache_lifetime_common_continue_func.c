#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ tv_sec; } ;
struct TYPE_5__ {scalar_t__ tv_sec; } ;
struct cache_policy_item_ {TYPE_2__ creation_time; TYPE_1__ last_request_time; } ;
struct TYPE_7__ {scalar_t__ tv_sec; } ;
struct TYPE_8__ {TYPE_3__ max_lifetime; } ;
struct cache_common_entry_ {TYPE_4__ common_params; } ;

/* Variables and functions */

__attribute__((used)) static int
cache_lifetime_common_continue_func(struct cache_common_entry_ *entry,
	struct cache_policy_item_ *item)
{

	return ((item->last_request_time.tv_sec - item->creation_time.tv_sec >
		entry->common_params.max_lifetime.tv_sec) ? 1: 0);
}