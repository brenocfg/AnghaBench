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
struct reply_info {scalar_t__ ttl; scalar_t__ prefetch_ttl; scalar_t__ serve_expired_ttl; } ;
struct TYPE_2__ {int /*<<< orphan*/  qname; } ;
struct msgreply_entry {TYPE_1__ key; } ;
struct lruhash_entry {scalar_t__ data; scalar_t__ key; } ;
struct del_info {scalar_t__ expired; int /*<<< orphan*/  num_msgs; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ dname_subdomain_c (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
zone_del_msg(struct lruhash_entry* e, void* arg)
{
	/* entry is locked */
	struct del_info* inf = (struct del_info*)arg;
	struct msgreply_entry* k = (struct msgreply_entry*)e->key;
	if(dname_subdomain_c(k->key.qname, inf->name)) {
		struct reply_info* d = (struct reply_info*)e->data;
		if(d->ttl > inf->expired) {
			d->ttl = inf->expired;
			d->prefetch_ttl = inf->expired;
			d->serve_expired_ttl = inf->expired;
			inf->num_msgs++;
		}
	}
}