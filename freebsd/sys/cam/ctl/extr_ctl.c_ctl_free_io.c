#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ pool; } ;
union ctl_io {TYPE_1__ io_hdr; } ;
struct ctl_io_pool {int /*<<< orphan*/  zone; } ;

/* Variables and functions */
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,union ctl_io*) ; 

void
ctl_free_io(union ctl_io *io)
{
	struct ctl_io_pool *pool;

	if (io == NULL)
		return;

	pool = (struct ctl_io_pool *)io->io_hdr.pool;
	uma_zfree(pool->zone, io);
}