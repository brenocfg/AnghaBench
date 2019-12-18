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
struct xen_blkif_ring {int dummy; } ;
struct page {int dummy; } ;
struct grant_page {scalar_t__ handle; struct page* page; int /*<<< orphan*/ * persistent_gnt; } ;
struct gnttab_unmap_grant_ref {int dummy; } ;

/* Variables and functions */
 scalar_t__ BLKBACK_INVALID_HANDLE ; 
 int /*<<< orphan*/  GNTMAP_host_map ; 
 int /*<<< orphan*/  gnttab_set_unmap_op (struct gnttab_unmap_grant_ref*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  put_persistent_gnt (struct xen_blkif_ring*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vaddr (struct page*) ; 

__attribute__((used)) static unsigned int xen_blkbk_unmap_prepare(
	struct xen_blkif_ring *ring,
	struct grant_page **pages,
	unsigned int num,
	struct gnttab_unmap_grant_ref *unmap_ops,
	struct page **unmap_pages)
{
	unsigned int i, invcount = 0;

	for (i = 0; i < num; i++) {
		if (pages[i]->persistent_gnt != NULL) {
			put_persistent_gnt(ring, pages[i]->persistent_gnt);
			continue;
		}
		if (pages[i]->handle == BLKBACK_INVALID_HANDLE)
			continue;
		unmap_pages[invcount] = pages[i]->page;
		gnttab_set_unmap_op(&unmap_ops[invcount], vaddr(pages[i]->page),
				    GNTMAP_host_map, pages[i]->handle);
		pages[i]->handle = BLKBACK_INVALID_HANDLE;
		invcount++;
	}

	return invcount;
}