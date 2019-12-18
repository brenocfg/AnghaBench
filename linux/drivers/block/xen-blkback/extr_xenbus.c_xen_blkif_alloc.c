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
struct xen_blkif {int /*<<< orphan*/  free_work; int /*<<< orphan*/  drain_complete; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  domid; } ;
typedef  int /*<<< orphan*/  domid_t ;

/* Variables and functions */
 scalar_t__ BLKIF_MAX_INDIRECT_PAGES_PER_REQUEST ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct xen_blkif* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ MAX_INDIRECT_PAGES ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct xen_blkif* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_blkif_cachep ; 
 int /*<<< orphan*/  xen_blkif_deferred_free ; 

__attribute__((used)) static struct xen_blkif *xen_blkif_alloc(domid_t domid)
{
	struct xen_blkif *blkif;

	BUILD_BUG_ON(MAX_INDIRECT_PAGES > BLKIF_MAX_INDIRECT_PAGES_PER_REQUEST);

	blkif = kmem_cache_zalloc(xen_blkif_cachep, GFP_KERNEL);
	if (!blkif)
		return ERR_PTR(-ENOMEM);

	blkif->domid = domid;
	atomic_set(&blkif->refcnt, 1);
	init_completion(&blkif->drain_complete);
	INIT_WORK(&blkif->free_work, xen_blkif_deferred_free);

	return blkif;
}