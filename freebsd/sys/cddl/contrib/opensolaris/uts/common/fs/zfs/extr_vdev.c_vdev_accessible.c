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
struct TYPE_6__ {scalar_t__ io_type; TYPE_2__* io_vd; } ;
typedef  TYPE_1__ zio_t ;
struct TYPE_7__ {int /*<<< orphan*/  vdev_cant_write; int /*<<< orphan*/  vdev_cant_read; scalar_t__ vdev_remove_wanted; } ;
typedef  TYPE_2__ vdev_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int B_FALSE ; 
 int B_TRUE ; 
 scalar_t__ ZIO_TYPE_READ ; 
 scalar_t__ ZIO_TYPE_WRITE ; 
 scalar_t__ vdev_is_dead (TYPE_2__*) ; 

boolean_t
vdev_accessible(vdev_t *vd, zio_t *zio)
{
	ASSERT(zio->io_vd == vd);

	if (vdev_is_dead(vd) || vd->vdev_remove_wanted)
		return (B_FALSE);

	if (zio->io_type == ZIO_TYPE_READ)
		return (!vd->vdev_cant_read);

	if (zio->io_type == ZIO_TYPE_WRITE)
		return (!vd->vdev_cant_write);

	return (B_TRUE);
}