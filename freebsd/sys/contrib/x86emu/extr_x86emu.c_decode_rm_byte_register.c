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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  R_BH; int /*<<< orphan*/  R_DH; int /*<<< orphan*/  R_CH; int /*<<< orphan*/  R_AH; int /*<<< orphan*/  R_BL; int /*<<< orphan*/  R_DL; int /*<<< orphan*/  R_CL; int /*<<< orphan*/  R_AL; } ;
struct x86emu {TYPE_1__ x86; } ;

/* Variables and functions */
 int /*<<< orphan*/  x86emu_halt_sys (struct x86emu*) ; 

__attribute__((used)) static uint8_t *
decode_rm_byte_register(struct x86emu *emu, int reg)
{
	switch (reg) {
	case 0:
		return &emu->x86.R_AL;
	case 1:
		return &emu->x86.R_CL;
	case 2:
		return &emu->x86.R_DL;
	case 3:
		return &emu->x86.R_BL;
	case 4:
		return &emu->x86.R_AH;
	case 5:
		return &emu->x86.R_CH;
	case 6:
		return &emu->x86.R_DH;
	case 7:
		return &emu->x86.R_BH;
	default:
		x86emu_halt_sys(emu);
	}
}