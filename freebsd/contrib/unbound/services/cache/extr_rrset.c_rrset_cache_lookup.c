#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  scalar_t__ time_t ;
struct TYPE_3__ {int /*<<< orphan*/  hash; int /*<<< orphan*/ * data; struct ub_packed_rrset_key* key; } ;
struct TYPE_4__ {size_t dname_len; int /*<<< orphan*/  flags; void* rrset_class; void* type; int /*<<< orphan*/ * dname; } ;
struct ub_packed_rrset_key {TYPE_1__ entry; TYPE_2__ rk; } ;
struct rrset_cache {int /*<<< orphan*/  table; } ;
struct packed_rrset_data {scalar_t__ ttl; } ;
struct lruhash_entry {scalar_t__ key; int /*<<< orphan*/  lock; scalar_t__ data; } ;

/* Variables and functions */
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrset_key_hash (TYPE_2__*) ; 
 struct lruhash_entry* slabhash_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ub_packed_rrset_key*,int) ; 

struct ub_packed_rrset_key* 
rrset_cache_lookup(struct rrset_cache* r, uint8_t* qname, size_t qnamelen, 
	uint16_t qtype, uint16_t qclass, uint32_t flags, time_t timenow,
	int wr)
{
	struct lruhash_entry* e;
	struct ub_packed_rrset_key key;
	
	key.entry.key = &key;
	key.entry.data = NULL;
	key.rk.dname = qname;
	key.rk.dname_len = qnamelen;
	key.rk.type = htons(qtype);
	key.rk.rrset_class = htons(qclass);
	key.rk.flags = flags;

	key.entry.hash = rrset_key_hash(&key.rk);

	if((e = slabhash_lookup(&r->table, key.entry.hash, &key, wr))) {
		/* check TTL */
		struct packed_rrset_data* data = 
			(struct packed_rrset_data*)e->data;
		if(timenow > data->ttl) {
			lock_rw_unlock(&e->lock);
			return NULL;
		}
		/* we're done */
		return (struct ub_packed_rrset_key*)e->key;
	}
	return NULL;
}