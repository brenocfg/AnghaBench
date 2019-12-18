#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zio_t ;
struct TYPE_10__ {int vdev_children; int /*<<< orphan*/  vdev_spa; TYPE_1__* vdev_ops; struct TYPE_10__** vdev_child; } ;
typedef  TYPE_2__ vdev_t ;
struct TYPE_11__ {char* vp_nvlist; } ;
typedef  TYPE_3__ vdev_phys_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  abd_t ;
struct TYPE_9__ {int /*<<< orphan*/  vdev_op_leaf; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  NV_ENCODE_XDR ; 
 int VDEV_LABELS ; 
 int ZIO_FLAG_DONT_PROPAGATE ; 
 int /*<<< orphan*/ * abd_alloc_linear (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abd_free (int /*<<< orphan*/ *) ; 
 TYPE_3__* abd_to_buf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  abd_zero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_pack (int /*<<< orphan*/ *,char**,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * spa_config_generate (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_label_sync_done ; 
 int /*<<< orphan*/  vdev_label_t ; 
 int /*<<< orphan*/  vdev_label_write (int /*<<< orphan*/ *,TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vdev_writeable (TYPE_2__*) ; 
 int /*<<< orphan*/  vl_vdev_phys ; 

__attribute__((used)) static void
vdev_label_sync(zio_t *zio, uint64_t *good_writes,
    vdev_t *vd, int l, uint64_t txg, int flags)
{
	nvlist_t *label;
	vdev_phys_t *vp;
	abd_t *vp_abd;
	char *buf;
	size_t buflen;

	for (int c = 0; c < vd->vdev_children; c++) {
		vdev_label_sync(zio, good_writes,
		    vd->vdev_child[c], l, txg, flags);
	}

	if (!vd->vdev_ops->vdev_op_leaf)
		return;

	if (!vdev_writeable(vd))
		return;

	/*
	 * Generate a label describing the top-level config to which we belong.
	 */
	label = spa_config_generate(vd->vdev_spa, vd, txg, B_FALSE);

	vp_abd = abd_alloc_linear(sizeof (vdev_phys_t), B_TRUE);
	abd_zero(vp_abd, sizeof (vdev_phys_t));
	vp = abd_to_buf(vp_abd);

	buf = vp->vp_nvlist;
	buflen = sizeof (vp->vp_nvlist);

	if (nvlist_pack(label, &buf, &buflen, NV_ENCODE_XDR, KM_SLEEP) == 0) {
		for (; l < VDEV_LABELS; l += 2) {
			vdev_label_write(zio, vd, l, vp_abd,
			    offsetof(vdev_label_t, vl_vdev_phys),
			    sizeof (vdev_phys_t),
			    vdev_label_sync_done, good_writes,
			    flags | ZIO_FLAG_DONT_PROPAGATE);
		}
	}

	abd_free(vp_abd);
	nvlist_free(label);
}