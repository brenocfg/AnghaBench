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
typedef  int /*<<< orphan*/  time_t ;
struct sockaddr_storage {int dummy; } ;
struct lruhash_entry {int /*<<< orphan*/  lock; scalar_t__ data; int /*<<< orphan*/  hash; } ;
struct infra_data {int edns_version; int edns_lame_known; int /*<<< orphan*/  ttl; } ;
struct infra_cache {int /*<<< orphan*/  hosts; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  data_entry_init (struct infra_cache*,struct lruhash_entry*,int /*<<< orphan*/ ) ; 
 struct lruhash_entry* infra_lookup_nottl (struct infra_cache*,struct sockaddr_storage*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 struct lruhash_entry* new_entry (struct infra_cache*,struct sockaddr_storage*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slabhash_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct lruhash_entry*,scalar_t__,int /*<<< orphan*/ *) ; 

int 
infra_edns_update(struct infra_cache* infra, struct sockaddr_storage* addr,
	socklen_t addrlen, uint8_t* nm, size_t nmlen, int edns_version,
	time_t timenow)
{
	struct lruhash_entry* e = infra_lookup_nottl(infra, addr, addrlen,
		nm, nmlen, 1);
	struct infra_data* data;
	int needtoinsert = 0;
	if(!e) {
		if(!(e = new_entry(infra, addr, addrlen, nm, nmlen, timenow)))
			return 0;
		needtoinsert = 1;
	} else if(((struct infra_data*)e->data)->ttl < timenow) {
		data_entry_init(infra, e, timenow);
	}
	/* have an entry, update the rtt, and the ttl */
	data = (struct infra_data*)e->data;
	/* do not update if noEDNS and stored is yesEDNS */
	if(!(edns_version == -1 && (data->edns_version != -1 &&
		data->edns_lame_known))) {
		data->edns_version = edns_version;
		data->edns_lame_known = 1;
	}

	if(needtoinsert)
		slabhash_insert(infra->hosts, e->hash, e, e->data, NULL);
	else 	{ lock_rw_unlock(&e->lock); }
	return 1;
}