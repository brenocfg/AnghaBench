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
 int /*<<< orphan*/  fetch_byte_imm (struct x86emu*) ; 
 int /*<<< orphan*/  x86emu_intr_dispatch (struct x86emu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
x86emuOp_int_IMM(struct x86emu *emu)
{
	uint8_t intnum;

	intnum = fetch_byte_imm(emu);
	x86emu_intr_dispatch(emu, intnum);
}