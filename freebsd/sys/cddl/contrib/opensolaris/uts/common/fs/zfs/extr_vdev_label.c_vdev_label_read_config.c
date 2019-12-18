#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zio_t ;
struct TYPE_8__ {int /*<<< orphan*/ * vdev_spa; } ;
typedef  TYPE_1__ vdev_t ;
struct TYPE_9__ {int /*<<< orphan*/  vp_nvlist; } ;
typedef  TYPE_2__ vdev_phys_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  abd_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  RW_WRITER ; 
 scalar_t__ SCL_STATE_ALL ; 
 int VDEV_LABELS ; 
 int ZIO_FLAG_CANFAIL ; 
 int ZIO_FLAG_CONFIG_WRITER ; 
 int ZIO_FLAG_SPECULATIVE ; 
 int ZIO_FLAG_TRYHARD ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_POOL_TXG ; 
 int /*<<< orphan*/ * abd_alloc_linear (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abd_free (int /*<<< orphan*/ *) ; 
 TYPE_2__* abd_to_buf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fnvlist_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ nvlist_unpack (int /*<<< orphan*/ ,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_config_held (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_dbgmsg (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_label_read (int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vdev_label_t ; 
 int /*<<< orphan*/  vdev_readable (TYPE_1__*) ; 
 int /*<<< orphan*/  vl_vdev_phys ; 
 int /*<<< orphan*/ * zio_root (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ zio_wait (int /*<<< orphan*/ *) ; 

nvlist_t *
vdev_label_read_config(vdev_t *vd, uint64_t txg)
{
	spa_t *spa = vd->vdev_spa;
	nvlist_t *config = NULL;
	vdev_phys_t *vp;
	abd_t *vp_abd;
	zio_t *zio;
	uint64_t best_txg = 0;
	uint64_t label_txg = 0;
	int error = 0;
	int flags = ZIO_FLAG_CONFIG_WRITER | ZIO_FLAG_CANFAIL |
	    ZIO_FLAG_SPECULATIVE;

	ASSERT(spa_config_held(spa, SCL_STATE_ALL, RW_WRITER) == SCL_STATE_ALL);

	if (!vdev_readable(vd))
		return (NULL);

	vp_abd = abd_alloc_linear(sizeof (vdev_phys_t), B_TRUE);
	vp = abd_to_buf(vp_abd);

retry:
	for (int l = 0; l < VDEV_LABELS; l++) {
		nvlist_t *label = NULL;

		zio = zio_root(spa, NULL, NULL, flags);

		vdev_label_read(zio, vd, l, vp_abd,
		    offsetof(vdev_label_t, vl_vdev_phys),
		    sizeof (vdev_phys_t), NULL, NULL, flags);

		if (zio_wait(zio) == 0 &&
		    nvlist_unpack(vp->vp_nvlist, sizeof (vp->vp_nvlist),
		    &label, 0) == 0) {
			/*
			 * Auxiliary vdevs won't have txg values in their
			 * labels and newly added vdevs may not have been
			 * completely initialized so just return the
			 * configuration from the first valid label we
			 * encounter.
			 */
			error = nvlist_lookup_uint64(label,
			    ZPOOL_CONFIG_POOL_TXG, &label_txg);
			if ((error || label_txg == 0) && !config) {
				config = label;
				break;
			} else if (label_txg <= txg && label_txg > best_txg) {
				best_txg = label_txg;
				nvlist_free(config);
				config = fnvlist_dup(label);
			}
		}

		if (label != NULL) {
			nvlist_free(label);
			label = NULL;
		}
	}

	if (config == NULL && !(flags & ZIO_FLAG_TRYHARD)) {
		flags |= ZIO_FLAG_TRYHARD;
		goto retry;
	}

	/*
	 * We found a valid label but it didn't pass txg restrictions.
	 */
	if (config == NULL && label_txg != 0) {
		vdev_dbgmsg(vd, "label discarded as txg is too large "
		    "(%llu > %llu)", (u_longlong_t)label_txg,
		    (u_longlong_t)txg);
	}

	abd_free(vp_abd);

	return (config);
}