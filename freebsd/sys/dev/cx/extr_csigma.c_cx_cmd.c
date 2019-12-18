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
typedef  int /*<<< orphan*/  port_t ;

/* Variables and functions */
 int /*<<< orphan*/  CCR (int /*<<< orphan*/ ) ; 
 scalar_t__ inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 

void cx_cmd (port_t base, int cmd)
{
	port_t port = CCR(base);
	int count;

	/* Wait 10 msec for the previous command to complete. */
	for (count=0; inb(port) && count<20000; ++count)
		continue;

	/* Issue the command. */
	outb (port, cmd);

	/* Wait 10 msec for the command to complete. */
	for (count=0; inb(port) && count<20000; ++count)
		continue;
}