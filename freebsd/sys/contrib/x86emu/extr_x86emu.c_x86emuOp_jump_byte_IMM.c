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
typedef  scalar_t__ uint16_t ;
struct TYPE_2__ {scalar_t__ R_IP; } ;
struct x86emu {TYPE_1__ x86; } ;
typedef  scalar_t__ int8_t ;

/* Variables and functions */
 scalar_t__ fetch_byte_imm (struct x86emu*) ; 

__attribute__((used)) static void
x86emuOp_jump_byte_IMM(struct x86emu *emu)
{
	uint16_t target;
	int8_t offset;

	offset = (int8_t) fetch_byte_imm(emu);
	target = (uint16_t) (emu->x86.R_IP + offset);
	emu->x86.R_IP = target;
}