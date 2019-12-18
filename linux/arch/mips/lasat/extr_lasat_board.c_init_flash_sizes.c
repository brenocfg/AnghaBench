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
struct TYPE_2__ {unsigned long* li_flashpart_base; unsigned long* li_flashpart_size; int li_flash_base; int li_flash_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_LASAT_200 () ; 
 size_t LASAT_MTD_BOOTLOADER ; 
 size_t LASAT_MTD_CONFIG ; 
 size_t LASAT_MTD_FS ; 
 int LASAT_MTD_LAST ; 
 size_t LASAT_MTD_NORMAL ; 
 size_t LASAT_MTD_SERVICE ; 
 TYPE_1__ lasat_board_info ; 

__attribute__((used)) static void init_flash_sizes(void)
{
	unsigned long *lb = lasat_board_info.li_flashpart_base;
	unsigned long *ls = lasat_board_info.li_flashpart_size;
	int i;

	ls[LASAT_MTD_BOOTLOADER] = 0x40000;
	ls[LASAT_MTD_SERVICE] = 0xC0000;
	ls[LASAT_MTD_NORMAL] = 0x100000;

	if (!IS_LASAT_200()) {
		lasat_board_info.li_flash_base = 0x1e000000;

		lb[LASAT_MTD_BOOTLOADER] = 0x1e400000;

		if (lasat_board_info.li_flash_size > 0x200000) {
			ls[LASAT_MTD_CONFIG] = 0x100000;
			ls[LASAT_MTD_FS] = 0x500000;
		}
	} else {
		lasat_board_info.li_flash_base = 0x10000000;

		if (lasat_board_info.li_flash_size < 0x1000000) {
			lb[LASAT_MTD_BOOTLOADER] = 0x10000000;
			ls[LASAT_MTD_CONFIG] = 0x100000;
			if (lasat_board_info.li_flash_size >= 0x400000)
				ls[LASAT_MTD_FS] =
				     lasat_board_info.li_flash_size - 0x300000;
		}
	}

	for (i = 1; i < LASAT_MTD_LAST; i++)
		lb[i] = lb[i-1] + ls[i-1];
}