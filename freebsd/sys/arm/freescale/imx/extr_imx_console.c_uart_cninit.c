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
struct consdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMX_UFCR ; 
 int /*<<< orphan*/  ub_setreg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
uart_cninit(struct consdev *cp)
{

        /* Init fifo trigger levels to 32 bytes, refclock div to 2. */
	ub_setreg(IMX_UFCR, 0x00004210);
}