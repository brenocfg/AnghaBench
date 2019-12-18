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
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 TYPE_2__* DP ; 
 TYPE_1__* DRS ; 
 int /*<<< orphan*/  FD_DISK_NEWCHANGE_BIT ; 
 int /*<<< orphan*/  current_reqD ; 
 int /*<<< orphan*/  debug_dcl (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  floppy_ready () ; 
 int /*<<< orphan*/  reschedule_timeout (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  scandrives () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void floppy_start(void)
{
	reschedule_timeout(current_reqD, "floppy start");

	scandrives();
	debug_dcl(DP->flags, "setting NEWCHANGE in floppy_start\n");
	set_bit(FD_DISK_NEWCHANGE_BIT, &DRS->flags);
	floppy_ready();
}