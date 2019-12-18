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
typedef  union savefpu {int dummy; } savefpu ;
typedef  int /*<<< orphan*/  register_t ;

/* Variables and functions */
 int /*<<< orphan*/ * PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,union savefpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_max_ext_state_size ; 
 int /*<<< orphan*/  fpcurthread ; 
 int /*<<< orphan*/  fpusave (union savefpu*) ; 
 int /*<<< orphan*/  hw_float ; 
 int /*<<< orphan*/  load_cr0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  npx_initialstate ; 
 int /*<<< orphan*/  rcr0 () ; 
 int /*<<< orphan*/  stop_emulating () ; 

void
npxsuspend(union savefpu *addr)
{
	register_t cr0;

	if (!hw_float)
		return;
	if (PCPU_GET(fpcurthread) == NULL) {
		bcopy(npx_initialstate, addr, cpu_max_ext_state_size);
		return;
	}
	cr0 = rcr0();
	stop_emulating();
	fpusave(addr);
	load_cr0(cr0);
}