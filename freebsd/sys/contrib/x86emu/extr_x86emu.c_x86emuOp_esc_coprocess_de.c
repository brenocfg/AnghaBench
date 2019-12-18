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
struct x86emu {int cur_mod; } ;

/* Variables and functions */
 int /*<<< orphan*/  decode_rl_address (struct x86emu*) ; 
 int /*<<< orphan*/  fetch_decode_modrm (struct x86emu*) ; 

__attribute__((used)) static void 
x86emuOp_esc_coprocess_de(struct x86emu *emu)
{
	fetch_decode_modrm(emu);
	if (emu->cur_mod != 3)
		decode_rl_address(emu);
}