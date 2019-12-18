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
typedef  scalar_t__ u16 ;
struct TYPE_3__ {scalar_t__ vid_mode; } ;
struct TYPE_4__ {TYPE_1__ hdr; } ;

/* Variables and functions */
 scalar_t__ ASK_VGA ; 
 int /*<<< orphan*/  RESET_HEAP () ; 
 TYPE_2__ boot_params ; 
 scalar_t__ do_restore ; 
 scalar_t__ mode_menu () ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 
 int /*<<< orphan*/  probe_cards (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restore_screen () ; 
 int /*<<< orphan*/  save_screen () ; 
 int /*<<< orphan*/  set_mode (scalar_t__) ; 
 int /*<<< orphan*/  store_mode_params () ; 
 int /*<<< orphan*/  vesa_store_edid () ; 

void set_video(void)
{
	u16 mode = boot_params.hdr.vid_mode;

	RESET_HEAP();

	store_mode_params();
	save_screen();
	probe_cards(0);

	for (;;) {
		if (mode == ASK_VGA)
			mode = mode_menu();

		if (!set_mode(mode))
			break;

		printf("Undefined video mode number: %x\n", mode);
		mode = ASK_VGA;
	}
	boot_params.hdr.vid_mode = mode;
	vesa_store_edid();
	store_mode_params();

	if (do_restore)
		restore_screen();
}