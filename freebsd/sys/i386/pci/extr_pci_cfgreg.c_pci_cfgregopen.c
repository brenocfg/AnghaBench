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
typedef  int uint16_t ;

/* Variables and functions */
 scalar_t__ CFGMECH_NONE ; 
 int /*<<< orphan*/  MTX_SPIN ; 
 int /*<<< orphan*/  PRVERB (char*) ; 
 scalar_t__ cfgmech ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_pir_open () ; 
 int pcibios_get_version () ; 
 int /*<<< orphan*/  pcicfg_mtx ; 
 scalar_t__ pcireg_cfgopen () ; 

int
pci_cfgregopen(void)
{
	uint16_t v;
	static int opened = 0;

	if (opened)
		return (1);

	if (cfgmech == CFGMECH_NONE && pcireg_cfgopen() == 0)
		return (0);

	v = pcibios_get_version();
	if (v > 0)
		PRVERB(("pcibios: BIOS version %x.%02x\n", (v & 0xff00) >> 8,
		    v & 0xff));
	mtx_init(&pcicfg_mtx, "pcicfg", NULL, MTX_SPIN);
	opened = 1;

	/* $PIR requires PCI BIOS 2.10 or greater. */
	if (v >= 0x0210)
		pci_pir_open();

	return (1);
}