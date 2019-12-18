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
typedef  int /*<<< orphan*/  uint32_t ;
struct x86emu {int cur_mod; int cur_rh; } ;

/* Variables and functions */
 int /*<<< orphan*/  dec_long (struct x86emu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decode_rl_address (struct x86emu*) ; 
 int /*<<< orphan*/ * decode_rl_long_register (struct x86emu*) ; 
 int /*<<< orphan*/  fetch_data_long (struct x86emu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inc_long (struct x86emu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_long (struct x86emu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store_data_long (struct x86emu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
x86emuOp32_opcFF_word_RM(struct x86emu *emu)
{
	uint32_t destoffset = 0;
	uint32_t destval, *destreg;

	if (emu->cur_mod != 3) {
		destoffset = decode_rl_address(emu);
		destval = fetch_data_long(emu, destoffset);
		switch (emu->cur_rh) {
		case 0:	/* inc word ptr ... */
			destval = inc_long(emu, destval);
			store_data_long(emu, destoffset, destval);
			break;
		case 1:	/* dec word ptr ... */
			destval = dec_long(emu, destval);
			store_data_long(emu, destoffset, destval);
			break;
		case 6:	/* push word ptr ... */
			push_long(emu, destval);
			break;
		}
	} else {
		destreg = decode_rl_long_register(emu);
		switch (emu->cur_rh) {
		case 0:
			*destreg = inc_long(emu, *destreg);
			break;
		case 1:
			*destreg = dec_long(emu, *destreg);
			break;
		case 6:
			push_long(emu, *destreg);
			break;
		}
	}
}