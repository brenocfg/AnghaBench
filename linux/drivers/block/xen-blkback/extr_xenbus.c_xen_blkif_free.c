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
struct xen_blkif {TYPE_1__* be; int /*<<< orphan*/  vbd; } ;
struct TYPE_2__ {struct TYPE_2__* mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct xen_blkif*) ; 
 int /*<<< orphan*/  xen_blkif_cachep ; 
 int /*<<< orphan*/  xen_blkif_disconnect (struct xen_blkif*) ; 
 int /*<<< orphan*/  xen_vbd_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xen_blkif_free(struct xen_blkif *blkif)
{
	WARN_ON(xen_blkif_disconnect(blkif));
	xen_vbd_free(&blkif->vbd);
	kfree(blkif->be->mode);
	kfree(blkif->be);

	/* Make sure everything is drained before shutting down */
	kmem_cache_free(xen_blkif_cachep, blkif);
}