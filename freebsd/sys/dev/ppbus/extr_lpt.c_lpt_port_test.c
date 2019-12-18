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
typedef  int u_char ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  lprintf (char*) ; 
 int ppb_rdtr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_wdtr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
lpt_port_test(device_t ppbus, u_char data, u_char mask)
{
	int	temp, timeout;

	data = data & mask;
	ppb_wdtr(ppbus, data);
	timeout = 10000;
	do {
		DELAY(10);
		temp = ppb_rdtr(ppbus) & mask;
	}
	while (temp != data && --timeout);
	lprintf(("out=%x\tin=%x\ttout=%d\n", data, temp, timeout));
	return (temp == data);
}