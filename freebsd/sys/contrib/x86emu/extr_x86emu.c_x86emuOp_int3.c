#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct x86emu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  x86emu_intr_dispatch (struct x86emu*,int) ; 

__attribute__((used)) static void
x86emuOp_int3(struct x86emu *emu)
{
	x86emu_intr_dispatch(emu, 3);
}