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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {scalar_t__ R_AX; scalar_t__ R_AH; scalar_t__ R_AL; } ;
struct x86emu {TYPE_1__ x86; } ;

/* Variables and functions */
 int /*<<< orphan*/  x86emu_intr_raise (struct x86emu*,int) ; 

__attribute__((used)) static void 
div_byte(struct x86emu *emu, uint8_t s)
{
	uint32_t dvd, div, mod;

	dvd = emu->x86.R_AX;
	if (s == 0) {
		x86emu_intr_raise(emu, 8);
		return;
	}
	div = dvd / (uint8_t) s;
	mod = dvd % (uint8_t) s;
	if (div > 0xff) {
		x86emu_intr_raise(emu, 8);
		return;
	}
	emu->x86.R_AL = (uint8_t) div;
	emu->x86.R_AH = (uint8_t) mod;
}