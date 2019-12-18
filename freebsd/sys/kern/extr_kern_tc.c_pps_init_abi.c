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
struct pps_state {scalar_t__ driver_abi; int /*<<< orphan*/  kernel_abi; int /*<<< orphan*/  kcmode; } ;

/* Variables and functions */
 int /*<<< orphan*/  KCMODE_ABIFLAG ; 
 int /*<<< orphan*/  PPS_ABI_VERSION ; 
 int /*<<< orphan*/  pps_init (struct pps_state*) ; 

void
pps_init_abi(struct pps_state *pps)
{

	pps_init(pps);
	if (pps->driver_abi > 0) {
		pps->kcmode |= KCMODE_ABIFLAG;
		pps->kernel_abi = PPS_ABI_VERSION;
	}
}