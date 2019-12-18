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
struct ppc_data {int ppc_avm; scalar_t__ ppc_dmachan; int /*<<< orphan*/  ppc_dmadone; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PPB_ECP ; 
 struct ppc_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isa_dma_acquire (scalar_t__) ; 
 int /*<<< orphan*/  isa_dmainit (scalar_t__,int) ; 
 int ppc_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppc_isa_dmadone ; 

int
ppc_isa_attach(device_t dev)
{
	struct ppc_data *ppc = device_get_softc(dev);

	if ((ppc->ppc_avm & PPB_ECP) && (ppc->ppc_dmachan > 0)) {
		/* acquire the DMA channel forever */   /* XXX */
		isa_dma_acquire(ppc->ppc_dmachan);
		isa_dmainit(ppc->ppc_dmachan, 1024); /* nlpt.BUFSIZE */
		ppc->ppc_dmadone = ppc_isa_dmadone;
	}

	return (ppc_attach(dev));
}