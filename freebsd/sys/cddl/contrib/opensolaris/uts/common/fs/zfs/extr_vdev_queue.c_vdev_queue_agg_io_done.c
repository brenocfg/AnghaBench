#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ io_type; int /*<<< orphan*/  io_abd; int /*<<< orphan*/  io_size; scalar_t__ io_offset; } ;
typedef  TYPE_1__ zio_t ;
typedef  int /*<<< orphan*/  zio_link_t ;

/* Variables and functions */
 scalar_t__ ZIO_TYPE_READ ; 
 int /*<<< orphan*/  abd_copy_off (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abd_free (int /*<<< orphan*/ ) ; 
 TYPE_1__* zio_walk_parents (TYPE_1__*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void
vdev_queue_agg_io_done(zio_t *aio)
{
	if (aio->io_type == ZIO_TYPE_READ) {
		zio_t *pio;
		zio_link_t *zl = NULL;
		while ((pio = zio_walk_parents(aio, &zl)) != NULL) {
			abd_copy_off(pio->io_abd, aio->io_abd,
			    0, pio->io_offset - aio->io_offset, pio->io_size);
		}
	}

	abd_free(aio->io_abd);
}