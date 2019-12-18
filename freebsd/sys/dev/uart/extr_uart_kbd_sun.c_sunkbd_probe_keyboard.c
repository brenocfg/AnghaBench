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
struct uart_devinfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  SKBD_CMD_RESET ; 
#define  SKBD_RSP_IDLE 128 
 int SKBD_RSP_RESET ; 
 int uart_poll (struct uart_devinfo*) ; 
 int /*<<< orphan*/  uart_putc (struct uart_devinfo*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sunkbd_probe_keyboard(struct uart_devinfo *di)
{
	int c, id, ltries, tries;

	for (tries = 5; tries != 0; tries--) {
		uart_putc(di, SKBD_CMD_RESET);
		for (ltries = 1000; ltries != 0; ltries--) {
			if (uart_poll(di) == SKBD_RSP_RESET)
				break;
			DELAY(1000);
		}
		if (ltries == 0)
			continue;
		id = -1;
		for (ltries = 1000; ltries != 0; ltries--) {
			switch (c = uart_poll(di)) {
			case -1:
				break;
			case SKBD_RSP_IDLE:
				return (id);
			default:
				id = c;
			}
			DELAY(1000);
		}
	}
	return (-1);
}