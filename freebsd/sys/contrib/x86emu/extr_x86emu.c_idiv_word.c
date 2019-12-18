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
typedef  scalar_t__ uint16_t ;
struct TYPE_2__ {int R_AX; scalar_t__ R_DX; } ;
struct x86emu {TYPE_1__ x86; } ;
typedef  int int32_t ;
typedef  int int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONDITIONAL_SET_FLAG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_CF ; 
 int /*<<< orphan*/  F_PF ; 
 int /*<<< orphan*/  F_SF ; 
 int /*<<< orphan*/  F_ZF ; 
 int PARITY (int) ; 
 int /*<<< orphan*/  x86emu_intr_raise (struct x86emu*,int) ; 

__attribute__((used)) static void 
idiv_word(struct x86emu *emu, uint16_t s)
{
	int32_t dvd, div, mod;

	dvd = (((int32_t) emu->x86.R_DX) << 16) | emu->x86.R_AX;
	if (s == 0) {
		x86emu_intr_raise(emu, 8);
		return;
	}
	div = dvd / (int16_t) s;
	mod = dvd % (int16_t) s;
	if (div > 0x7fff || div < -0x7fff) {
		x86emu_intr_raise(emu, 8);
		return;
	}
	CLEAR_FLAG(F_CF);
	CLEAR_FLAG(F_SF);
	CONDITIONAL_SET_FLAG(div == 0, F_ZF);
	CONDITIONAL_SET_FLAG(PARITY(mod & 0xff), F_PF);

	emu->x86.R_AX = (uint16_t) div;
	emu->x86.R_DX = (uint16_t) mod;
}