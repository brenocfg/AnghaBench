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
struct TYPE_6__ {int dor; } ;
struct TYPE_5__ {int flags; scalar_t__ select_delay; } ;
struct TYPE_4__ {int flags; scalar_t__ keep_data; int last_checked; scalar_t__ maxblock; scalar_t__ select_date; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int FDC (int) ; 
 TYPE_3__* FDCS ; 
 int FD_BROKEN_DCL ; 
 int /*<<< orphan*/  FD_DIR ; 
 int /*<<< orphan*/  FD_DISK_CHANGED_BIT ; 
 int /*<<< orphan*/  FD_DISK_NEWCHANGE_BIT ; 
 int /*<<< orphan*/  FD_VERIFY_BIT ; 
 int FTD_MSG ; 
 int MAX_DISK_SIZE ; 
 size_t TOMINOR (int) ; 
 TYPE_2__* UDP ; 
 TYPE_1__* UDRS ; 
 int UNIT (int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ ** current_type ; 
 int /*<<< orphan*/  debug_dcl (int,char*,int) ; 
 int fd_inb (int /*<<< orphan*/ ) ; 
 int* floppy_sizes ; 
 int jiffies ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int*) ; 
 int test_bit (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ time_before (int,scalar_t__) ; 

__attribute__((used)) static int disk_change(int drive)
{
	int fdc = FDC(drive);

	if (time_before(jiffies, UDRS->select_date + UDP->select_delay))
		DPRINT("WARNING disk change called early\n");
	if (!(FDCS->dor & (0x10 << UNIT(drive))) ||
	    (FDCS->dor & 3) != UNIT(drive) || fdc != FDC(drive)) {
		DPRINT("probing disk change on unselected drive\n");
		DPRINT("drive=%d fdc=%d dor=%x\n", drive, FDC(drive),
		       (unsigned int)FDCS->dor);
	}

	debug_dcl(UDP->flags,
		  "checking disk change line for drive %d\n", drive);
	debug_dcl(UDP->flags, "jiffies=%lu\n", jiffies);
	debug_dcl(UDP->flags, "disk change line=%x\n", fd_inb(FD_DIR) & 0x80);
	debug_dcl(UDP->flags, "flags=%lx\n", UDRS->flags);

	if (UDP->flags & FD_BROKEN_DCL)
		return test_bit(FD_DISK_CHANGED_BIT, &UDRS->flags);
	if ((fd_inb(FD_DIR) ^ UDP->flags) & 0x80) {
		set_bit(FD_VERIFY_BIT, &UDRS->flags);
					/* verify write protection */

		if (UDRS->maxblock)	/* mark it changed */
			set_bit(FD_DISK_CHANGED_BIT, &UDRS->flags);

		/* invalidate its geometry */
		if (UDRS->keep_data >= 0) {
			if ((UDP->flags & FTD_MSG) &&
			    current_type[drive] != NULL)
				DPRINT("Disk type is undefined after disk change\n");
			current_type[drive] = NULL;
			floppy_sizes[TOMINOR(drive)] = MAX_DISK_SIZE << 1;
		}

		return 1;
	} else {
		UDRS->last_checked = jiffies;
		clear_bit(FD_DISK_NEWCHANGE_BIT, &UDRS->flags);
	}
	return 0;
}