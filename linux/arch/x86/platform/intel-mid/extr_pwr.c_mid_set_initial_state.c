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
typedef  int /*<<< orphan*/  u32 ;
struct mid_pwr {TYPE_1__** lss; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SET_CFG ; 
 unsigned int LSS_MAX_DEVS ; 
 unsigned int LSS_MAX_SHARED_DEVS ; 
 int /*<<< orphan*/  PCI_D3hot ; 
 int /*<<< orphan*/  mid_pwr_set_state (struct mid_pwr*,int,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  mid_pwr_set_wake (struct mid_pwr*,int,int) ; 
 int mid_pwr_wait_for_cmd (struct mid_pwr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mid_set_initial_state(struct mid_pwr *pwr, const u32 *states)
{
	unsigned int i, j;
	int ret;

	/*
	 * Enable wake events.
	 *
	 * PWRMU supports up to 32 sources for wake up the system. Ungate them
	 * all here.
	 */
	mid_pwr_set_wake(pwr, 0, 0xffffffff);
	mid_pwr_set_wake(pwr, 1, 0xffffffff);

	/*
	 * Power off South Complex devices.
	 *
	 * There is a map (see a note below) of 64 devices with 2 bits per each
	 * on 32-bit HW registers. The following calls set all devices to one
	 * known initial state, i.e. PCI_D3hot. This is done in conjunction
	 * with PMCSR setting in arch/x86/pci/intel_mid_pci.c.
	 *
	 * NOTE: The actual device mapping is provided by a platform at run
	 * time using vendor capability of PCI configuration space.
	 */
	mid_pwr_set_state(pwr, 0, states[0]);
	mid_pwr_set_state(pwr, 1, states[1]);
	mid_pwr_set_state(pwr, 2, states[2]);
	mid_pwr_set_state(pwr, 3, states[3]);

	/* Send command to SCU */
	ret = mid_pwr_wait_for_cmd(pwr, CMD_SET_CFG);
	if (ret)
		return ret;

	for (i = 0; i < LSS_MAX_DEVS; i++) {
		for (j = 0; j < LSS_MAX_SHARED_DEVS; j++)
			pwr->lss[i][j].state = PCI_D3hot;
	}

	return 0;
}