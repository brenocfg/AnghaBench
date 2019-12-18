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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct x86emu {int cur_mod; } ;

/* Variables and functions */
 int /*<<< orphan*/ * decode_rh_word_register (struct x86emu*) ; 
 scalar_t__ decode_rl_address (struct x86emu*) ; 
 int /*<<< orphan*/  fetch_data_word (struct x86emu*,scalar_t__) ; 
 int /*<<< orphan*/  fetch_decode_modrm (struct x86emu*) ; 
 int /*<<< orphan*/  x86emu_halt_sys (struct x86emu*) ; 

__attribute__((used)) static void
common_load_far_pointer(struct x86emu *emu, uint16_t *seg)
{
	uint16_t *dstreg;
	uint32_t srcoffset;

	fetch_decode_modrm(emu);
	if (emu->cur_mod == 3)
		x86emu_halt_sys(emu);

	dstreg = decode_rh_word_register(emu);
	srcoffset = decode_rl_address(emu);
	*dstreg = fetch_data_word(emu, srcoffset);
	*seg = fetch_data_word(emu, srcoffset + 2);
}