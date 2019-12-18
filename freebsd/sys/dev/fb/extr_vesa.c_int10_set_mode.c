#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int R_AL; } ;
typedef  TYPE_1__ x86regs_t ;

/* Variables and functions */
 int /*<<< orphan*/  x86bios_init_regs (TYPE_1__*) ; 
 int /*<<< orphan*/  x86bios_intr (TYPE_1__*,int) ; 

__attribute__((used)) static int
int10_set_mode(int mode)
{
	x86regs_t regs;

	x86bios_init_regs(&regs);
	regs.R_AL = mode;

	x86bios_intr(&regs, 0x10);

	return (0);
}