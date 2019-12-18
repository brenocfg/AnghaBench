#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zio_t ;
struct TYPE_6__ {TYPE_1__* vdev_ops; } ;
typedef  TYPE_2__ vdev_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_5__ {int /*<<< orphan*/  vdev_op_leaf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int ZIO_FLAG_CANFAIL ; 
 int ZIO_FLAG_DONT_AGGREGATE ; 
 int ZIO_FLAG_DONT_PROPAGATE ; 
 int ZIO_FLAG_DONT_RETRY ; 
 int /*<<< orphan*/  ZIO_FREE_PHYS_PIPELINE ; 
 int /*<<< orphan*/  ZIO_PRIORITY_TRIM ; 
 int /*<<< orphan*/  ZIO_STAGE_OPEN ; 
 int /*<<< orphan*/  ZIO_TYPE_FREE ; 
 int /*<<< orphan*/ * zio_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

zio_t *
zio_trim(zio_t *zio, spa_t *spa, vdev_t *vd, uint64_t offset, uint64_t size)
{

	ASSERT(vd->vdev_ops->vdev_op_leaf);

	return (zio_create(zio, spa, 0, NULL, NULL, size, size, NULL, NULL,
	    ZIO_TYPE_FREE, ZIO_PRIORITY_TRIM, ZIO_FLAG_DONT_AGGREGATE |
	    ZIO_FLAG_CANFAIL | ZIO_FLAG_DONT_PROPAGATE | ZIO_FLAG_DONT_RETRY,
	    vd, offset, NULL, ZIO_STAGE_OPEN, ZIO_FREE_PHYS_PIPELINE));
}