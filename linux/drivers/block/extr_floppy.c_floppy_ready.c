#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  select_delay; int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {scalar_t__ reset; } ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  length; int /*<<< orphan*/  kernel_data; } ;

/* Variables and functions */
 TYPE_3__* DP ; 
 TYPE_2__* FDCS ; 
 int FD_RAW_NEED_DISK ; 
 int FD_RAW_NEED_SEEK ; 
 int FD_RAW_NO_MOTOR ; 
 int FD_RAW_READ ; 
 int FD_RAW_WRITE ; 
 unsigned long claim_dma_lock () ; 
 int /*<<< orphan*/  current_drive ; 
 int /*<<< orphan*/  debug_dcl (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ disk_change (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fd_chose_dma_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fdc_dtr () ; 
 int /*<<< orphan*/  fdc_specify () ; 
 int /*<<< orphan*/  perpendicular_mode () ; 
 TYPE_1__* raw_cmd ; 
 int /*<<< orphan*/  release_dma_lock (unsigned long) ; 
 int /*<<< orphan*/  reset_fdc () ; 
 int /*<<< orphan*/  seek_floppy () ; 
 int /*<<< orphan*/  setup_rw_floppy () ; 
 scalar_t__ start_motor (void (*) ()) ; 
 int /*<<< orphan*/  twaddle () ; 

__attribute__((used)) static void floppy_ready(void)
{
	if (FDCS->reset) {
		reset_fdc();
		return;
	}
	if (start_motor(floppy_ready))
		return;
	if (fdc_dtr())
		return;

	debug_dcl(DP->flags, "calling disk change from floppy_ready\n");
	if (!(raw_cmd->flags & FD_RAW_NO_MOTOR) &&
	    disk_change(current_drive) && !DP->select_delay)
		twaddle();	/* this clears the dcl on certain
				 * drive/controller combinations */

#ifdef fd_chose_dma_mode
	if ((raw_cmd->flags & FD_RAW_READ) || (raw_cmd->flags & FD_RAW_WRITE)) {
		unsigned long flags = claim_dma_lock();
		fd_chose_dma_mode(raw_cmd->kernel_data, raw_cmd->length);
		release_dma_lock(flags);
	}
#endif

	if (raw_cmd->flags & (FD_RAW_NEED_SEEK | FD_RAW_NEED_DISK)) {
		perpendicular_mode();
		fdc_specify();	/* must be done here because of hut, hlt ... */
		seek_floppy();
	} else {
		if ((raw_cmd->flags & FD_RAW_READ) ||
		    (raw_cmd->flags & FD_RAW_WRITE))
			fdc_specify();
		setup_rw_floppy();
	}
}