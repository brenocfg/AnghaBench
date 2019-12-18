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
struct s10_svc_softc {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  method ;
typedef  int /*<<< orphan*/ * intel_smc_callfn_t ;

/* Variables and functions */
 scalar_t__ OF_getprop (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/ * arm_smccc_hvc ; 
 int /*<<< orphan*/ * arm_smccc_smc ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static intel_smc_callfn_t
s10_svc_get_callfn(struct s10_svc_softc *sc, phandle_t node)
{
	char method[16];

	if ((OF_getprop(node, "method", method, sizeof(method))) > 0) {
		if (strcmp(method, "hvc") == 0)
			return (arm_smccc_hvc);
		else if (strcmp(method, "smc") == 0)
			return (arm_smccc_smc);
		else
			device_printf(sc->dev,
			    "Invalid method \"%s\"\n", method);
	} else
		device_printf(sc->dev, "SMC method not provided\n");

	return (NULL);
}