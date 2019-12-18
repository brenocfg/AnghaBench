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
typedef  int uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  R_AL; int /*<<< orphan*/  R_AX; } ;
struct x86emu {TYPE_1__ x86; } ;

/* Variables and functions */
 int /*<<< orphan*/  aam_word (struct x86emu*,int /*<<< orphan*/ ) ; 
 int fetch_byte_imm (struct x86emu*) ; 
 int /*<<< orphan*/  x86emu_halt_sys (struct x86emu*) ; 

__attribute__((used)) static void
x86emuOp_aam(struct x86emu *emu)
{
	uint8_t a;

	a = fetch_byte_imm(emu);	/* this is a stupid encoding. */
	if (a != 10) {
		/* fix: add base decoding aam_word(uint8_t val, int base a) */
		x86emu_halt_sys(emu);
	}
	/* note the type change here --- returning AL and AH in AX. */
	emu->x86.R_AX = aam_word(emu, emu->x86.R_AL);
}