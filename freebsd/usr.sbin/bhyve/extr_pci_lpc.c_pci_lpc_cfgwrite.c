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
typedef  int /*<<< orphan*/  uint32_t ;
struct vmctx {int dummy; } ;
struct pci_devinst {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_set_cfgdata8 (struct pci_devinst*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pirq_read (int) ; 
 int /*<<< orphan*/  pirq_write (struct vmctx*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pci_lpc_cfgwrite(struct vmctx *ctx, int vcpu, struct pci_devinst *pi,
		  int coff, int bytes, uint32_t val)
{
	int pirq_pin;

	if (bytes == 1) {
		pirq_pin = 0;
		if (coff >= 0x60 && coff <= 0x63)
			pirq_pin = coff - 0x60 + 1;
		if (coff >= 0x68 && coff <= 0x6b)
			pirq_pin = coff - 0x68 + 5;
		if (pirq_pin != 0) {
			pirq_write(ctx, pirq_pin, val);
			pci_set_cfgdata8(pi, coff, pirq_read(pirq_pin));
			return (0);
		}
	}
	return (-1);
}