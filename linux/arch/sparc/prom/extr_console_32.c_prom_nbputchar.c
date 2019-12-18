#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * fd_stdout; } ;
struct TYPE_4__ {int (* v2_dev_write ) (int /*<<< orphan*/ ,char const*,int) ;} ;
struct TYPE_6__ {TYPE_2__ pv_v2bootargs; TYPE_1__ pv_v2devops; int /*<<< orphan*/  (* pv_nbputchar ) (char const) ;} ;

/* Variables and functions */
#define  PROM_V0 130 
#define  PROM_V2 129 
#define  PROM_V3 128 
 int /*<<< orphan*/  prom_lock ; 
 int prom_vers ; 
 int /*<<< orphan*/  restore_current () ; 
 TYPE_3__* romvec ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (char const) ; 
 int stub2 (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static int prom_nbputchar(const char *buf)
{
	unsigned long flags;
	int i = -1;

	spin_lock_irqsave(&prom_lock, flags);
	switch(prom_vers) {
	case PROM_V0:
		if ((*(romvec->pv_nbputchar))(*buf))
			i = 1;
		break;
	case PROM_V2:
	case PROM_V3:
		if ((*(romvec->pv_v2devops).v2_dev_write)(*romvec->pv_v2bootargs.fd_stdout,
							  buf, 0x1) == 1)
			i = 1;
		break;
	default:
		break;
	}
	restore_current();
	spin_unlock_irqrestore(&prom_lock, flags);
	return i; /* Ugh, we could spin forever on unsupported proms ;( */
}