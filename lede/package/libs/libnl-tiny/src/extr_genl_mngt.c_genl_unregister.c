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
struct nl_cache_ops {TYPE_1__* co_genl; } ;
struct TYPE_2__ {int /*<<< orphan*/  o_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  nl_cache_mngt_unregister (struct nl_cache_ops*) ; 
 int /*<<< orphan*/  nl_list_del (int /*<<< orphan*/ *) ; 

void genl_unregister(struct nl_cache_ops *ops)
{
	nl_cache_mngt_unregister(ops);
	nl_list_del(&ops->co_genl->o_list);
}