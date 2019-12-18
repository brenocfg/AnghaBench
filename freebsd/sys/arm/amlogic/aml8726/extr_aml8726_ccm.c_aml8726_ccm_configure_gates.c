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
typedef  int uint32_t ;
struct aml8726_ccm_softc {int /*<<< orphan*/  dev; struct aml8726_ccm_function* soc; } ;
struct aml8726_ccm_gate {int bits; int /*<<< orphan*/  addr; } ;
struct aml8726_ccm_function {struct aml8726_ccm_gate* gates; int /*<<< orphan*/ * name; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  phandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  AML_CCM_LOCK (struct aml8726_ccm_softc*) ; 
 int /*<<< orphan*/  AML_CCM_UNLOCK (struct aml8726_ccm_softc*) ; 
 int CSR_READ_4 (struct aml8726_ccm_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct aml8726_ccm_softc*,int /*<<< orphan*/ ,int) ; 
 int ENXIO ; 
 scalar_t__ OF_getprop_alloc (int /*<<< orphan*/ ,char*,void**) ; 
 int /*<<< orphan*/  OF_prop_free (char*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ *,char*,scalar_t__) ; 

__attribute__((used)) static int
aml8726_ccm_configure_gates(struct aml8726_ccm_softc *sc)
{
	struct aml8726_ccm_function *f;
	struct aml8726_ccm_gate *g;
	char *function_name;
	char *functions;
	phandle_t node;
	ssize_t len;
	uint32_t value;

	node = ofw_bus_get_node(sc->dev);

	len = OF_getprop_alloc(node, "functions",
	    (void **)&functions);

	if (len < 0) {
		device_printf(sc->dev, "missing functions attribute in FDT\n");
		return (ENXIO);
	}

	function_name = functions;

	while (len) {
		for (f = sc->soc; f->name != NULL; f++)
			if (strncmp(f->name, function_name, len) == 0)
				break;

		if (f->name == NULL) {
			/* display message prior to queuing up next string */
			device_printf(sc->dev,
			    "unknown function attribute %.*s in FDT\n",
			    len, function_name);
		}

		/* queue up next string */
		while (*function_name && len) {
			function_name++;
			len--;
		}
		if (len) {
			function_name++;
			len--;
		}

		if (f->name == NULL)
			continue;

		AML_CCM_LOCK(sc);

		/*
		 * Enable the clock gates necessary for the function.
		 *
		 * In some cases a clock may be shared across functions
		 * (meaning don't disable a clock without ensuring that
		 * it's not required by someone else).
		 */
		for (g = f->gates; g->bits != 0x00000000; g++) {
			value = CSR_READ_4(sc, g->addr);
			value |= g->bits;
			CSR_WRITE_4(sc, g->addr, value);
		}

		AML_CCM_UNLOCK(sc);
	}

	OF_prop_free(functions);

	return (0);
}