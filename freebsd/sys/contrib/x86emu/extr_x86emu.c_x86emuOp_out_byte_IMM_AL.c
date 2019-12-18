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
typedef  scalar_t__ uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  R_AL; } ;
struct x86emu {TYPE_1__ x86; int /*<<< orphan*/  (* emu_outb ) (struct x86emu*,scalar_t__,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ fetch_byte_imm (struct x86emu*) ; 
 int /*<<< orphan*/  stub1 (struct x86emu*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
x86emuOp_out_byte_IMM_AL(struct x86emu *emu)
{
	uint8_t port;

	port = (uint8_t) fetch_byte_imm(emu);
	(*emu->emu_outb) (emu, port, emu->x86.R_AL);
}