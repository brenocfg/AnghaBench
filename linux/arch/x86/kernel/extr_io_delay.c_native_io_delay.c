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

/* Variables and functions */
#define  IO_DELAY_TYPE_0X80 131 
#define  IO_DELAY_TYPE_0XED 130 
#define  IO_DELAY_TYPE_NONE 129 
#define  IO_DELAY_TYPE_UDELAY 128 
 int io_delay_type ; 
 int /*<<< orphan*/  udelay (int) ; 

void native_io_delay(void)
{
	switch (io_delay_type) {
	default:
	case IO_DELAY_TYPE_0X80:
		asm volatile ("outb %al, $0x80");
		break;
	case IO_DELAY_TYPE_0XED:
		asm volatile ("outb %al, $0xed");
		break;
	case IO_DELAY_TYPE_UDELAY:
		/*
		 * 2 usecs is an upper-bound for the outb delay but
		 * note that udelay doesn't have the bus-level
		 * side-effects that outb does, nor does udelay() have
		 * precise timings during very early bootup (the delays
		 * are shorter until calibrated):
		 */
		udelay(2);
		break;
	case IO_DELAY_TYPE_NONE:
		break;
	}
}