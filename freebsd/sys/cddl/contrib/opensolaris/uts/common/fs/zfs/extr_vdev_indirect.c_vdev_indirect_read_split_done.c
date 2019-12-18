#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ io_error; TYPE_2__* io_private; } ;
typedef  TYPE_1__ zio_t ;
struct TYPE_5__ {int /*<<< orphan*/ * ic_data; } ;
typedef  TYPE_2__ indirect_child_t ;

/* Variables and functions */
 int /*<<< orphan*/  abd_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vdev_indirect_read_split_done(zio_t *zio)
{
	indirect_child_t *ic = zio->io_private;

	if (zio->io_error != 0) {
		/*
		 * Clear ic_data to indicate that we do not have data for this
		 * child.
		 */
		abd_free(ic->ic_data);
		ic->ic_data = NULL;
	}
}