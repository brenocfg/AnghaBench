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
struct TYPE_6__ {scalar_t__ select_delay; } ;
struct TYPE_5__ {scalar_t__ select_delay; } ;
struct TYPE_4__ {scalar_t__ fd_ref; } ;

/* Variables and functions */
 TYPE_3__* DP ; 
 int N_DRIVE ; 
 TYPE_2__* UDP ; 
 TYPE_1__* UDRS ; 
 int UNIT (int) ; 
 int current_drive ; 
 int /*<<< orphan*/  fdc ; 
 int set_dor (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  set_fdc (int) ; 

__attribute__((used)) static void scandrives(void)
{
	int i;
	int drive;
	int saved_drive;

	if (DP->select_delay)
		return;

	saved_drive = current_drive;
	for (i = 0; i < N_DRIVE; i++) {
		drive = (saved_drive + i + 1) % N_DRIVE;
		if (UDRS->fd_ref == 0 || UDP->select_delay != 0)
			continue;	/* skip closed drives */
		set_fdc(drive);
		if (!(set_dor(fdc, ~3, UNIT(drive) | (0x10 << UNIT(drive))) &
		      (0x10 << UNIT(drive))))
			/* switch the motor off again, if it was off to
			 * begin with */
			set_dor(fdc, ~(0x10 << UNIT(drive)), 0);
	}
	set_fdc(saved_drive);
}