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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ u_long ;
struct nchashhead {int dummy; } ;
struct namecache {int /*<<< orphan*/  nc_dvp; int /*<<< orphan*/  nc_nlen; int /*<<< orphan*/  nc_name; } ;

/* Variables and functions */
 struct namecache* LIST_FIRST (struct nchashhead*) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ ,struct namecache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct namecache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_VFSCACHE ; 
 int /*<<< orphan*/  NCHHASH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_get_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_lock_all_buckets () ; 
 int /*<<< orphan*/  cache_lock_all_vnodes () ; 
 int cache_roundup_2 (int) ; 
 int /*<<< orphan*/  cache_unlock_all_buckets () ; 
 int /*<<< orphan*/  cache_unlock_all_vnodes () ; 
 int /*<<< orphan*/  free (struct nchashhead*,int /*<<< orphan*/ ) ; 
 struct nchashhead* hashinit (int,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  nc_hash ; 
 scalar_t__ nchash ; 
 struct nchashhead* nchashtbl ; 
 int ncsize ; 
 int ncsizefactor ; 
 int numbucketlocks ; 

void
cache_changesize(int newmaxvnodes)
{
	struct nchashhead *new_nchashtbl, *old_nchashtbl;
	u_long new_nchash, old_nchash;
	struct namecache *ncp;
	uint32_t hash;
	int newncsize;
	int i;

	newncsize = newmaxvnodes * ncsizefactor;
	newmaxvnodes = cache_roundup_2(newmaxvnodes * 2);
	if (newmaxvnodes < numbucketlocks)
		newmaxvnodes = numbucketlocks;

	new_nchashtbl = hashinit(newmaxvnodes, M_VFSCACHE, &new_nchash);
	/* If same hash table size, nothing to do */
	if (nchash == new_nchash) {
		free(new_nchashtbl, M_VFSCACHE);
		return;
	}
	/*
	 * Move everything from the old hash table to the new table.
	 * None of the namecache entries in the table can be removed
	 * because to do so, they have to be removed from the hash table.
	 */
	cache_lock_all_vnodes();
	cache_lock_all_buckets();
	old_nchashtbl = nchashtbl;
	old_nchash = nchash;
	nchashtbl = new_nchashtbl;
	nchash = new_nchash;
	for (i = 0; i <= old_nchash; i++) {
		while ((ncp = LIST_FIRST(&old_nchashtbl[i])) != NULL) {
			hash = cache_get_hash(ncp->nc_name, ncp->nc_nlen,
			    ncp->nc_dvp);
			LIST_REMOVE(ncp, nc_hash);
			LIST_INSERT_HEAD(NCHHASH(hash), ncp, nc_hash);
		}
	}
	ncsize = newncsize;
	cache_unlock_all_buckets();
	cache_unlock_all_vnodes();
	free(old_nchashtbl, M_VFSCACHE);
}