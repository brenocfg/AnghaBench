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
typedef  uintptr_t u_long ;
struct ppc_data {int /*<<< orphan*/  ppc_lock; int /*<<< orphan*/  ppc_epp; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  PPC_ASSERT_LOCKED (struct ppc_data*) ; 
#define  PPC_IVAR_EPP_PROTO 129 
#define  PPC_IVAR_LOCK 128 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 

int
ppc_read_ivar(device_t bus, device_t dev, int index, uintptr_t *val)
{
	struct ppc_data *ppc = (struct ppc_data *)device_get_softc(bus);

	switch (index) {
	case PPC_IVAR_EPP_PROTO:
		PPC_ASSERT_LOCKED(ppc);
		*val = (u_long)ppc->ppc_epp;
		break;
	case PPC_IVAR_LOCK:
		*val = (uintptr_t)&ppc->ppc_lock;
		break;
	default:
		return (ENOENT);
	}

	return (0);
}