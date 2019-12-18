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
struct TYPE_2__ {int level; } ;

/* Variables and functions */
 unsigned int TX4939_NUM_IR ; 
 TYPE_1__* tx4939irq ; 

__attribute__((used)) static int tx4939_irq_set_pri(int irc_irq, int new_pri)
{
	int old_pri;

	if ((unsigned int)irc_irq >= TX4939_NUM_IR)
		return 0;
	old_pri = tx4939irq[irc_irq].level;
	tx4939irq[irc_irq].level = new_pri;
	return old_pri;
}