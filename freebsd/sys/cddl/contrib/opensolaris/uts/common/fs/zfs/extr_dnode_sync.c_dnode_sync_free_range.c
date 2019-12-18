#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {int /*<<< orphan*/  dn_mtx; } ;
typedef  TYPE_1__ dnode_t ;
struct TYPE_5__ {int /*<<< orphan*/  dsfra_tx; int /*<<< orphan*/  dsfra_free_indirects; TYPE_1__* dsfra_dnode; } ;
typedef  TYPE_2__ dnode_sync_free_range_arg_t ;

/* Variables and functions */
 int /*<<< orphan*/  dnode_sync_free_range_impl (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dnode_sync_free_range(void *arg, uint64_t blkid, uint64_t nblks)
{
	dnode_sync_free_range_arg_t *dsfra = arg;
	dnode_t *dn = dsfra->dsfra_dnode;

	mutex_exit(&dn->dn_mtx);
	dnode_sync_free_range_impl(dn, blkid, nblks,
	    dsfra->dsfra_free_indirects, dsfra->dsfra_tx);
	mutex_enter(&dn->dn_mtx);
}