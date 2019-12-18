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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct x86emu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iodev_write_1 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
x86bios_emu_outb(struct x86emu *emu, uint16_t port, uint8_t val)
{

#ifndef X86BIOS_NATIVE_ARCH
	if (port == 0xb2) /* APM scratch register */
		return;
	if (port >= 0x80 && port < 0x88) /* POST status register */
		return;
#endif

	iodev_write_1(port, val);
}