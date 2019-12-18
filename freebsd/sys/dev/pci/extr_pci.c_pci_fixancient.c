#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int hdrtype; scalar_t__ baseclass; scalar_t__ subclass; } ;
typedef  TYPE_1__ pcicfgregs ;

/* Variables and functions */
 scalar_t__ PCIC_BRIDGE ; 
 int PCIM_HDRTYPE ; 
 int PCIM_HDRTYPE_BRIDGE ; 
 int PCIM_HDRTYPE_NORMAL ; 
 scalar_t__ PCIS_BRIDGE_PCI ; 

__attribute__((used)) static void
pci_fixancient(pcicfgregs *cfg)
{
	if ((cfg->hdrtype & PCIM_HDRTYPE) != PCIM_HDRTYPE_NORMAL)
		return;

	/* PCI to PCI bridges use header type 1 */
	if (cfg->baseclass == PCIC_BRIDGE && cfg->subclass == PCIS_BRIDGE_PCI)
		cfg->hdrtype = PCIM_HDRTYPE_BRIDGE;
}