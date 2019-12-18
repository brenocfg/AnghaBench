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
struct netmap_obj_pool {size_t objtotal; scalar_t__ alloc_done; scalar_t__ objfree; scalar_t__ numclusters; scalar_t__ memtotal; TYPE_1__* lut; int /*<<< orphan*/  _clustsize; scalar_t__ _clustentries; int /*<<< orphan*/ * invalid_bitmap; int /*<<< orphan*/ * bitmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  vaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NETMAP ; 
 int /*<<< orphan*/  contigfree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nm_free_lut (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  nm_os_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
netmap_reset_obj_allocator(struct netmap_obj_pool *p)
{

	if (p == NULL)
		return;
	if (p->bitmap)
		nm_os_free(p->bitmap);
	p->bitmap = NULL;
	if (p->invalid_bitmap)
		nm_os_free(p->invalid_bitmap);
	p->invalid_bitmap = NULL;
	if (!p->alloc_done) {
		/* allocation was done by somebody else.
		 * Let them clean up after themselves.
		 */
		return;
	}
	if (p->lut) {
		u_int i;

		/*
		 * Free each cluster allocated in
		 * netmap_finalize_obj_allocator().  The cluster start
		 * addresses are stored at multiples of p->_clusterentries
		 * in the lut.
		 */
		for (i = 0; i < p->objtotal; i += p->_clustentries) {
			contigfree(p->lut[i].vaddr, p->_clustsize, M_NETMAP);
		}
		nm_free_lut(p->lut, p->objtotal);
	}
	p->lut = NULL;
	p->objtotal = 0;
	p->memtotal = 0;
	p->numclusters = 0;
	p->objfree = 0;
	p->alloc_done = 0;
}