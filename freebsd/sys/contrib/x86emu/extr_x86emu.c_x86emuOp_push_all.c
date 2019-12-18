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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {int mode; int /*<<< orphan*/  R_DI; int /*<<< orphan*/  R_SI; int /*<<< orphan*/  R_BP; int /*<<< orphan*/  R_BX; int /*<<< orphan*/  R_DX; int /*<<< orphan*/  R_CX; int /*<<< orphan*/  R_AX; int /*<<< orphan*/  R_SP; int /*<<< orphan*/  R_EDI; int /*<<< orphan*/  R_ESI; int /*<<< orphan*/  R_EBP; int /*<<< orphan*/  R_EBX; int /*<<< orphan*/  R_EDX; int /*<<< orphan*/  R_ECX; int /*<<< orphan*/  R_EAX; int /*<<< orphan*/  R_ESP; } ;
struct x86emu {TYPE_1__ x86; } ;

/* Variables and functions */
 int SYSMODE_PREFIX_DATA ; 
 int /*<<< orphan*/  push_long (struct x86emu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_word (struct x86emu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
x86emuOp_push_all(struct x86emu *emu)
{
	if (emu->x86.mode & SYSMODE_PREFIX_DATA) {
		uint32_t old_sp = emu->x86.R_ESP;

		push_long(emu, emu->x86.R_EAX);
		push_long(emu, emu->x86.R_ECX);
		push_long(emu, emu->x86.R_EDX);
		push_long(emu, emu->x86.R_EBX);
		push_long(emu, old_sp);
		push_long(emu, emu->x86.R_EBP);
		push_long(emu, emu->x86.R_ESI);
		push_long(emu, emu->x86.R_EDI);
	} else {
		uint16_t old_sp = emu->x86.R_SP;

		push_word(emu, emu->x86.R_AX);
		push_word(emu, emu->x86.R_CX);
		push_word(emu, emu->x86.R_DX);
		push_word(emu, emu->x86.R_BX);
		push_word(emu, old_sp);
		push_word(emu, emu->x86.R_BP);
		push_word(emu, emu->x86.R_SI);
		push_word(emu, emu->x86.R_DI);
	}
}