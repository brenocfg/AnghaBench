#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_short ;
struct TYPE_3__ {int en_cw; int en_sw; } ;
struct savefpu {TYPE_1__ sv_env; } ;
struct TYPE_4__ {struct savefpu* pcb_save; } ;

/* Variables and functions */
 scalar_t__ PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 TYPE_2__* curpcb ; 
 scalar_t__ curthread ; 
 int /*<<< orphan*/  fnstcw (int*) ; 
 int /*<<< orphan*/  fnstsw (int*) ; 
 int /*<<< orphan*/  fpcurthread ; 
 int* fpetable ; 

int
fputrap_x87(void)
{
	struct savefpu *pcb_save;
	u_short control, status;

	critical_enter();

	/*
	 * Interrupt handling (for another interrupt) may have pushed the
	 * state to memory.  Fetch the relevant parts of the state from
	 * wherever they are.
	 */
	if (PCPU_GET(fpcurthread) != curthread) {
		pcb_save = curpcb->pcb_save;
		control = pcb_save->sv_env.en_cw;
		status = pcb_save->sv_env.en_sw;
	} else {
		fnstcw(&control);
		fnstsw(&status);
	}

	critical_exit();
	return (fpetable[status & ((~control & 0x3f) | 0x40)]);
}