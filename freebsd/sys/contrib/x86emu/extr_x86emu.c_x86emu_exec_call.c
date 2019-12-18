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
typedef  void* uint16_t ;
struct TYPE_2__ {void* R_IP; void* R_CS; } ;
struct x86emu {TYPE_1__ x86; } ;

/* Variables and functions */
 int /*<<< orphan*/  push_word (struct x86emu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x86emu_exec (struct x86emu*) ; 

void
x86emu_exec_call(struct x86emu *emu, uint16_t seg, uint16_t off)
{
	push_word(emu, 0);
	push_word(emu, 0);
	emu->x86.R_CS = seg;
	emu->x86.R_IP = off;

	x86emu_exec(emu);
}