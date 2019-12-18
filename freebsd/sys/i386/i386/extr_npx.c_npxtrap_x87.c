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
typedef  int u_short ;

/* Variables and functions */
 int GET_FPU_CW (scalar_t__) ; 
 int GET_FPU_SW (scalar_t__) ; 
 scalar_t__ PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 scalar_t__ curthread ; 
 int /*<<< orphan*/  fnstcw (int*) ; 
 int /*<<< orphan*/  fnstsw (int*) ; 
 int /*<<< orphan*/  fpcurthread ; 
 int* fpetable ; 
 int hw_float ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__,scalar_t__,int) ; 

int
npxtrap_x87(void)
{
	u_short control, status;

	if (!hw_float) {
		printf(
	"npxtrap_x87: fpcurthread = %p, curthread = %p, hw_float = %d\n",
		       PCPU_GET(fpcurthread), curthread, hw_float);
		panic("npxtrap from nowhere");
	}
	critical_enter();

	/*
	 * Interrupt handling (for another interrupt) may have pushed the
	 * state to memory.  Fetch the relevant parts of the state from
	 * wherever they are.
	 */
	if (PCPU_GET(fpcurthread) != curthread) {
		control = GET_FPU_CW(curthread);
		status = GET_FPU_SW(curthread);
	} else {
		fnstcw(&control);
		fnstsw(&status);
	}
	critical_exit();
	return (fpetable[status & ((~control & 0x3f) | 0x40)]);
}