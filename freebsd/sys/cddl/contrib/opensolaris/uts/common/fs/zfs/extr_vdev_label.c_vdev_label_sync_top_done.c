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
struct TYPE_3__ {int /*<<< orphan*/  io_error; scalar_t__* io_private; } ;
typedef  TYPE_1__ zio_t ;
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (scalar_t__*,int) ; 

__attribute__((used)) static void
vdev_label_sync_top_done(zio_t *zio)
{
	uint64_t *good_writes = zio->io_private;

	if (*good_writes == 0)
		zio->io_error = SET_ERROR(EIO);

	kmem_free(good_writes, sizeof (uint64_t));
}