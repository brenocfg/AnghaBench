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
struct cache_policy_item_ {int dummy; } ;
struct TYPE_2__ {scalar_t__ satisf_elemsize; } ;
struct cache_common_entry_ {scalar_t__ items_size; TYPE_1__ common_params; } ;

/* Variables and functions */

__attribute__((used)) static int
cache_elemsize_common_continue_func(struct cache_common_entry_ *entry,
	struct cache_policy_item_ *item)
{

	return ((entry->items_size > entry->common_params.satisf_elemsize) ? 1
    		: 0);
}