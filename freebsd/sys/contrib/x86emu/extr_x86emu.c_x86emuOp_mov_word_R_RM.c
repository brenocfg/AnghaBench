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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {int mode; } ;
struct x86emu {TYPE_1__ x86; } ;

/* Variables and functions */
 int SYSMODE_PREFIX_DATA ; 
 int /*<<< orphan*/  decode_and_fetch_long (struct x86emu*) ; 
 int /*<<< orphan*/  decode_and_fetch_word (struct x86emu*) ; 
 int /*<<< orphan*/ * decode_rh_long_register (struct x86emu*) ; 
 int /*<<< orphan*/ * decode_rh_word_register (struct x86emu*) ; 
 int /*<<< orphan*/  fetch_decode_modrm (struct x86emu*) ; 

__attribute__((used)) static void
x86emuOp_mov_word_R_RM(struct x86emu *emu)
{
	if (emu->x86.mode & SYSMODE_PREFIX_DATA) {
		uint32_t *destreg;

		fetch_decode_modrm(emu);
		destreg = decode_rh_long_register(emu);
		*destreg = decode_and_fetch_long(emu);
	} else {
		uint16_t *destreg;

		fetch_decode_modrm(emu);
		destreg = decode_rh_word_register(emu);
		*destreg = decode_and_fetch_word(emu);
	}
}