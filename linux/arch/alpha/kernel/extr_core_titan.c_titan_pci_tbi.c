#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {unsigned long csr; } ;
struct TYPE_9__ {unsigned long csr; } ;
struct TYPE_11__ {TYPE_2__ gtlbiv; TYPE_1__ gtlbia; } ;
struct TYPE_12__ {TYPE_3__ g; } ;
struct TYPE_13__ {TYPE_4__ port_specific; } ;
typedef  TYPE_5__ titan_pachip_port ;
struct TYPE_14__ {TYPE_5__ a_port; TYPE_5__ g_port; } ;
typedef  TYPE_6__ titan_pachip ;
struct pci_controller {int index; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 TYPE_6__* TITAN_pachip0 ; 
 TYPE_6__* TITAN_pachip1 ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  wmb () ; 

void
titan_pci_tbi(struct pci_controller *hose, dma_addr_t start, dma_addr_t end)
{
	titan_pachip *pachip = 
	  (hose->index & 1) ? TITAN_pachip1 : TITAN_pachip0;
	titan_pachip_port *port;
	volatile unsigned long *csr;
	unsigned long value;

	/* Get the right hose.  */
	port = &pachip->g_port;
	if (hose->index & 2) 
		port = &pachip->a_port;

	/* We can invalidate up to 8 tlb entries in a go.  The flush
	   matches against <31:16> in the pci address.  
	   Note that gtlbi* and atlbi* are in the same place in the g_port
	   and a_port, respectively, so the g_port offset can be used
	   even if hose is an a_port */
	csr = &port->port_specific.g.gtlbia.csr;
	if (((start ^ end) & 0xffff0000) == 0)
		csr = &port->port_specific.g.gtlbiv.csr;

	/* For TBIA, it doesn't matter what value we write.  For TBI, 
	   it's the shifted tag bits.  */
	value = (start & 0xffff0000) >> 12;

	wmb();
	*csr = value;
	mb();
	*csr;
}