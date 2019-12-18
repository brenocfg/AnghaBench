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
struct uart_bas {int rclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDNC_UART_BAUDDIV_REG ; 
 int /*<<< orphan*/  CDNC_UART_BAUDGEN_REG ; 
 int /*<<< orphan*/  WR4 (struct uart_bas*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
cdnc_uart_set_baud(struct uart_bas *bas, int baudrate)
{
	uint32_t baudgen, bauddiv;
	uint32_t best_bauddiv, best_baudgen, best_error;
	uint32_t baud_out, err;

	best_bauddiv = 0;
	best_baudgen = 0;
	best_error = ~0;

	/* Try all possible bauddiv values and pick best match. */
	for (bauddiv = 4; bauddiv <= 255; bauddiv++) {
		baudgen = (bas->rclk + (baudrate * (bauddiv + 1)) / 2) /
			(baudrate * (bauddiv + 1));
		if (baudgen < 1 || baudgen > 0xffff)
			continue;

		baud_out = bas->rclk / (baudgen * (bauddiv + 1));
		err = baud_out > baudrate ?
			baud_out - baudrate : baudrate - baud_out;

		if (err < best_error) {
			best_error = err;
			best_bauddiv = bauddiv;
			best_baudgen = baudgen;
		}
	}

	if (best_bauddiv > 0) {
		WR4(bas, CDNC_UART_BAUDDIV_REG, best_bauddiv);
		WR4(bas, CDNC_UART_BAUDGEN_REG, best_baudgen);
		return (0);
	} else
		return (-1); /* out of range */
}