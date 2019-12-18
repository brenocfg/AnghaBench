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
struct TYPE_2__ {int mode; } ;
struct x86emu {TYPE_1__ x86; } ;
typedef  scalar_t__ int8_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  scalar_t__ int16_t ;

/* Variables and functions */
 int SYSMODE_PREFIX_DATA ; 
 scalar_t__ fetch_byte_imm (struct x86emu*) ; 
 int /*<<< orphan*/  push_long (struct x86emu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_word (struct x86emu*,scalar_t__) ; 

__attribute__((used)) static void
x86emuOp_push_byte_IMM(struct x86emu *emu)
{
	int16_t imm;

	imm = (int8_t) fetch_byte_imm(emu);
	if (emu->x86.mode & SYSMODE_PREFIX_DATA) {
		push_long(emu, (int32_t) imm);
	} else {
		push_word(emu, imm);
	}
}