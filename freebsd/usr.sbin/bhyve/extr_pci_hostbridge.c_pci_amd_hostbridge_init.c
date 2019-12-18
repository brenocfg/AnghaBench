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
struct vmctx {int dummy; } ;
struct pci_devinst {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIR_DEVICE ; 
 int /*<<< orphan*/  PCIR_VENDOR ; 
 int /*<<< orphan*/  pci_hostbridge_init (struct vmctx*,struct pci_devinst*,char*) ; 
 int /*<<< orphan*/  pci_set_cfgdata16 (struct pci_devinst*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
pci_amd_hostbridge_init(struct vmctx *ctx, struct pci_devinst *pi, char *opts)
{
	(void) pci_hostbridge_init(ctx, pi, opts);
	pci_set_cfgdata16(pi, PCIR_VENDOR, 0x1022);	/* AMD */
	pci_set_cfgdata16(pi, PCIR_DEVICE, 0x7432);	/* made up */

	return (0);
}