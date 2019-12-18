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
struct ppc_data {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct ppc_data* DEVTOSOFTC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PPC_ASSERT_LOCKED (struct ppc_data*) ; 
 int /*<<< orphan*/  ppc_reset_epp_timeout (struct ppc_data*) ; 

int
ppc_reset_epp(device_t dev)
{
	struct ppc_data *ppc = DEVTOSOFTC(dev);

	PPC_ASSERT_LOCKED(ppc);
	ppc_reset_epp_timeout(ppc);

	return 0;
}