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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
typedef  scalar_t__ time_t ;
struct sockaddr_storage {int dummy; } ;
struct lruhash_entry {int /*<<< orphan*/  lock; scalar_t__ data; } ;
struct TYPE_3__ {int rto; } ;
struct infra_data {scalar_t__ probedelay; scalar_t__ timeout_A; scalar_t__ timeout_AAAA; scalar_t__ timeout_other; scalar_t__ ttl; scalar_t__ rec_lame; scalar_t__ isdnsseclame; scalar_t__ lame_other; scalar_t__ lame_type_A; TYPE_1__ rtt; } ;
struct infra_cache {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_A ; 
 scalar_t__ LDNS_RR_TYPE_AAAA ; 
 int PROBE_MAXRTO ; 
 scalar_t__ TIMEOUT_COUNT_MAX ; 
 int USEFUL_SERVER_TOP_TIMEOUT ; 
 struct lruhash_entry* infra_lookup_nottl (struct infra_cache*,struct sockaddr_storage*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int rtt_notimeout (TYPE_1__*) ; 
 int rtt_unclamped (TYPE_1__*) ; 

int
infra_get_lame_rtt(struct infra_cache* infra,
        struct sockaddr_storage* addr, socklen_t addrlen,
        uint8_t* name, size_t namelen, uint16_t qtype, 
	int* lame, int* dnsseclame, int* reclame, int* rtt, time_t timenow)
{
	struct infra_data* host;
	struct lruhash_entry* e = infra_lookup_nottl(infra, addr, addrlen,
		name, namelen, 0);
	if(!e) 
		return 0;
	host = (struct infra_data*)e->data;
	*rtt = rtt_unclamped(&host->rtt);
	if(host->rtt.rto >= PROBE_MAXRTO && timenow < host->probedelay
		&& rtt_notimeout(&host->rtt)*4 <= host->rtt.rto) {
		/* single probe for this domain, and we are not probing */
		/* unless the query type allows a probe to happen */
		if(qtype == LDNS_RR_TYPE_A) {
			if(host->timeout_A >= TIMEOUT_COUNT_MAX)
				*rtt = USEFUL_SERVER_TOP_TIMEOUT;
			else	*rtt = USEFUL_SERVER_TOP_TIMEOUT-1000;
		} else if(qtype == LDNS_RR_TYPE_AAAA) {
			if(host->timeout_AAAA >= TIMEOUT_COUNT_MAX)
				*rtt = USEFUL_SERVER_TOP_TIMEOUT;
			else	*rtt = USEFUL_SERVER_TOP_TIMEOUT-1000;
		} else {
			if(host->timeout_other >= TIMEOUT_COUNT_MAX)
				*rtt = USEFUL_SERVER_TOP_TIMEOUT;
			else	*rtt = USEFUL_SERVER_TOP_TIMEOUT-1000;
		}
	}
	if(timenow > host->ttl) {
		/* expired entry */
		/* see if this can be a re-probe of an unresponsive server */
		/* minus 1000 because that is outside of the RTTBAND, so
		 * blacklisted servers stay blacklisted if this is chosen */
		if(host->rtt.rto >= USEFUL_SERVER_TOP_TIMEOUT) {
			lock_rw_unlock(&e->lock);
			*rtt = USEFUL_SERVER_TOP_TIMEOUT-1000;
			*lame = 0;
			*dnsseclame = 0;
			*reclame = 0;
			return 1;
		}
		lock_rw_unlock(&e->lock);
		return 0;
	}
	/* check lameness first */
	if(host->lame_type_A && qtype == LDNS_RR_TYPE_A) {
		lock_rw_unlock(&e->lock);
		*lame = 1;
		*dnsseclame = 0;
		*reclame = 0;
		return 1;
	} else if(host->lame_other && qtype != LDNS_RR_TYPE_A) {
		lock_rw_unlock(&e->lock);
		*lame = 1;
		*dnsseclame = 0;
		*reclame = 0;
		return 1;
	} else if(host->isdnsseclame) {
		lock_rw_unlock(&e->lock);
		*lame = 0;
		*dnsseclame = 1;
		*reclame = 0;
		return 1;
	} else if(host->rec_lame) {
		lock_rw_unlock(&e->lock);
		*lame = 0;
		*dnsseclame = 0;
		*reclame = 1;
		return 1;
	}
	/* no lameness for this type of query */
	lock_rw_unlock(&e->lock);
	*lame = 0;
	*dnsseclame = 0;
	*reclame = 0;
	return 1;
}