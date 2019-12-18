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
typedef  int u_int ;
struct uma_hash {int uh_hashsize; int uh_hashmask; struct slabhead* uh_slab_hash; } ;
struct slabhead {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_UMAHASH ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  UMA_ANYDOMAIN ; 
 int UMA_HASH_SIZE_INIT ; 
 int /*<<< orphan*/  bzero (struct slabhead*,size_t) ; 
 int /*<<< orphan*/  hashzone ; 
 scalar_t__ malloc (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  powerof2 (int) ; 
 struct slabhead* zone_alloc_item (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hash_alloc(struct uma_hash *hash, u_int size)
{
	size_t alloc;

	KASSERT(powerof2(size), ("hash size must be power of 2"));
	if (size > UMA_HASH_SIZE_INIT)  {
		hash->uh_hashsize = size;
		alloc = sizeof(hash->uh_slab_hash[0]) * hash->uh_hashsize;
		hash->uh_slab_hash = (struct slabhead *)malloc(alloc,
		    M_UMAHASH, M_NOWAIT);
	} else {
		alloc = sizeof(hash->uh_slab_hash[0]) * UMA_HASH_SIZE_INIT;
		hash->uh_slab_hash = zone_alloc_item(hashzone, NULL,
		    UMA_ANYDOMAIN, M_WAITOK);
		hash->uh_hashsize = UMA_HASH_SIZE_INIT;
	}
	if (hash->uh_slab_hash) {
		bzero(hash->uh_slab_hash, alloc);
		hash->uh_hashmask = hash->uh_hashsize - 1;
		return (1);
	}

	return (0);
}