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

__attribute__((used)) static int
chap_hex2int(const char hex)
{
	switch (hex) {
	case '0':
		return (0x00);
	case '1':
		return (0x01);
	case '2':
		return (0x02);
	case '3':
		return (0x03);
	case '4':
		return (0x04);
	case '5':
		return (0x05);
	case '6':
		return (0x06);
	case '7':
		return (0x07);
	case '8':
		return (0x08);
	case '9':
		return (0x09);
	case 'a':
	case 'A':
		return (0x0a);
	case 'b':
	case 'B':
		return (0x0b);
	case 'c':
	case 'C':
		return (0x0c);
	case 'd':
	case 'D':
		return (0x0d);
	case 'e':
	case 'E':
		return (0x0e);
	case 'f':
	case 'F':
		return (0x0f);
	default:
		return (-1);
	}
}