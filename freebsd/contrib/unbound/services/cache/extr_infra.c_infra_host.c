#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  scalar_t__ time_t ;
struct sockaddr_storage {int dummy; } ;
struct lruhash_entry {int /*<<< orphan*/  lock; scalar_t__ data; int /*<<< orphan*/  hash; } ;
struct TYPE_3__ {int rto; } ;
struct infra_data {scalar_t__ ttl; int edns_version; scalar_t__ probedelay; TYPE_1__ rtt; void* edns_lame_known; void* timeout_other; void* timeout_AAAA; void* timeout_A; } ;
struct infra_cache {int /*<<< orphan*/  hosts; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int PROBE_MAXRTO ; 
 int USEFUL_SERVER_TOP_TIMEOUT ; 
 int /*<<< orphan*/  data_entry_init (struct infra_cache*,struct lruhash_entry*,scalar_t__) ; 
 struct lruhash_entry* infra_lookup_nottl (struct infra_cache*,struct sockaddr_storage*,int /*<<< orphan*/ ,void**,size_t,int) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 struct lruhash_entry* new_entry (struct infra_cache*,struct sockaddr_storage*,int /*<<< orphan*/ ,void**,size_t,scalar_t__) ; 
 int rtt_notimeout (TYPE_1__*) ; 
 int rtt_timeout (TYPE_1__*) ; 
 int /*<<< orphan*/  slabhash_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct lruhash_entry*,struct infra_data*,int /*<<< orphan*/ *) ; 

int 
infra_host(struct infra_cache* infra, struct sockaddr_storage* addr,
        socklen_t addrlen, uint8_t* nm, size_t nmlen, time_t timenow,
	int* edns_vs, uint8_t* edns_lame_known, int* to)
{
	struct lruhash_entry* e = infra_lookup_nottl(infra, addr, addrlen,
		nm, nmlen, 0);
	struct infra_data* data;
	int wr = 0;
	if(e && ((struct infra_data*)e->data)->ttl < timenow) {
		/* it expired, try to reuse existing entry */
		int old = ((struct infra_data*)e->data)->rtt.rto;
		uint8_t tA = ((struct infra_data*)e->data)->timeout_A;
		uint8_t tAAAA = ((struct infra_data*)e->data)->timeout_AAAA;
		uint8_t tother = ((struct infra_data*)e->data)->timeout_other;
		lock_rw_unlock(&e->lock);
		e = infra_lookup_nottl(infra, addr, addrlen, nm, nmlen, 1);
		if(e) {
			/* if its still there we have a writelock, init */
			/* re-initialise */
			/* do not touch lameness, it may be valid still */
			data_entry_init(infra, e, timenow);
			wr = 1;
			/* TOP_TIMEOUT remains on reuse */
			if(old >= USEFUL_SERVER_TOP_TIMEOUT) {
				((struct infra_data*)e->data)->rtt.rto
					= USEFUL_SERVER_TOP_TIMEOUT;
				((struct infra_data*)e->data)->timeout_A = tA;
				((struct infra_data*)e->data)->timeout_AAAA = tAAAA;
				((struct infra_data*)e->data)->timeout_other = tother;
			}
		}
	}
	if(!e) {
		/* insert new entry */
		if(!(e = new_entry(infra, addr, addrlen, nm, nmlen, timenow)))
			return 0;
		data = (struct infra_data*)e->data;
		*edns_vs = data->edns_version;
		*edns_lame_known = data->edns_lame_known;
		*to = rtt_timeout(&data->rtt);
		slabhash_insert(infra->hosts, e->hash, e, data, NULL);
		return 1;
	}
	/* use existing entry */
	data = (struct infra_data*)e->data;
	*edns_vs = data->edns_version;
	*edns_lame_known = data->edns_lame_known;
	*to = rtt_timeout(&data->rtt);
	if(*to >= PROBE_MAXRTO && rtt_notimeout(&data->rtt)*4 <= *to) {
		/* delay other queries, this is the probe query */
		if(!wr) {
			lock_rw_unlock(&e->lock);
			e = infra_lookup_nottl(infra, addr,addrlen,nm,nmlen, 1);
			if(!e) { /* flushed from cache real fast, no use to
				allocate just for the probedelay */
				return 1;
			}
			data = (struct infra_data*)e->data;
		}
		/* add 999 to round up the timeout value from msec to sec,
		 * then add a whole second so it is certain that this probe
		 * has timed out before the next is allowed */
		data->probedelay = timenow + ((*to)+1999)/1000;
	}
	lock_rw_unlock(&e->lock);
	return 1;
}