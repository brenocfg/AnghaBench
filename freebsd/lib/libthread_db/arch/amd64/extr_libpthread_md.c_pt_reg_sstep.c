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
struct reg {int r_rflags; } ;
typedef  int register_t ;

/* Variables and functions */

int
pt_reg_sstep(struct reg *reg, int step)
{
	register_t old;

	old = reg->r_rflags;
	if (step)
		reg->r_rflags |= 0x0100;
	else
		reg->r_rflags &= ~0x0100;
	return (old != reg->r_rflags); /* changed ? */
}