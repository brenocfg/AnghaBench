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
struct TYPE_2__ {int /*<<< orphan*/  R_AL; int /*<<< orphan*/  R_DX; } ;
struct x86emu {TYPE_1__ x86; int /*<<< orphan*/  (* emu_outb ) (struct x86emu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct x86emu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
x86emuOp_out_byte_DX_AL(struct x86emu *emu)
{
	(*emu->emu_outb) (emu, emu->x86.R_DX, emu->x86.R_AL);
}