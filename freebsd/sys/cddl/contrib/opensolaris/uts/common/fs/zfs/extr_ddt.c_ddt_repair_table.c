#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zio_t ;
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_17__ {int /*<<< orphan*/  ddt_checksum; int /*<<< orphan*/  ddt_repair_tree; int /*<<< orphan*/ * ddt_spa; } ;
typedef  TYPE_1__ ddt_t ;
struct TYPE_18__ {int /*<<< orphan*/  dde_key; } ;
typedef  TYPE_2__ ddt_entry_t ;
typedef  int /*<<< orphan*/  blkptr_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;

/* Variables and functions */
 TYPE_2__* AVL_NEXT (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_2__* avl_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avl_remove (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ddt_bp_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ddt_enter (TYPE_1__*) ; 
 int /*<<< orphan*/  ddt_exit (TYPE_1__*) ; 
 int /*<<< orphan*/  ddt_repair_done (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ddt_repair_entry (TYPE_1__*,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* ddt_repair_start (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int spa_sync_pass (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ddt_repair_table(ddt_t *ddt, zio_t *rio)
{
	spa_t *spa = ddt->ddt_spa;
	ddt_entry_t *dde, *rdde_next, *rdde;
	avl_tree_t *t = &ddt->ddt_repair_tree;
	blkptr_t blk;

	if (spa_sync_pass(spa) > 1)
		return;

	ddt_enter(ddt);
	for (rdde = avl_first(t); rdde != NULL; rdde = rdde_next) {
		rdde_next = AVL_NEXT(t, rdde);
		avl_remove(&ddt->ddt_repair_tree, rdde);
		ddt_exit(ddt);
		ddt_bp_create(ddt->ddt_checksum, &rdde->dde_key, NULL, &blk);
		dde = ddt_repair_start(ddt, &blk);
		ddt_repair_entry(ddt, dde, rdde, rio);
		ddt_repair_done(ddt, dde);
		ddt_enter(ddt);
	}
	ddt_exit(ddt);
}