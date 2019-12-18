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
 int /*<<< orphan*/  IMX_RXD ; 
 int ub_getreg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ub_tstc () ; 

__attribute__((used)) static int
ub_getc(void)
{

	while (!ub_tstc());
		__asm __volatile("nop");

	return (ub_getreg(IMX_RXD) & 0xff);
}