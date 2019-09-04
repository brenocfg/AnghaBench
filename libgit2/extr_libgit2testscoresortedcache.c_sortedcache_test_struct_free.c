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
struct TYPE_2__ {scalar_t__ smaller_value; } ;
typedef  TYPE_1__ sortedcache_test_struct ;

/* Variables and functions */

__attribute__((used)) static void sortedcache_test_struct_free(void *payload, void *item_)
{
	sortedcache_test_struct *item = item_;
	int *count = payload;
	(*count)++;
	item->smaller_value = 0;
}