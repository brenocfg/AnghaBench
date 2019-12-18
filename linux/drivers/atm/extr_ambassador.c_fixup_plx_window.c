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
typedef  unsigned long u32 ;
typedef  int /*<<< orphan*/  loader_block ;
typedef  int /*<<< orphan*/  amb_dev ;

/* Variables and functions */
 int /*<<< orphan*/  amb_mem ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long onegigmask ; 
 unsigned long rd_plain (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stuff ; 
 unsigned long virt_to_bus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wr_plain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void fixup_plx_window (amb_dev *dev, loader_block *lb)
{
	// fix up the PLX-mapped window base address to match the block
	unsigned long blb;
	u32 mapreg;
	blb = virt_to_bus(lb);
	// the kernel stack had better not ever cross a 1Gb boundary!
	mapreg = rd_plain (dev, offsetof(amb_mem, stuff[10]));
	mapreg &= ~onegigmask;
	mapreg |= blb & onegigmask;
	wr_plain (dev, offsetof(amb_mem, stuff[10]), mapreg);
	return;
}