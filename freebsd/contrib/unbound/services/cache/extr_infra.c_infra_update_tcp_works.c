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
typedef  int /*<<< orphan*/  uint8_t ;
struct sockaddr_storage {int dummy; } ;
struct lruhash_entry {int /*<<< orphan*/  lock; scalar_t__ data; } ;
struct TYPE_2__ {scalar_t__ rto; } ;
struct infra_data {TYPE_1__ rtt; } ;
struct infra_cache {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 scalar_t__ RTT_MAX_TIMEOUT ; 
 struct lruhash_entry* infra_lookup_nottl (struct infra_cache*,struct sockaddr_storage*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 

void 
infra_update_tcp_works(struct infra_cache* infra,
        struct sockaddr_storage* addr, socklen_t addrlen, uint8_t* nm,
	size_t nmlen)
{
	struct lruhash_entry* e = infra_lookup_nottl(infra, addr, addrlen,
		nm, nmlen, 1);
	struct infra_data* data;
	if(!e)
		return; /* doesn't exist */
	data = (struct infra_data*)e->data;
	if(data->rtt.rto >= RTT_MAX_TIMEOUT)
		/* do not disqualify this server altogether, it is better
		 * than nothing */
		data->rtt.rto = RTT_MAX_TIMEOUT-1000;
	lock_rw_unlock(&e->lock);
}