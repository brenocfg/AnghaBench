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
struct nl_cache_ops {int co_protocol; TYPE_1__* co_msgtypes; struct nl_cache_ops* co_next; } ;
struct TYPE_2__ {int mt_id; } ;

/* Variables and functions */
 struct nl_cache_ops* cache_ops ; 

struct nl_cache_ops *nl_cache_ops_associate(int protocol, int msgtype)
{
	int i;
	struct nl_cache_ops *ops;

	for (ops = cache_ops; ops; ops = ops->co_next) {
		if (ops->co_protocol != protocol)
			continue;

		for (i = 0; ops->co_msgtypes[i].mt_id >= 0; i++)
			if (ops->co_msgtypes[i].mt_id == msgtype)
				return ops;
	}

	return NULL;
}