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
typedef  void* uint16_t ;
struct TYPE_2__ {void* R_IP; void* R_CS; } ;
struct x86emu {TYPE_1__ x86; } ;

/* Variables and functions */
 void* fetch_word_imm (struct x86emu*) ; 
 int /*<<< orphan*/  push_word (struct x86emu*,void*) ; 

__attribute__((used)) static void
x86emuOp_call_far_IMM(struct x86emu *emu)
{
	uint16_t farseg, faroff;

	faroff = fetch_word_imm(emu);
	farseg = fetch_word_imm(emu);
	/* XXX
	 * 
	 * Hooked interrupt vectors calling into our "BIOS" will cause problems
	 * unless all intersegment stuff is checked for BIOS access.  Check
	 * needed here.  For moment, let it alone. */
	push_word(emu, emu->x86.R_CS);
	emu->x86.R_CS = farseg;
	push_word(emu, emu->x86.R_IP);
	emu->x86.R_IP = faroff;
}