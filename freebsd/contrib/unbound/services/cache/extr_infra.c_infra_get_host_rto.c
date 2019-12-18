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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ time_t ;
struct sockaddr_storage {int dummy; } ;
struct rtt_info {int dummy; } ;
struct lruhash_entry {int /*<<< orphan*/  lock; scalar_t__ data; } ;
struct infra_data {scalar_t__ ttl; scalar_t__ probedelay; scalar_t__ timeout_other; scalar_t__ timeout_AAAA; scalar_t__ timeout_A; int /*<<< orphan*/  rtt; } ;
struct infra_cache {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 struct lruhash_entry* infra_lookup_nottl (struct infra_cache*,struct sockaddr_storage*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (struct rtt_info*,int /*<<< orphan*/ *,int) ; 

long long infra_get_host_rto(struct infra_cache* infra,
        struct sockaddr_storage* addr, socklen_t addrlen, uint8_t* nm,
	size_t nmlen, struct rtt_info* rtt, int* delay, time_t timenow,
	int* tA, int* tAAAA, int* tother)
{
	struct lruhash_entry* e = infra_lookup_nottl(infra, addr, addrlen,
		nm, nmlen, 0);
	struct infra_data* data;
	long long ttl = -2;
	if(!e) return -1;
	data = (struct infra_data*)e->data;
	if(data->ttl >= timenow) {
		ttl = (long long)(data->ttl - timenow);
		memmove(rtt, &data->rtt, sizeof(*rtt));
		if(timenow < data->probedelay)
			*delay = (int)(data->probedelay - timenow);
		else	*delay = 0;
	}
	*tA = (int)data->timeout_A;
	*tAAAA = (int)data->timeout_AAAA;
	*tother = (int)data->timeout_other;
	lock_rw_unlock(&e->lock);
	return ttl;
}