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
typedef  int u_int ;
struct TYPE_6__ {TYPE_2__* pcb_save; } ;
struct TYPE_4__ {int en_mxcsr; } ;
struct TYPE_5__ {TYPE_1__ sv_env; } ;

/* Variables and functions */
 scalar_t__ PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 TYPE_3__* curpcb ; 
 scalar_t__ curthread ; 
 int /*<<< orphan*/  fpcurthread ; 
 int* fpetable ; 
 int /*<<< orphan*/  stmxcsr (int*) ; 

int
fputrap_sse(void)
{
	u_int mxcsr;

	critical_enter();
	if (PCPU_GET(fpcurthread) != curthread)
		mxcsr = curpcb->pcb_save->sv_env.en_mxcsr;
	else
		stmxcsr(&mxcsr);
	critical_exit();
	return (fpetable[(mxcsr & (~mxcsr >> 7)) & 0x3f]);
}