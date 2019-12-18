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
 scalar_t__ ADDR_H ; 
 scalar_t__ ADDR_L ; 
 int /*<<< orphan*/  outb (unsigned short,scalar_t__) ; 

__attribute__((used)) static inline void bt3c_address(unsigned int iobase, unsigned short addr)
{
	outb(addr & 0xff, iobase + ADDR_L);
	outb((addr >> 8) & 0xff, iobase + ADDR_H);
}