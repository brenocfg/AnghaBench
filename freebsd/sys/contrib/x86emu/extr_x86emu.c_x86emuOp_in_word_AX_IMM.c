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
struct TYPE_2__ {int mode; int /*<<< orphan*/  R_AX; int /*<<< orphan*/  R_EAX; } ;
struct x86emu {int /*<<< orphan*/  (* emu_inw ) (struct x86emu*,scalar_t__) ;TYPE_1__ x86; int /*<<< orphan*/  (* emu_inl ) (struct x86emu*,scalar_t__) ;} ;

/* Variables and functions */
 int SYSMODE_PREFIX_DATA ; 
 scalar_t__ fetch_byte_imm (struct x86emu*) ; 
 int /*<<< orphan*/  stub1 (struct x86emu*,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (struct x86emu*,scalar_t__) ; 

__attribute__((used)) static void
x86emuOp_in_word_AX_IMM(struct x86emu *emu)
{
	uint8_t port;

	port = (uint8_t) fetch_byte_imm(emu);
	if (emu->x86.mode & SYSMODE_PREFIX_DATA) {
		emu->x86.R_EAX = (*emu->emu_inl) (emu, port);
	} else {
		emu->x86.R_AX = (*emu->emu_inw) (emu, port);
	}
}