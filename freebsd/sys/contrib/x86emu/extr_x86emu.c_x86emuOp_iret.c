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
struct TYPE_2__ {void* R_FLG; void* R_CS; void* R_IP; } ;
struct x86emu {TYPE_1__ x86; } ;

/* Variables and functions */
 void* pop_word (struct x86emu*) ; 

__attribute__((used)) static void
x86emuOp_iret(struct x86emu *emu)
{
	emu->x86.R_IP = pop_word(emu);
	emu->x86.R_CS = pop_word(emu);
	emu->x86.R_FLG = pop_word(emu);
}