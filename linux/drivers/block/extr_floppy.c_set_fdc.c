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
struct TYPE_2__ {int rawcmd; int reset; } ;

/* Variables and functions */
 int FDC (int) ; 
 TYPE_1__* FDCS ; 
 int /*<<< orphan*/  FD_STATUS ; 
 int N_DRIVE ; 
 scalar_t__ STATUS_READY ; 
 int current_drive ; 
 scalar_t__ fd_inb (int /*<<< orphan*/ ) ; 
 int fdc ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  reset_fdc_info (int) ; 
 int /*<<< orphan*/  set_dor (int,int,int) ; 

__attribute__((used)) static void set_fdc(int drive)
{
	if (drive >= 0 && drive < N_DRIVE) {
		fdc = FDC(drive);
		current_drive = drive;
	}
	if (fdc != 1 && fdc != 0) {
		pr_info("bad fdc value\n");
		return;
	}
	set_dor(fdc, ~0, 8);
#if N_FDC > 1
	set_dor(1 - fdc, ~8, 0);
#endif
	if (FDCS->rawcmd == 2)
		reset_fdc_info(1);
	if (fd_inb(FD_STATUS) != STATUS_READY)
		FDCS->reset = 1;
}