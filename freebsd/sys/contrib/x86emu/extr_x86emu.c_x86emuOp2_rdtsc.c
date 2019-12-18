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
struct TYPE_2__ {int R_EAX; int R_EDX; } ;
struct x86emu {int cur_cycles; TYPE_1__ x86; } ;

/* Variables and functions */

__attribute__((used)) static void
x86emuOp2_rdtsc(struct x86emu *emu)
{
	emu->x86.R_EAX = emu->cur_cycles & 0xffffffff;
	emu->x86.R_EDX = emu->cur_cycles >> 32;
}