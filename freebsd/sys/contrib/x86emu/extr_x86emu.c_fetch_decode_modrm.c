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
struct x86emu {int cur_mod; int cur_rh; int cur_rl; } ;

/* Variables and functions */
 int fetch_byte_imm (struct x86emu*) ; 

__attribute__((used)) static void 
fetch_decode_modrm(struct x86emu *emu)
{
	int fetched;

	fetched = fetch_byte_imm(emu);
	emu->cur_mod = (fetched >> 6) & 0x03;
	emu->cur_rh = (fetched >> 3) & 0x07;
	emu->cur_rl = (fetched >> 0) & 0x07;
}