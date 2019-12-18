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
struct TYPE_2__ {int rd_data_reg_sel; int wd_data; } ;

/* Variables and functions */
 scalar_t__ MACH_IS_FALCON ; 
 int SelectedDrive ; 
 scalar_t__ atari_dont_touch_floppy_select ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 TYPE_1__ sound_ym ; 

__attribute__((used)) static void fd_deselect( void )
{
	unsigned long flags;

	/* protect against various other ints mucking around with the PSG */
	local_irq_save(flags);
	atari_dont_touch_floppy_select = 0;
	sound_ym.rd_data_reg_sel=14;	/* Select PSG Port A */
	sound_ym.wd_data = (sound_ym.rd_data_reg_sel |
			    (MACH_IS_FALCON ? 3 : 7)); /* no drives selected */
	/* On Falcon, the drive B select line is used on the printer port, so
	 * leave it alone... */
	SelectedDrive = -1;
	local_irq_restore(flags);
}