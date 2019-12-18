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
struct TYPE_2__ {int mode; int R_ESP; int R_SP; void* R_AX; void* R_CX; void* R_DX; void* R_BX; void* R_BP; void* R_SI; void* R_DI; void* R_EAX; void* R_ECX; void* R_EDX; void* R_EBX; void* R_EBP; void* R_ESI; void* R_EDI; } ;
struct x86emu {TYPE_1__ x86; } ;

/* Variables and functions */
 int SYSMODE_PREFIX_DATA ; 
 void* pop_long (struct x86emu*) ; 
 void* pop_word (struct x86emu*) ; 

__attribute__((used)) static void
x86emuOp_pop_all(struct x86emu *emu)
{
	if (emu->x86.mode & SYSMODE_PREFIX_DATA) {
		emu->x86.R_EDI = pop_long(emu);
		emu->x86.R_ESI = pop_long(emu);
		emu->x86.R_EBP = pop_long(emu);
		emu->x86.R_ESP += 4;	/* skip ESP */
		emu->x86.R_EBX = pop_long(emu);
		emu->x86.R_EDX = pop_long(emu);
		emu->x86.R_ECX = pop_long(emu);
		emu->x86.R_EAX = pop_long(emu);
	} else {
		emu->x86.R_DI = pop_word(emu);
		emu->x86.R_SI = pop_word(emu);
		emu->x86.R_BP = pop_word(emu);
		emu->x86.R_SP += 2;/* skip SP */
		emu->x86.R_BX = pop_word(emu);
		emu->x86.R_DX = pop_word(emu);
		emu->x86.R_CX = pop_word(emu);
		emu->x86.R_AX = pop_word(emu);
	}
}