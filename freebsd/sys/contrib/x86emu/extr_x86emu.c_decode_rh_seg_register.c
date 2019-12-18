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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  R_GS; int /*<<< orphan*/  R_FS; int /*<<< orphan*/  R_DS; int /*<<< orphan*/  R_SS; int /*<<< orphan*/  R_CS; int /*<<< orphan*/  R_ES; } ;
struct x86emu {int cur_rh; TYPE_1__ x86; } ;

/* Variables and functions */
 int /*<<< orphan*/  x86emu_halt_sys (struct x86emu*) ; 

__attribute__((used)) static uint16_t *
decode_rh_seg_register(struct x86emu *emu)
{
	switch (emu->cur_rh) {
	case 0:
		return &emu->x86.R_ES;
	case 1:
		return &emu->x86.R_CS;
	case 2:
		return &emu->x86.R_SS;
	case 3:
		return &emu->x86.R_DS;
	case 4:
		return &emu->x86.R_FS;
	case 5:
		return &emu->x86.R_GS;
	default:
		x86emu_halt_sys(emu);
	}
}