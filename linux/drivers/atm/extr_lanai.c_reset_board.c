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
struct lanai_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int /*<<< orphan*/  Reset_Reg ; 
 int /*<<< orphan*/  reg_write (struct lanai_dev const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static inline void reset_board(const struct lanai_dev *lanai)
{
	DPRINTK("about to reset board\n");
	reg_write(lanai, 0, Reset_Reg);
	/*
	 * If we don't delay a little while here then we can end up
	 * leaving the card in a VERY weird state and lock up the
	 * PCI bus.  This isn't documented anywhere but I've convinced
	 * myself after a lot of painful experimentation
	 */
	udelay(5);
}