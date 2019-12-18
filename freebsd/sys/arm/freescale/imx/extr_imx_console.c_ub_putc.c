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
 int /*<<< orphan*/  IMX_TXD ; 
 int /*<<< orphan*/  IMX_UTS ; 
 int IMX_UTS_TXFULL ; 
 int ub_getreg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ub_setreg (int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void
ub_putc(unsigned char c)
{

	if (c == '\n')
		ub_putc('\r');

	while (ub_getreg(IMX_UTS) & IMX_UTS_TXFULL)
		__asm __volatile("nop");

	ub_setreg(IMX_TXD, c);
}