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
struct x86emu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  decode_and_fetch_byte (struct x86emu*) ; 
 int /*<<< orphan*/ * decode_rh_byte_register (struct x86emu*) ; 
 int /*<<< orphan*/  fetch_decode_modrm (struct x86emu*) ; 
 int /*<<< orphan*/  write_back_byte (struct x86emu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
x86emuOp_xchg_byte_RM_R(struct x86emu *emu)
{
	uint8_t *srcreg, destval, tmp;

	fetch_decode_modrm(emu);
	destval = decode_and_fetch_byte(emu);
	srcreg = decode_rh_byte_register(emu);
	tmp = destval;
	destval = *srcreg;
	*srcreg = tmp;
	write_back_byte(emu, destval);
}