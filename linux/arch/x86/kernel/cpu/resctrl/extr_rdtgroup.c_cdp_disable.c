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
struct rdt_resource {int alloc_enabled; int alloc_capable; } ;

/* Variables and functions */
 struct rdt_resource* rdt_resources_all ; 
 int /*<<< orphan*/  set_cache_qos_cfg (int,int) ; 

__attribute__((used)) static void cdp_disable(int level, int data_type, int code_type)
{
	struct rdt_resource *r = &rdt_resources_all[level];

	r->alloc_enabled = r->alloc_capable;

	if (rdt_resources_all[data_type].alloc_enabled) {
		rdt_resources_all[data_type].alloc_enabled = false;
		rdt_resources_all[code_type].alloc_enabled = false;
		set_cache_qos_cfg(level, false);
	}
}