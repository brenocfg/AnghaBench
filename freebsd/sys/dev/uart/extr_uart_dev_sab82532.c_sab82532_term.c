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
struct uart_bas {int chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAB_PVR ; 
 int /*<<< orphan*/  SAB_PVR_DTR_A ; 
 int /*<<< orphan*/  SAB_PVR_DTR_B ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int /*<<< orphan*/  uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sab82532_term(struct uart_bas *bas)
{
	uint8_t pvr;

	pvr = uart_getreg(bas, SAB_PVR);
	switch (bas->chan) {
	case 1:
		pvr |= SAB_PVR_DTR_A;
		break;
	case 2:
		pvr |= SAB_PVR_DTR_B;
		break;
	}
	uart_setreg(bas, SAB_PVR, pvr);
	uart_barrier(bas);
}