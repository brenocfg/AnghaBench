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
typedef  int /*<<< orphan*/  AT91PS_USART ;

/* Variables and functions */
 scalar_t__ AT91F_US_GetChar (int /*<<< orphan*/ ) ; 
 scalar_t__ AT91F_US_RxReady (int /*<<< orphan*/ ) ; 
 int port_detected ; 
 scalar_t__ us ; 
 scalar_t__* usa ; 

int at91_serial_getc()
{
	while(1) {
#if 0
		if (!port_detected) {
			if (us == usa[0]) {
				us = usa[1];
			}
			else {
				us = usa[0];
			}
		}
#endif
		if(AT91F_US_RxReady((AT91PS_USART)us)) {
#if 0
			port_detected = 1;
#endif
			return((int)AT91F_US_GetChar((AT91PS_USART)us));
		}
	}
}