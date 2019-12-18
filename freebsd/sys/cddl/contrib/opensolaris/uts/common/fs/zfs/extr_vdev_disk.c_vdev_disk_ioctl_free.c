#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  io_vsd; } ;
typedef  TYPE_1__ zio_t ;
struct dk_callback {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
vdev_disk_ioctl_free(zio_t *zio)
{
	kmem_free(zio->io_vsd, sizeof (struct dk_callback));
}