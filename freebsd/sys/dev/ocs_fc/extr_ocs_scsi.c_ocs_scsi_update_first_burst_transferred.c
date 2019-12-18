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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  transferred; } ;
typedef  TYPE_1__ ocs_io_t ;

/* Variables and functions */

void
ocs_scsi_update_first_burst_transferred(ocs_io_t *io, uint32_t transferred)
{
	io->transferred = transferred;
}