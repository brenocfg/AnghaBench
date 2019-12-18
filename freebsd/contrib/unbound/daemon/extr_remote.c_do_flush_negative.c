#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int* now; TYPE_2__* key_cache; int /*<<< orphan*/ * msg_cache; TYPE_1__* rrset_cache; } ;
struct worker {TYPE_3__ env; } ;
struct del_info {int expired; scalar_t__ num_keys; scalar_t__ num_msgs; scalar_t__ num_rrsets; struct worker* worker; } ;
struct TYPE_5__ {int /*<<< orphan*/ * slab; } ;
struct TYPE_4__ {int /*<<< orphan*/  table; } ;
typedef  int /*<<< orphan*/  RES ;

/* Variables and functions */
 int /*<<< orphan*/  negative_del_kcache ; 
 int /*<<< orphan*/  negative_del_msg ; 
 int /*<<< orphan*/  negative_del_rrset ; 
 int /*<<< orphan*/  slabhash_traverse (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,struct del_info*) ; 
 int /*<<< orphan*/  ssl_printf (int /*<<< orphan*/ *,char*,unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static void
do_flush_negative(RES* ssl, struct worker* worker)
{
	struct del_info inf;
	/* what we do is to set them all expired */
	inf.worker = worker;
	inf.expired = *worker->env.now;
	inf.expired -= 3; /* handle 3 seconds skew between threads */
	inf.num_rrsets = 0;
	inf.num_msgs = 0;
	inf.num_keys = 0;
	slabhash_traverse(&worker->env.rrset_cache->table, 1, 
		&negative_del_rrset, &inf);

	slabhash_traverse(worker->env.msg_cache, 1, &negative_del_msg, &inf);

	/* and validator cache */
	if(worker->env.key_cache) {
		slabhash_traverse(worker->env.key_cache->slab, 1, 
			&negative_del_kcache, &inf);
	}

	(void)ssl_printf(ssl, "ok removed %lu rrsets, %lu messages "
		"and %lu key entries\n", (unsigned long)inf.num_rrsets, 
		(unsigned long)inf.num_msgs, (unsigned long)inf.num_keys);
}