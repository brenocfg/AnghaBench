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
struct TYPE_2__ {void* pool; } ;
union ctl_io {TYPE_1__ io_hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (union ctl_io*,int /*<<< orphan*/ ,int) ; 

void
ctl_scsi_zero_io(union ctl_io *io)
{
	void *pool_ref;

	if (io == NULL)
		return;

	pool_ref = io->io_hdr.pool;
	memset(io, 0, sizeof(*io));
	io->io_hdr.pool = pool_ref;
}