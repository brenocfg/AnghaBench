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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  scalar_t__ time_t ;
struct reply_info {int /*<<< orphan*/  prefetch_ttl; } ;
struct query_info {int /*<<< orphan*/  qclass; int /*<<< orphan*/  qtype; int /*<<< orphan*/  qname_len; int /*<<< orphan*/  qname; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; scalar_t__ data; } ;
struct msgreply_entry {TYPE_1__ entry; } ;
struct module_env {int /*<<< orphan*/ * now; } ;

/* Variables and functions */
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 struct msgreply_entry* msg_cache_lookup (struct module_env*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int 
dns_cache_prefetch_adjust(struct module_env* env, struct query_info* qinfo,
        time_t adjust, uint16_t flags)
{
	struct msgreply_entry* msg;
	msg = msg_cache_lookup(env, qinfo->qname, qinfo->qname_len,
		qinfo->qtype, qinfo->qclass, flags, *env->now, 1);
	if(msg) {
		struct reply_info* rep = (struct reply_info*)msg->entry.data;
		if(rep) {
			rep->prefetch_ttl += adjust;
			lock_rw_unlock(&msg->entry.lock);
			return 1;
		}
		lock_rw_unlock(&msg->entry.lock);
	}
	return 0;
}