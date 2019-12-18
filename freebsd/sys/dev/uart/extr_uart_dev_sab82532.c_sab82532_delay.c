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
struct uart_bas {int rclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAB_CCR2 ; 
 int /*<<< orphan*/  SAB_TCR ; 
 int uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sab82532_delay(struct uart_bas *bas)
{
	int divisor, m, n;
	uint8_t bgr, ccr2;

	bgr = uart_getreg(bas, SAB_TCR);
	ccr2 = uart_getreg(bas, SAB_CCR2);
	n = (bgr & 0x3f) + 1;
	m = (bgr >> 6) | ((ccr2 >> 4) & 0xC);
	divisor = n * (1<<m);

	/* 1/10th the time to transmit 1 character (estimate). */
	return (16000000 * divisor / bas->rclk);
}