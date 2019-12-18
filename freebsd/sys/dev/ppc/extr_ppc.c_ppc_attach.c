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
struct ppc_data {size_t ppc_model; size_t ppc_avm; size_t ppc_mode; size_t ppc_epp; int /*<<< orphan*/  ppbus; int /*<<< orphan*/  ppc_lock; int /*<<< orphan*/  intr_cookie; scalar_t__ res_irq; int /*<<< orphan*/  ppc_rthr; int /*<<< orphan*/  ppc_wthr; scalar_t__ ppc_fifo; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct ppc_data* DEVTOSOFTC (int /*<<< orphan*/ ) ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_TTY ; 
 int /*<<< orphan*/  MTX_DEF ; 
 scalar_t__ PPB_IS_EPP (size_t) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ppc_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  device_probe_and_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ppc_avms ; 
 char** ppc_epp_protocol ; 
 int /*<<< orphan*/ * ppc_models ; 
 int /*<<< orphan*/ * ppc_modes ; 
 int /*<<< orphan*/  ppcintr ; 

int
ppc_attach(device_t dev)
{
	struct ppc_data *ppc = DEVTOSOFTC(dev);
	int error;

	mtx_init(&ppc->ppc_lock, device_get_nameunit(dev), "ppc", MTX_DEF);

	device_printf(dev, "%s chipset (%s) in %s mode%s\n",
		      ppc_models[ppc->ppc_model], ppc_avms[ppc->ppc_avm],
		      ppc_modes[ppc->ppc_mode], (PPB_IS_EPP(ppc->ppc_mode)) ?
		      ppc_epp_protocol[ppc->ppc_epp] : "");

	if (ppc->ppc_fifo)
		device_printf(dev, "FIFO with %d/%d/%d bytes threshold\n",
			      ppc->ppc_fifo, ppc->ppc_wthr, ppc->ppc_rthr);

	if (ppc->res_irq) {
		/* default to the tty mask for registration */	/* XXX */
		error = bus_setup_intr(dev, ppc->res_irq, INTR_TYPE_TTY |
		    INTR_MPSAFE, NULL, ppcintr, ppc, &ppc->intr_cookie);
		if (error) {
			device_printf(dev,
			    "failed to register interrupt handler: %d\n",
			    error);
			mtx_destroy(&ppc->ppc_lock);
			return (error);
		}
	}

	/* add ppbus as a child of this isa to parallel bridge */
	ppc->ppbus = device_add_child(dev, "ppbus", -1);

	/*
	 * Probe the ppbus and attach devices found.
	 */
	device_probe_and_attach(ppc->ppbus);

	return (0);
}