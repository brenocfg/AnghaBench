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
struct lruhash_entry {void* data; void* key; int /*<<< orphan*/  hash; int /*<<< orphan*/  lock; } ;
struct infra_key {size_t namelen; struct lruhash_entry entry; int /*<<< orphan*/  addr; int /*<<< orphan*/  addrlen; int /*<<< orphan*/  zonename; } ;
struct infra_data {size_t namelen; struct lruhash_entry entry; int /*<<< orphan*/  addr; int /*<<< orphan*/  addrlen; int /*<<< orphan*/  zonename; } ;
struct infra_cache {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  data_entry_init (struct infra_cache*,struct lruhash_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct infra_key*) ; 
 int /*<<< orphan*/  hash_infra (struct sockaddr_storage*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_init (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr_storage*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memdup (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static struct lruhash_entry*
new_entry(struct infra_cache* infra, struct sockaddr_storage* addr, 
	socklen_t addrlen, uint8_t* name, size_t namelen, time_t tm)
{
	struct infra_data* data;
	struct infra_key* key = (struct infra_key*)malloc(sizeof(*key));
	if(!key)
		return NULL;
	data = (struct infra_data*)malloc(sizeof(struct infra_data));
	if(!data) {
		free(key);
		return NULL;
	}
	key->zonename = memdup(name, namelen);
	if(!key->zonename) {
		free(key);
		free(data);
		return NULL;
	}
	key->namelen = namelen;
	lock_rw_init(&key->entry.lock);
	key->entry.hash = hash_infra(addr, addrlen, name);
	key->entry.key = (void*)key;
	key->entry.data = (void*)data;
	key->addrlen = addrlen;
	memcpy(&key->addr, addr, addrlen);
	data_entry_init(infra, &key->entry, tm);
	return &key->entry;
}