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
struct lruhash_entry {scalar_t__ data; scalar_t__ key; } ;
struct infra_key {int /*<<< orphan*/  addrlen; int /*<<< orphan*/  addr; } ;
struct infra_data {scalar_t__ ttl; int /*<<< orphan*/  rtt; scalar_t__ timeout_other; scalar_t__ timeout_AAAA; scalar_t__ timeout_A; scalar_t__ probedelay; } ;
struct del_info {scalar_t__ expired; int /*<<< orphan*/  num_keys; int /*<<< orphan*/  addrlen; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtt_init (int /*<<< orphan*/ *) ; 
 scalar_t__ sockaddr_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
infra_del_host(struct lruhash_entry* e, void* arg)
{
	/* entry is locked */
	struct del_info* inf = (struct del_info*)arg;
	struct infra_key* k = (struct infra_key*)e->key;
	if(sockaddr_cmp(&inf->addr, inf->addrlen, &k->addr, k->addrlen) == 0) {
		struct infra_data* d = (struct infra_data*)e->data;
		d->probedelay = 0;
		d->timeout_A = 0;
		d->timeout_AAAA = 0;
		d->timeout_other = 0;
		rtt_init(&d->rtt);
		if(d->ttl > inf->expired) {
			d->ttl = inf->expired;
			inf->num_keys++;
		}
	}
}