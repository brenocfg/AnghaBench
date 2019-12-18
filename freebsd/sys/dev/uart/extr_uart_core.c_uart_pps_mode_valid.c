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
#define  UART_PPS_CTS 130 
#define  UART_PPS_DCD 129 
#define  UART_PPS_DISABLED 128 
 int UART_PPS_INVERT_PULSE ; 
 int UART_PPS_NARROW_PULSE ; 
 int UART_PPS_OPTION_MASK ; 
 int UART_PPS_SIGNAL_MASK ; 

__attribute__((used)) static inline int
uart_pps_mode_valid(int pps_mode)
{
	int opt;

	switch(pps_mode & UART_PPS_SIGNAL_MASK) {
	case UART_PPS_DISABLED:
	case UART_PPS_CTS:
	case UART_PPS_DCD:
		break;
	default:
		return (false);
	}

	opt = pps_mode & UART_PPS_OPTION_MASK;
	if ((opt & ~(UART_PPS_INVERT_PULSE | UART_PPS_NARROW_PULSE)) != 0)
		return (false);

	return (true);
}