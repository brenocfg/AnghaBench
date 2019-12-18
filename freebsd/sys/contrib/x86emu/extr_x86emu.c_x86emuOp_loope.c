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
struct TYPE_2__ {scalar_t__ R_CX; scalar_t__ R_IP; } ;
struct x86emu {TYPE_1__ x86; } ;
typedef  scalar_t__ int8_t ;
typedef  scalar_t__ int16_t ;

/* Variables and functions */
 scalar_t__ ACCESS_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_ZF ; 
 scalar_t__ fetch_byte_imm (struct x86emu*) ; 

__attribute__((used)) static void
x86emuOp_loope(struct x86emu *emu)
{
	int16_t ip;

	ip = (int8_t) fetch_byte_imm(emu);
	ip += (int16_t) emu->x86.R_IP;
	emu->x86.R_CX -= 1;
	if (emu->x86.R_CX != 0 && ACCESS_FLAG(F_ZF))	/* CX != 0 and ZF */
		emu->x86.R_IP = ip;
}