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
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {int R_EAX; scalar_t__ R_EDX; } ;
struct x86emu {TYPE_1__ x86; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONDITIONAL_SET_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_AF ; 
 int /*<<< orphan*/  F_CF ; 
 int /*<<< orphan*/  F_PF ; 
 int /*<<< orphan*/  F_SF ; 
 int /*<<< orphan*/  F_ZF ; 
 int /*<<< orphan*/  PARITY (int) ; 
 int /*<<< orphan*/  SET_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x86emu_intr_raise (struct x86emu*,int) ; 

__attribute__((used)) static void 
div_long(struct x86emu *emu, uint32_t s)
{
	uint64_t dvd, div, mod;

	dvd = (((uint64_t) emu->x86.R_EDX) << 32) | emu->x86.R_EAX;
	if (s == 0) {
		x86emu_intr_raise(emu, 8);
		return;
	}
	div = dvd / (uint32_t) s;
	mod = dvd % (uint32_t) s;
	if (div > 0xffffffff) {
		x86emu_intr_raise(emu, 8);
		return;
	}
	CLEAR_FLAG(F_CF);
	CLEAR_FLAG(F_AF);
	CLEAR_FLAG(F_SF);
	SET_FLAG(F_ZF);
	CONDITIONAL_SET_FLAG(PARITY(mod & 0xff), F_PF);

	emu->x86.R_EAX = (uint32_t) div;
	emu->x86.R_EDX = (uint32_t) mod;
}