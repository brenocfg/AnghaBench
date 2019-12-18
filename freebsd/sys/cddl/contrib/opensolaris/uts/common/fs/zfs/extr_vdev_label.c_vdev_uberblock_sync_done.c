#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ io_error; TYPE_2__* io_vd; int /*<<< orphan*/ * io_private; } ;
typedef  TYPE_3__ zio_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_6__ {TYPE_1__* vdev_top; } ;
struct TYPE_5__ {scalar_t__ vdev_ms_array; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc_64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vdev_uberblock_sync_done(zio_t *zio)
{
	uint64_t *good_writes = zio->io_private;

	if (zio->io_error == 0 && zio->io_vd->vdev_top->vdev_ms_array != 0)
		atomic_inc_64(good_writes);
}