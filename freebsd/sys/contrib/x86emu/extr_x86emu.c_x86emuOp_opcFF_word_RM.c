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
typedef  void* uint16_t ;
struct TYPE_2__ {int mode; void* R_IP; void* R_CS; } ;
struct x86emu {int cur_mod; int cur_rh; TYPE_1__ x86; } ;

/* Variables and functions */
 int SYSMODE_PREFIX_DATA ; 
 int /*<<< orphan*/  decode_rl_address (struct x86emu*) ; 
 void** decode_rl_word_register (struct x86emu*) ; 
 void* fetch_data_word (struct x86emu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fetch_decode_modrm (struct x86emu*) ; 
 int /*<<< orphan*/  push_word (struct x86emu*,void*) ; 
 int /*<<< orphan*/  x86emuOp16_opcFF_word_RM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp32_opcFF_word_RM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emu_halt_sys (struct x86emu*) ; 

__attribute__((used)) static void
x86emuOp_opcFF_word_RM(struct x86emu *emu)
{
	uint32_t destoffset = 0;
	uint16_t destval, destval2;

	/* Yet another special case instruction. */
	fetch_decode_modrm(emu);
	if ((emu->cur_mod == 3 && (emu->cur_rh == 3 || emu->cur_rh == 5)) ||
	    emu->cur_rh == 7)
		x86emu_halt_sys(emu);
	if (emu->cur_rh == 0 || emu->cur_rh == 1 || emu->cur_rh == 6) {
		if (emu->x86.mode & SYSMODE_PREFIX_DATA)
			x86emuOp32_opcFF_word_RM(emu);
		else
			x86emuOp16_opcFF_word_RM(emu);
		return;
	}

	if (emu->cur_mod != 3) {
		destoffset = decode_rl_address(emu);
		destval = fetch_data_word(emu, destoffset);
		switch (emu->cur_rh) {
		case 3:	/* call far ptr ... */
			destval2 = fetch_data_word(emu, destoffset + 2);
			push_word(emu, emu->x86.R_CS);
			emu->x86.R_CS = destval2;
			push_word(emu, emu->x86.R_IP);
			emu->x86.R_IP = destval;
			break;
		case 5:	/* jmp far ptr ... */
			destval2 = fetch_data_word(emu, destoffset + 2);
			emu->x86.R_IP = destval;
			emu->x86.R_CS = destval2;
			break;
		}
	} else {
		destval = *decode_rl_word_register(emu);
	}

	switch (emu->cur_rh) {
	case 2: /* call word ptr */
		push_word(emu, emu->x86.R_IP);
		emu->x86.R_IP = destval;
		break;
	case 4: /* jmp */
		emu->x86.R_IP = destval;
		break;
	}
}