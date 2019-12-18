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
struct TYPE_2__ {int mode; int R_CX; int R_DI; int /*<<< orphan*/  R_AX; int /*<<< orphan*/  R_ES; int /*<<< orphan*/  R_EAX; } ;
struct x86emu {TYPE_1__ x86; } ;

/* Variables and functions */
 scalar_t__ ACCESS_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_DF ; 
 int SYSMODE_PREFIX_DATA ; 
 int SYSMODE_PREFIX_REPE ; 
 int SYSMODE_PREFIX_REPNE ; 
 int /*<<< orphan*/  store_long (struct x86emu*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store_word (struct x86emu*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
x86emuOp_stos_word(struct x86emu *emu)
{
	int inc;
	uint32_t count;

	if (emu->x86.mode & SYSMODE_PREFIX_DATA)
		inc = 4;
	else
		inc = 2;
	
	if (ACCESS_FLAG(F_DF))	/* down */
		inc = -inc;

	count = 1;
	if (emu->x86.mode & (SYSMODE_PREFIX_REPE | SYSMODE_PREFIX_REPNE)) {
		/* dont care whether REPE or REPNE */
		/* move them until CX is ZERO. */
		count = emu->x86.R_CX;
		emu->x86.R_CX = 0;
		emu->x86.mode &= ~(SYSMODE_PREFIX_REPE | SYSMODE_PREFIX_REPNE);
	}
	while (count--) {
		if (emu->x86.mode & SYSMODE_PREFIX_DATA) {
			store_long(emu, emu->x86.R_ES, emu->x86.R_DI,
			    emu->x86.R_EAX);
		} else {
			store_word(emu, emu->x86.R_ES, emu->x86.R_DI,
			    emu->x86.R_AX);
		}
		emu->x86.R_DI += inc;
	}
}