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
 int /*<<< orphan*/  E1CS2 (int /*<<< orphan*/ ) ; 
 unsigned char E1CS2_SCC ; 
 int /*<<< orphan*/  E1DAT (int /*<<< orphan*/ ) ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,unsigned char) ; 

unsigned char cte_in2 (port_t base, unsigned char reg)
{
	outb (E1CS2(base), E1CS2_SCC | reg >> 4);
	outb (E1DAT(base), reg & 15);
	return inb (E1DAT(base));
}