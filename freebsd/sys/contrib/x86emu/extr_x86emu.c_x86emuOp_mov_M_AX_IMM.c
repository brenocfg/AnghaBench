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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {int mode; int /*<<< orphan*/  R_AX; int /*<<< orphan*/  R_EAX; } ;
struct x86emu {TYPE_1__ x86; } ;

/* Variables and functions */
 int SYSMODE_PREFIX_DATA ; 
 int /*<<< orphan*/  fetch_word_imm (struct x86emu*) ; 
 int /*<<< orphan*/  store_data_long (struct x86emu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store_data_word (struct x86emu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
x86emuOp_mov_M_AX_IMM(struct x86emu *emu)
{
	uint16_t offset;

	offset = fetch_word_imm(emu);
	if (emu->x86.mode & SYSMODE_PREFIX_DATA) {
		store_data_long(emu, offset, emu->x86.R_EAX);
	} else {
		store_data_word(emu, offset, emu->x86.R_AX);
	}
}