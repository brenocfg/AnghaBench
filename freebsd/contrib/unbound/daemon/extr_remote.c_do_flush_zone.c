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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int* now; TYPE_2__* key_cache; int /*<<< orphan*/ * msg_cache; TYPE_1__* rrset_cache; } ;
struct worker {TYPE_3__ env; } ;
struct del_info {size_t len; int labs; int expired; scalar_t__ num_keys; scalar_t__ num_msgs; scalar_t__ num_rrsets; int /*<<< orphan*/ * name; struct worker* worker; } ;
struct TYPE_5__ {int /*<<< orphan*/ * slab; } ;
struct TYPE_4__ {int /*<<< orphan*/  table; } ;
typedef  int /*<<< orphan*/  RES ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_arg_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,size_t*,int*) ; 
 int /*<<< orphan*/  slabhash_traverse (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,struct del_info*) ; 
 int /*<<< orphan*/  ssl_printf (int /*<<< orphan*/ *,char*,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  zone_del_kcache ; 
 int /*<<< orphan*/  zone_del_msg ; 
 int /*<<< orphan*/  zone_del_rrset ; 

__attribute__((used)) static void
do_flush_zone(RES* ssl, struct worker* worker, char* arg)
{
	uint8_t* nm;
	int nmlabs;
	size_t nmlen;
	struct del_info inf;
	if(!parse_arg_name(ssl, arg, &nm, &nmlen, &nmlabs))
		return;
	/* delete all RRs and key entries from zone */
	/* what we do is to set them all expired */
	inf.worker = worker;
	inf.name = nm;
	inf.len = nmlen;
	inf.labs = nmlabs;
	inf.expired = *worker->env.now;
	inf.expired -= 3; /* handle 3 seconds skew between threads */
	inf.num_rrsets = 0;
	inf.num_msgs = 0;
	inf.num_keys = 0;
	slabhash_traverse(&worker->env.rrset_cache->table, 1, 
		&zone_del_rrset, &inf);

	slabhash_traverse(worker->env.msg_cache, 1, &zone_del_msg, &inf);

	/* and validator cache */
	if(worker->env.key_cache) {
		slabhash_traverse(worker->env.key_cache->slab, 1, 
			&zone_del_kcache, &inf);
	}

	free(nm);

	(void)ssl_printf(ssl, "ok removed %lu rrsets, %lu messages "
		"and %lu key entries\n", (unsigned long)inf.num_rrsets, 
		(unsigned long)inf.num_msgs, (unsigned long)inf.num_keys);
}