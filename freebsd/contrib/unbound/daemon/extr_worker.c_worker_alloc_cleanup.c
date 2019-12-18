#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * msg_cache; TYPE_1__* rrset_cache; } ;
struct worker {TYPE_2__ env; } ;
struct TYPE_3__ {int /*<<< orphan*/  table; } ;

/* Variables and functions */
 int /*<<< orphan*/  slabhash_clear (int /*<<< orphan*/ *) ; 

void 
worker_alloc_cleanup(void* arg)
{
	struct worker* worker = (struct worker*)arg;
	slabhash_clear(&worker->env.rrset_cache->table);
	slabhash_clear(worker->env.msg_cache);
}