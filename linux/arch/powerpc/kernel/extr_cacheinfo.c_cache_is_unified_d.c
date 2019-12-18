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
struct device_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  size_prop; } ;

/* Variables and functions */
 int CACHE_TYPE_UNIFIED ; 
 size_t CACHE_TYPE_UNIFIED_D ; 
 TYPE_1__* cache_type_info ; 
 scalar_t__ of_get_property (struct device_node const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cache_is_unified_d(const struct device_node *np)
{
	return of_get_property(np,
		cache_type_info[CACHE_TYPE_UNIFIED_D].size_prop, NULL) ?
		CACHE_TYPE_UNIFIED_D : CACHE_TYPE_UNIFIED;
}