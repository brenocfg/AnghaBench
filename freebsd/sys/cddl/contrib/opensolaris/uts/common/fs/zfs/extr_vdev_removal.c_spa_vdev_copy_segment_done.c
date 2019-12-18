#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  io_spa; TYPE_2__* io_private; } ;
typedef  TYPE_1__ zio_t ;
struct TYPE_7__ {int /*<<< orphan*/  vcsa_obsolete_segs; } ;
typedef  TYPE_2__ vdev_copy_segment_arg_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCL_STATE ; 
 int /*<<< orphan*/  kmem_free (TYPE_2__*,int) ; 
 int /*<<< orphan*/  range_tree_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  range_tree_vacate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  spa_config_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unalloc_seg ; 

__attribute__((used)) static void
spa_vdev_copy_segment_done(zio_t *zio)
{
	vdev_copy_segment_arg_t *vcsa = zio->io_private;

	range_tree_vacate(vcsa->vcsa_obsolete_segs,
	    unalloc_seg, vcsa);
	range_tree_destroy(vcsa->vcsa_obsolete_segs);
	kmem_free(vcsa, sizeof (*vcsa));

	spa_config_exit(zio->io_spa, SCL_STATE, zio->io_spa);
}