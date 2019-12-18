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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  time_t ;
struct sockaddr_storage {int dummy; } ;
struct lruhash_entry {int /*<<< orphan*/  lock; scalar_t__ data; int /*<<< orphan*/  hash; } ;
struct infra_data {int isdnsseclame; int rec_lame; int lame_type_A; int lame_other; int /*<<< orphan*/  ttl; } ;
struct infra_cache {int /*<<< orphan*/  hosts; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_A ; 
 int /*<<< orphan*/  data_entry_init (struct infra_cache*,struct lruhash_entry*,int /*<<< orphan*/ ) ; 
 struct lruhash_entry* infra_lookup_nottl (struct infra_cache*,struct sockaddr_storage*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 struct lruhash_entry* new_entry (struct infra_cache*,struct sockaddr_storage*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slabhash_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct lruhash_entry*,scalar_t__,int /*<<< orphan*/ *) ; 

int 
infra_set_lame(struct infra_cache* infra, struct sockaddr_storage* addr,
	socklen_t addrlen, uint8_t* nm, size_t nmlen, time_t timenow,
	int dnsseclame, int reclame, uint16_t qtype)
{
	struct infra_data* data;
	struct lruhash_entry* e;
	int needtoinsert = 0;
	e = infra_lookup_nottl(infra, addr, addrlen, nm, nmlen, 1);
	if(!e) {
		/* insert it */
		if(!(e = new_entry(infra, addr, addrlen, nm, nmlen, timenow))) {
			log_err("set_lame: malloc failure");
			return 0;
		}
		needtoinsert = 1;
	} else if( ((struct infra_data*)e->data)->ttl < timenow) {
		/* expired, reuse existing entry */
		data_entry_init(infra, e, timenow);
	}
	/* got an entry, now set the zone lame */
	data = (struct infra_data*)e->data;
	/* merge data (if any) */
	if(dnsseclame)
		data->isdnsseclame = 1;
	if(reclame)
		data->rec_lame = 1;
	if(!dnsseclame && !reclame && qtype == LDNS_RR_TYPE_A)
		data->lame_type_A = 1;
	if(!dnsseclame  && !reclame && qtype != LDNS_RR_TYPE_A)
		data->lame_other = 1;
	/* done */
	if(needtoinsert)
		slabhash_insert(infra->hosts, e->hash, e, e->data, NULL);
	else 	{ lock_rw_unlock(&e->lock); }
	return 1;
}