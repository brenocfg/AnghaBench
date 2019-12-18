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
struct consdev {int /*<<< orphan*/  cn_arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPAL_POLL_EVENTS ; 
 int /*<<< orphan*/  opal_call (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uart_opal_put (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static void
uart_opal_cnputc(struct consdev *cp, int c)
{
	unsigned char ch = c;
	int a;

	if (1) {
		/* Clear FIFO if needed. Must be repeated few times. */
		for (a = 0; a < 20; a++) {
			opal_call(OPAL_POLL_EVENTS, NULL);
		}
	}
	uart_opal_put(cp->cn_arg, &ch, 1);
}