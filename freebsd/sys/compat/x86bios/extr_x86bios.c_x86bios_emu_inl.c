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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct x86emu {int dummy; } ;

/* Variables and functions */
 int iodev_read_1 (int) ; 
 int iodev_read_2 (int) ; 
 int iodev_read_4 (int) ; 

__attribute__((used)) static uint32_t
x86bios_emu_inl(struct x86emu *emu, uint16_t port)
{
	uint32_t val;

#ifndef X86BIOS_NATIVE_ARCH
	if (port >= 0x80 && port < 0x88) /* POST status register */
		return (0);

	if ((port & 1) != 0) {
		val = iodev_read_1(port);
		val |= iodev_read_2(port + 1) << 8;
		val |= iodev_read_1(port + 3) << 24;
	} else if ((port & 2) != 0) {
		val = iodev_read_2(port);
		val |= iodev_read_2(port + 2) << 16;
	} else
#endif
	val = iodev_read_4(port);

	return (val);
}