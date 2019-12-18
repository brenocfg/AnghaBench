#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct locked_reg {scalar_t__ reg; scalar_t__ key; } ;
struct TYPE_2__ {struct locked_reg* locked; } ;

/* Variables and functions */
 int MAX_LOCKED_REGS ; 
 TYPE_1__ dscr ; 

__attribute__((used)) static struct locked_reg *find_locked_reg(u32 reg)
{
	int i;

	for (i = 0; i < MAX_LOCKED_REGS; i++)
		if (dscr.locked[i].key && reg == dscr.locked[i].reg)
			return &dscr.locked[i];
	return NULL;
}