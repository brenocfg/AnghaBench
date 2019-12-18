#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  initid; } ;
struct TYPE_4__ {TYPE_1__ nexus; } ;
union ctl_io {TYPE_2__ io_hdr; } ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 

union ctl_io *
ctl_scsi_alloc_io(uint32_t initid)
{
	union ctl_io *io;

	io = (union ctl_io *)malloc(sizeof(*io));
	if (io == NULL)
		goto bailout;

	io->io_hdr.nexus.initid = initid;

bailout:
	return (io);
}