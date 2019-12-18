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
struct ppc_data {int ppc_type; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct ppc_data* DEVTOSOFTC (int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 int /*<<< orphan*/  PPC_ASSERT_LOCKED (struct ppc_data*) ; 
#define  PPC_TYPE_GENERIC 129 
#define  PPC_TYPE_SMCLIKE 128 
 int ppc_generic_setmode (struct ppc_data*,int) ; 
 int ppc_smclike_setmode (struct ppc_data*,int) ; 

int
ppc_setmode(device_t dev, int mode)
{
	struct ppc_data *ppc = DEVTOSOFTC(dev);

	PPC_ASSERT_LOCKED(ppc);
	switch (ppc->ppc_type) {
	case PPC_TYPE_SMCLIKE:
		return (ppc_smclike_setmode(ppc, mode));
		break;

	case PPC_TYPE_GENERIC:
	default:
		return (ppc_generic_setmode(ppc, mode));
		break;
	}

	/* not reached */
	return (ENXIO);
}