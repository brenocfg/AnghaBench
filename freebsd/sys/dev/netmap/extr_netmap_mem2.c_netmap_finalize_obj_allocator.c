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
struct netmap_obj_pool {int numclusters; int _numclusters; int objtotal; int _objtotal; int alloc_done; size_t _clustsize; int _clustentries; size_t memtotal; int /*<<< orphan*/  name; TYPE_1__* lut; int /*<<< orphan*/  _objsize; } ;
struct TYPE_2__ {char* vaddr; int /*<<< orphan*/  paddr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  M_NETMAP ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  contigfree (char*,size_t,int /*<<< orphan*/ ) ; 
 char* contigmalloc (size_t,int /*<<< orphan*/ ,int,size_t,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netmap_reset_obj_allocator (struct netmap_obj_pool*) ; 
 scalar_t__ netmap_verbose ; 
 TYPE_1__* nm_alloc_lut (int) ; 
 int /*<<< orphan*/  nm_prerr (char*,int,...) ; 
 int /*<<< orphan*/  nm_prinf (char*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtophys (char*) ; 

__attribute__((used)) static int
netmap_finalize_obj_allocator(struct netmap_obj_pool *p)
{
	int i; /* must be signed */
	size_t n;

	if (p->lut) {
		/* if the lut is already there we assume that also all the
		 * clusters have already been allocated, possibily by somebody
		 * else (e.g., extmem). In the latter case, the alloc_done flag
		 * will remain at zero, so that we will not attempt to
		 * deallocate the clusters by ourselves in
		 * netmap_reset_obj_allocator.
		 */
		return 0;
	}

	/* optimistically assume we have enough memory */
	p->numclusters = p->_numclusters;
	p->objtotal = p->_objtotal;
	p->alloc_done = 1;

	p->lut = nm_alloc_lut(p->objtotal);
	if (p->lut == NULL) {
		nm_prerr("Unable to create lookup table for '%s'", p->name);
		goto clean;
	}

	/*
	 * Allocate clusters, init pointers
	 */

	n = p->_clustsize;
	for (i = 0; i < (int)p->objtotal;) {
		int lim = i + p->_clustentries;
		char *clust;

		/*
		 * XXX Note, we only need contigmalloc() for buffers attached
		 * to native interfaces. In all other cases (nifp, netmap rings
		 * and even buffers for VALE ports or emulated interfaces) we
		 * can live with standard malloc, because the hardware will not
		 * access the pages directly.
		 */
		clust = contigmalloc(n, M_NETMAP, M_NOWAIT | M_ZERO,
		    (size_t)0, -1UL, PAGE_SIZE, 0);
		if (clust == NULL) {
			/*
			 * If we get here, there is a severe memory shortage,
			 * so halve the allocated memory to reclaim some.
			 */
			nm_prerr("Unable to create cluster at %d for '%s' allocator",
			    i, p->name);
			if (i < 2) /* nothing to halve */
				goto out;
			lim = i / 2;
			for (i--; i >= lim; i--) {
				if (i % p->_clustentries == 0 && p->lut[i].vaddr)
					contigfree(p->lut[i].vaddr,
						n, M_NETMAP);
				p->lut[i].vaddr = NULL;
			}
		out:
			p->objtotal = i;
			/* we may have stopped in the middle of a cluster */
			p->numclusters = (i + p->_clustentries - 1) / p->_clustentries;
			break;
		}
		/*
		 * Set lut state for all buffers in the current cluster.
		 *
		 * [i, lim) is the set of buffer indexes that cover the
		 * current cluster.
		 *
		 * 'clust' is really the address of the current buffer in
		 * the current cluster as we index through it with a stride
		 * of p->_objsize.
		 */
		for (; i < lim; i++, clust += p->_objsize) {
			p->lut[i].vaddr = clust;
#if !defined(linux) && !defined(_WIN32)
			p->lut[i].paddr = vtophys(clust);
#endif
		}
	}
	p->memtotal = (size_t)p->numclusters * (size_t)p->_clustsize;
	if (netmap_verbose)
		nm_prinf("Pre-allocated %d clusters (%d/%zuKB) for '%s'",
		    p->numclusters, p->_clustsize >> 10,
		    p->memtotal >> 10, p->name);

	return 0;

clean:
	netmap_reset_obj_allocator(p);
	return ENOMEM;
}