#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  io_priority; int /*<<< orphan*/  io_type; int /*<<< orphan*/  io_abd; TYPE_2__* io_vsd; } ;
typedef  TYPE_1__ zio_t ;
struct TYPE_12__ {int /*<<< orphan*/  iv_reconstruct; int /*<<< orphan*/  iv_splits; } ;
typedef  TYPE_2__ indirect_vsd_t ;
struct TYPE_13__ {int is_children; int /*<<< orphan*/  is_size; int /*<<< orphan*/  is_target_offset; TYPE_4__* is_child; } ;
typedef  TYPE_3__ indirect_split_t ;
struct TYPE_14__ {int /*<<< orphan*/  ic_data; int /*<<< orphan*/  ic_vdev; int /*<<< orphan*/ * ic_duplicate; } ;
typedef  TYPE_4__ indirect_child_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  abd_alloc_sametype (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* list_head (int /*<<< orphan*/ *) ; 
 TYPE_3__* list_next (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  vdev_indirect_read_split_done ; 
 int /*<<< orphan*/  vdev_readable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zio_nowait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zio_vdev_child_io (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static void
vdev_indirect_read_all(zio_t *zio)
{
	indirect_vsd_t *iv = zio->io_vsd;

	for (indirect_split_t *is = list_head(&iv->iv_splits);
	    is != NULL; is = list_next(&iv->iv_splits, is)) {
		for (int i = 0; i < is->is_children; i++) {
			indirect_child_t *ic = &is->is_child[i];

			if (!vdev_readable(ic->ic_vdev))
				continue;

			/*
			 * Note, we may read from a child whose DTL
			 * indicates that the data may not be present here.
			 * While this might result in a few i/os that will
			 * likely return incorrect data, it simplifies the
			 * code since we can treat scrub and resilver
			 * identically.  (The incorrect data will be
			 * detected and ignored when we verify the
			 * checksum.)
			 */

			ic->ic_data = abd_alloc_sametype(zio->io_abd,
			    is->is_size);
			ic->ic_duplicate = NULL;

			zio_nowait(zio_vdev_child_io(zio, NULL,
			    ic->ic_vdev, is->is_target_offset, ic->ic_data,
			    is->is_size, zio->io_type, zio->io_priority, 0,
			    vdev_indirect_read_split_done, ic));
		}
	}
	iv->iv_reconstruct = B_TRUE;
}