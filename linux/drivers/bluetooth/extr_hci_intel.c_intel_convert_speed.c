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
typedef  int u8 ;

/* Variables and functions */

__attribute__((used)) static u8 intel_convert_speed(unsigned int speed)
{
	switch (speed) {
	case 9600:
		return 0x00;
	case 19200:
		return 0x01;
	case 38400:
		return 0x02;
	case 57600:
		return 0x03;
	case 115200:
		return 0x04;
	case 230400:
		return 0x05;
	case 460800:
		return 0x06;
	case 921600:
		return 0x07;
	case 1843200:
		return 0x08;
	case 3250000:
		return 0x09;
	case 2000000:
		return 0x0a;
	case 3000000:
		return 0x0b;
	default:
		return 0xff;
	}
}