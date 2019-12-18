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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {int R_EFLG; int mode; } ;
struct x86emu {TYPE_1__ x86; } ;

/* Variables and functions */
 int F_ALWAYS_ON ; 
 int F_MSK ; 
 int SYSMODE_PREFIX_DATA ; 
 int /*<<< orphan*/  push_long (struct x86emu*,int) ; 
 int /*<<< orphan*/  push_word (struct x86emu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
x86emuOp_pushf_word(struct x86emu *emu)
{
	uint32_t flags;

	/* clear out *all* bits not representing flags, and turn on real bits */
	flags = (emu->x86.R_EFLG & F_MSK) | F_ALWAYS_ON;
	if (emu->x86.mode & SYSMODE_PREFIX_DATA) {
		push_long(emu, flags);
	} else {
		push_word(emu, (uint16_t) flags);
	}
}