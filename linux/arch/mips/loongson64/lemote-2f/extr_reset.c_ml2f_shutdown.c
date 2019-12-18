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
typedef  int u8 ;
typedef  int u64 ;

/* Variables and functions */
 int BIT_SHUTDOWN_ON ; 
 int /*<<< orphan*/  EC_SHUTDOWN_IO_PORT_DATA ; 
 int /*<<< orphan*/  EC_SHUTDOWN_IO_PORT_HIGH ; 
 int /*<<< orphan*/  EC_SHUTDOWN_IO_PORT_LOW ; 
 int REG_SHUTDOWN_HIGH ; 
 int REG_SHUTDOWN_LOW ; 
 int /*<<< orphan*/  delay () ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ml2f_shutdown(void)
{
	u8 val;
	u64 i;

	outb(REG_SHUTDOWN_HIGH, EC_SHUTDOWN_IO_PORT_HIGH);
	outb(REG_SHUTDOWN_LOW, EC_SHUTDOWN_IO_PORT_LOW);
	mmiowb();
	val = inb(EC_SHUTDOWN_IO_PORT_DATA);
	outb(val & (~BIT_SHUTDOWN_ON), EC_SHUTDOWN_IO_PORT_DATA);
	mmiowb();
	/* need enough wait here... how many microseconds needs? */
	for (i = 0; i < 0x10000; i++)
		delay();
	outb(val | BIT_SHUTDOWN_ON, EC_SHUTDOWN_IO_PORT_DATA);
	mmiowb();
}