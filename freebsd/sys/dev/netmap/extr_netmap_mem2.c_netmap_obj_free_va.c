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
typedef  size_t u_int ;
struct netmap_obj_pool {size_t numclusters; size_t _clustentries; int _clustsize; int _objsize; int /*<<< orphan*/  name; TYPE_1__* lut; } ;
typedef  int ssize_t ;
struct TYPE_2__ {void* vaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  netmap_obj_free (struct netmap_obj_pool*,size_t) ; 
 int /*<<< orphan*/  nm_prerr (char*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
netmap_obj_free_va(struct netmap_obj_pool *p, void *vaddr)
{
	u_int i, j, n = p->numclusters;

	for (i = 0, j = 0; i < n; i++, j += p->_clustentries) {
		void *base = p->lut[i * p->_clustentries].vaddr;
		ssize_t relofs = (ssize_t) vaddr - (ssize_t) base;

		/* Given address, is out of the scope of the current cluster.*/
		if (base == NULL || vaddr < base || relofs >= p->_clustsize)
			continue;

		j = j + relofs / p->_objsize;
		/* KASSERT(j != 0, ("Cannot free object 0")); */
		netmap_obj_free(p, j);
		return;
	}
	nm_prerr("address %p is not contained inside any cluster (%s)",
	    vaddr, p->name);
}