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
struct TYPE_2__ {int /*<<< orphan*/  R_DI; int /*<<< orphan*/  R_SI; int /*<<< orphan*/  R_BP; int /*<<< orphan*/  R_SP; int /*<<< orphan*/  R_BX; int /*<<< orphan*/  R_DX; int /*<<< orphan*/  R_CX; int /*<<< orphan*/  R_AX; } ;
struct x86emu {TYPE_1__ x86; } ;

/* Variables and functions */
 int /*<<< orphan*/  x86emu_halt_sys (struct x86emu*) ; 

__attribute__((used)) static uint16_t *
decode_rm_word_register(struct x86emu *emu, int reg)
{
	switch (reg) {
	case 0:
		return &emu->x86.R_AX;
	case 1:
		return &emu->x86.R_CX;
	case 2:
		return &emu->x86.R_DX;
	case 3:
		return &emu->x86.R_BX;
	case 4:
		return &emu->x86.R_SP;
	case 5:
		return &emu->x86.R_BP;
	case 6:
		return &emu->x86.R_SI;
	case 7:
		return &emu->x86.R_DI;
	default:
		x86emu_halt_sys(emu);
	}
}