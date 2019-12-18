#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  spc_refcnt; } ;
typedef  TYPE_1__ scan_prefetch_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  zfs_refcount_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_refcount_remove (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static void
scan_prefetch_ctx_rele(scan_prefetch_ctx_t *spc, void *tag)
{
	if (zfs_refcount_remove(&spc->spc_refcnt, tag) == 0) {
		zfs_refcount_destroy(&spc->spc_refcnt);
		kmem_free(spc, sizeof (scan_prefetch_ctx_t));
	}
}