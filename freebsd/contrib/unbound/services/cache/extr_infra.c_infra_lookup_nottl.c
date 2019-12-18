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
struct lruhash_entry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  hash; int /*<<< orphan*/ * data; void* key; } ;
struct infra_key {size_t namelen; TYPE_1__ entry; int /*<<< orphan*/ * zonename; int /*<<< orphan*/  addr; int /*<<< orphan*/  addrlen; } ;
struct infra_cache {int /*<<< orphan*/  hosts; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  hash_infra (struct sockaddr_storage*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr_storage*,int /*<<< orphan*/ ) ; 
 struct lruhash_entry* slabhash_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct infra_key*,int) ; 

struct lruhash_entry* 
infra_lookup_nottl(struct infra_cache* infra, struct sockaddr_storage* addr,
	socklen_t addrlen, uint8_t* name, size_t namelen, int wr)
{
	struct infra_key k;
	k.addrlen = addrlen;
	memcpy(&k.addr, addr, addrlen);
	k.namelen = namelen;
	k.zonename = name;
	k.entry.hash = hash_infra(addr, addrlen, name);
	k.entry.key = (void*)&k;
	k.entry.data = NULL;
	return slabhash_lookup(infra->hosts, k.entry.hash, &k, wr);
}