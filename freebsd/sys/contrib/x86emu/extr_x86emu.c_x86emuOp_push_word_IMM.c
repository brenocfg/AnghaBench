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
struct TYPE_2__ {int mode; } ;
struct x86emu {TYPE_1__ x86; } ;

/* Variables and functions */
 int SYSMODE_PREFIX_DATA ; 
 int /*<<< orphan*/  fetch_long_imm (struct x86emu*) ; 
 int /*<<< orphan*/  fetch_word_imm (struct x86emu*) ; 
 int /*<<< orphan*/  push_long (struct x86emu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_word (struct x86emu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
x86emuOp_push_word_IMM(struct x86emu *emu)
{
	if (emu->x86.mode & SYSMODE_PREFIX_DATA) {
		uint32_t imm;

		imm = fetch_long_imm(emu);
		push_long(emu, imm);
	} else {
		uint16_t imm;

		imm = fetch_word_imm(emu);
		push_word(emu, imm);
	}
}