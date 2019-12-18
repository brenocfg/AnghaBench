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
 unsigned int BASE_BAUD ; 
 unsigned char DLAB ; 
 scalar_t__ DLH ; 
 scalar_t__ DLL ; 
 scalar_t__ LCR ; 
 unsigned char inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 

__attribute__((used)) static unsigned int probe_baud(int port)
{
	unsigned char lcr, dll, dlh;
	unsigned int quot;

	lcr = inb(port + LCR);
	outb(lcr | DLAB, port + LCR);
	dll = inb(port + DLL);
	dlh = inb(port + DLH);
	outb(lcr, port + LCR);
	quot = (dlh << 8) | dll;

	return BASE_BAUD / quot;
}