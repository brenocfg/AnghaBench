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
typedef  int /*<<< orphan*/  zio_t ;
struct TYPE_7__ {TYPE_1__* vdev_ops; int /*<<< orphan*/ * vdev_spa; } ;
typedef  TYPE_2__ vdev_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  abd_t ;
struct TYPE_6__ {int /*<<< orphan*/  vdev_op_leaf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_TRUE ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENXIO ; 
 int /*<<< orphan*/  RW_WRITER ; 
 scalar_t__ SCL_ALL ; 
 size_t VDEV_PAD_SIZE ; 
 int ZIO_FLAG_CANFAIL ; 
 int ZIO_FLAG_CONFIG_WRITER ; 
 int ZIO_FLAG_TRYHARD ; 
 int /*<<< orphan*/ * abd_alloc_for_io (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abd_copy_from_buf (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  abd_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  abd_zero (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_config_held (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ vdev_is_dead (TYPE_2__*) ; 
 int /*<<< orphan*/  vdev_label_t ; 
 int /*<<< orphan*/  vdev_label_write (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vl_pad2 ; 
 int /*<<< orphan*/ * zio_root (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int zio_wait (int /*<<< orphan*/ *) ; 

int
vdev_label_write_pad2(vdev_t *vd, const char *buf, size_t size)
{
	spa_t *spa = vd->vdev_spa;
	zio_t *zio;
	abd_t *pad2;
	int flags = ZIO_FLAG_CONFIG_WRITER | ZIO_FLAG_CANFAIL;
	int error;

	if (size > VDEV_PAD_SIZE)
		return (EINVAL);

	if (!vd->vdev_ops->vdev_op_leaf)
		return (ENODEV);
	if (vdev_is_dead(vd))
		return (ENXIO);

	ASSERT(spa_config_held(spa, SCL_ALL, RW_WRITER) == SCL_ALL);

	pad2 = abd_alloc_for_io(VDEV_PAD_SIZE, B_TRUE);
	abd_zero(pad2, VDEV_PAD_SIZE);
	abd_copy_from_buf(pad2, buf, size);

retry:
	zio = zio_root(spa, NULL, NULL, flags);
	vdev_label_write(zio, vd, 0, pad2,
	    offsetof(vdev_label_t, vl_pad2),
	    VDEV_PAD_SIZE, NULL, NULL, flags);
	error = zio_wait(zio);
	if (error != 0 && !(flags & ZIO_FLAG_TRYHARD)) {
		flags |= ZIO_FLAG_TRYHARD;
		goto retry;
	}

	abd_free(pad2);
	return (error);
}