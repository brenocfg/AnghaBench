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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct x86emu {int cur_mod; int cur_rh; } ;

/* Variables and functions */
 int /*<<< orphan*/  dec_byte (struct x86emu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decode_rl_address (struct x86emu*) ; 
 int /*<<< orphan*/ * decode_rl_byte_register (struct x86emu*) ; 
 int /*<<< orphan*/  fetch_data_byte (struct x86emu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fetch_decode_modrm (struct x86emu*) ; 
 int /*<<< orphan*/  inc_byte (struct x86emu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store_data_byte (struct x86emu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
x86emuOp_opcFE_byte_RM(struct x86emu *emu)
{
	uint8_t destval;
	uint32_t destoffset;
	uint8_t *destreg;

	/* Yet another special case instruction. */
	fetch_decode_modrm(emu);
	if (emu->cur_mod != 3) {
		destoffset = decode_rl_address(emu);
		switch (emu->cur_rh) {
		case 0:	/* inc word ptr ... */
			destval = fetch_data_byte(emu, destoffset);
			destval = inc_byte(emu, destval);
			store_data_byte(emu, destoffset, destval);
			break;
		case 1:	/* dec word ptr ... */
			destval = fetch_data_byte(emu, destoffset);
			destval = dec_byte(emu, destval);
			store_data_byte(emu, destoffset, destval);
			break;
		}
	} else {
		destreg = decode_rl_byte_register(emu);
		switch (emu->cur_rh) {
		case 0:
			*destreg = inc_byte(emu, *destreg);
			break;
		case 1:
			*destreg = dec_byte(emu, *destreg);
			break;
		}
	}
}