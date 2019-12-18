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
typedef  scalar_t__ uint16_t ;
struct x86emu {int dummy; } ;
typedef  scalar_t__ int8_t ;
typedef  scalar_t__ int16_t ;

/* Variables and functions */
 scalar_t__ decode_and_fetch_byte (struct x86emu*) ; 
 scalar_t__* decode_rh_word_register (struct x86emu*) ; 
 int /*<<< orphan*/  fetch_decode_modrm (struct x86emu*) ; 

__attribute__((used)) static void
x86emuOp2_16_movsx_byte_R_RM(struct x86emu *emu)
{
	uint16_t *destreg;

	fetch_decode_modrm(emu);
	destreg = decode_rh_word_register(emu);
	*destreg = (int16_t)(int8_t)decode_and_fetch_byte(emu);
}