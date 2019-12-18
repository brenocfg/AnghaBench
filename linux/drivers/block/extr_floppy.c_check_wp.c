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
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int reset; } ;

/* Variables and functions */
 TYPE_3__* DP ; 
 TYPE_2__* DRS ; 
 TYPE_1__* FDCS ; 
 int /*<<< orphan*/  FD_DISK_WRITABLE_BIT ; 
 int /*<<< orphan*/  FD_GETSTATUS ; 
 int /*<<< orphan*/  FD_NEED_TWADDLE_BIT ; 
 int /*<<< orphan*/  FD_VERIFY_BIT ; 
 int ST3 ; 
 int /*<<< orphan*/  UNIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current_drive ; 
 int /*<<< orphan*/  debug_dcl (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  output_byte (int /*<<< orphan*/ ) ; 
 int result () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void check_wp(void)
{
	if (test_bit(FD_VERIFY_BIT, &DRS->flags)) {
					/* check write protection */
		output_byte(FD_GETSTATUS);
		output_byte(UNIT(current_drive));
		if (result() != 1) {
			FDCS->reset = 1;
			return;
		}
		clear_bit(FD_VERIFY_BIT, &DRS->flags);
		clear_bit(FD_NEED_TWADDLE_BIT, &DRS->flags);
		debug_dcl(DP->flags,
			  "checking whether disk is write protected\n");
		debug_dcl(DP->flags, "wp=%x\n", ST3 & 0x40);
		if (!(ST3 & 0x40))
			set_bit(FD_DISK_WRITABLE_BIT, &DRS->flags);
		else
			clear_bit(FD_DISK_WRITABLE_BIT, &DRS->flags);
	}
}