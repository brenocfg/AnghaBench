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
struct linux_prom_registers {int dummy; } ;
struct TYPE_2__ {int (* v3_cpustart ) (int,int,int,char*) ;} ;

/* Variables and functions */
#define  PROM_V0 130 
#define  PROM_V2 129 
#define  PROM_V3 128 
 int /*<<< orphan*/  prom_lock ; 
 int prom_vers ; 
 int /*<<< orphan*/  restore_current () ; 
 TYPE_1__* romvec ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (int,int,int,char*) ; 

int
prom_startcpu(int cpunode, struct linux_prom_registers *ctable_reg, int ctx, char *pc)
{
	int ret;
	unsigned long flags;

	spin_lock_irqsave(&prom_lock, flags);
	switch(prom_vers) {
	case PROM_V0:
	case PROM_V2:
	default:
		ret = -1;
		break;
	case PROM_V3:
		ret = (*(romvec->v3_cpustart))(cpunode, (int) ctable_reg, ctx, pc);
		break;
	}
	restore_current();
	spin_unlock_irqrestore(&prom_lock, flags);

	return ret;
}