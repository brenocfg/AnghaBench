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
typedef  int uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
#define  B0 137 
#define  B1200 136 
#define  B19200 135 
#define  B2400 134 
#define  B300 133 
#define  B38400 132 
#define  B4800 131 
#define  B57600 130 
#define  B600 129 
#define  B9600 128 

__attribute__((used)) static uint8_t
umct_calc_baud(uint32_t baud)
{
	switch (baud) {
		case B300:return (0x1);
	case B600:
		return (0x2);
	case B1200:
		return (0x3);
	case B2400:
		return (0x4);
	case B4800:
		return (0x6);
	case B9600:
		return (0x8);
	case B19200:
		return (0x9);
	case B38400:
		return (0xa);
	case B57600:
		return (0xb);
	case 115200:
		return (0xc);
	case B0:
	default:
		break;
	}
	return (0x0);
}