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
struct x86emu {int dummy; } ;
typedef  scalar_t__ int8_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ decode_and_fetch_byte (struct x86emu*) ; 
 scalar_t__* decode_rh_long_register (struct x86emu*) ; 
 int /*<<< orphan*/  fetch_decode_modrm (struct x86emu*) ; 

__attribute__((used)) static void
x86emuOp2_32_movsx_byte_R_RM(struct x86emu *emu)
{
	uint32_t *destreg;

	fetch_decode_modrm(emu);
	destreg = decode_rh_long_register(emu);
	*destreg = (int32_t)(int8_t)decode_and_fetch_byte(emu);
}