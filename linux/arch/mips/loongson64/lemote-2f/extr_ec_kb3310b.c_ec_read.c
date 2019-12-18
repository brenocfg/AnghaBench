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
 int /*<<< orphan*/  EC_IO_PORT_DATA ; 
 int /*<<< orphan*/  EC_IO_PORT_HIGH ; 
 int /*<<< orphan*/  EC_IO_PORT_LOW ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_access_lock ; 
 int /*<<< orphan*/  outb (unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

unsigned char ec_read(unsigned short addr)
{
	unsigned char value;
	unsigned long flags;

	spin_lock_irqsave(&index_access_lock, flags);
	outb((addr & 0xff00) >> 8, EC_IO_PORT_HIGH);
	outb((addr & 0x00ff), EC_IO_PORT_LOW);
	value = inb(EC_IO_PORT_DATA);
	spin_unlock_irqrestore(&index_access_lock, flags);

	return value;
}