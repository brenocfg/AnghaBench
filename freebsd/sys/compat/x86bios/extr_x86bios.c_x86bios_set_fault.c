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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  R_IP; int /*<<< orphan*/  R_CS; } ;
struct x86emu {TYPE_1__ x86; } ;

/* Variables and functions */
 int x86bios_fault ; 
 int /*<<< orphan*/  x86bios_fault_addr ; 
 int /*<<< orphan*/  x86bios_fault_cs ; 
 int /*<<< orphan*/  x86bios_fault_ip ; 
 int /*<<< orphan*/  x86emu_halt_sys (struct x86emu*) ; 

__attribute__((used)) static void
x86bios_set_fault(struct x86emu *emu, uint32_t addr)
{

	x86bios_fault = 1;
	x86bios_fault_addr = addr;
	x86bios_fault_cs = emu->x86.R_CS;
	x86bios_fault_ip = emu->x86.R_IP;
	x86emu_halt_sys(emu);
}