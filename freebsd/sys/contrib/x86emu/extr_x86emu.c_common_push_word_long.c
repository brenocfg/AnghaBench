#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  x_reg; } ;
struct TYPE_5__ {int /*<<< orphan*/  e_reg; } ;
union x86emu_register {TYPE_3__ I16_reg; TYPE_2__ I32_reg; } ;
struct TYPE_4__ {int mode; } ;
struct x86emu {TYPE_1__ x86; } ;

/* Variables and functions */
 int SYSMODE_PREFIX_DATA ; 
 int /*<<< orphan*/  push_long (struct x86emu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_word (struct x86emu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
common_push_word_long(struct x86emu *emu, union x86emu_register *reg)
{
	if (emu->x86.mode & SYSMODE_PREFIX_DATA)
		push_long(emu, reg->I32_reg.e_reg);
	else
		push_word(emu, reg->I16_reg.x_reg);
}