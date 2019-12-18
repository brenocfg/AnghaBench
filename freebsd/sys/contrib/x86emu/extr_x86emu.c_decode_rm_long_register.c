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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  R_EDI; int /*<<< orphan*/  R_ESI; int /*<<< orphan*/  R_EBP; int /*<<< orphan*/  R_ESP; int /*<<< orphan*/  R_EBX; int /*<<< orphan*/  R_EDX; int /*<<< orphan*/  R_ECX; int /*<<< orphan*/  R_EAX; } ;
struct x86emu {TYPE_1__ x86; } ;

/* Variables and functions */
 int /*<<< orphan*/  x86emu_halt_sys (struct x86emu*) ; 

__attribute__((used)) static uint32_t *
decode_rm_long_register(struct x86emu *emu, int reg)
{
	switch (reg) {
	case 0:
		return &emu->x86.R_EAX;
	case 1:
		return &emu->x86.R_ECX;
	case 2:
		return &emu->x86.R_EDX;
	case 3:
		return &emu->x86.R_EBX;
	case 4:
		return &emu->x86.R_ESP;
	case 5:
		return &emu->x86.R_EBP;
	case 6:
		return &emu->x86.R_ESI;
	case 7:
		return &emu->x86.R_EDI;
	default:
		x86emu_halt_sys(emu);
	}
}