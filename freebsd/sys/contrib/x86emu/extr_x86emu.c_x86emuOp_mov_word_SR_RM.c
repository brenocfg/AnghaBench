#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct x86emu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  decode_and_fetch_word (struct x86emu*) ; 
 int /*<<< orphan*/ * decode_rh_seg_register (struct x86emu*) ; 
 int /*<<< orphan*/  fetch_decode_modrm (struct x86emu*) ; 

__attribute__((used)) static void
x86emuOp_mov_word_SR_RM(struct x86emu *emu)
{
	uint16_t *destreg;

	fetch_decode_modrm(emu);
	destreg = decode_rh_seg_register(emu);
	*destreg = decode_and_fetch_word(emu);
	/*
         * Clean up, and reset all the R_xSP pointers to the correct
         * locations.  This is about 3x too much overhead (doing all the
         * segreg ptrs when only one is needed, but this instruction
         * *cannot* be that common, and this isn't too much work anyway.
         */
}