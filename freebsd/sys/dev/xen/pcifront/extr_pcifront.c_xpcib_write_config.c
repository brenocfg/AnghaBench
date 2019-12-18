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
typedef  int /*<<< orphan*/  u_int32_t ;
struct xpcib_softc {int /*<<< orphan*/  pdev; int /*<<< orphan*/  bus; int /*<<< orphan*/  domain; } ;
struct xen_pci_op {int offset; int size; int /*<<< orphan*/  value; int /*<<< orphan*/  devfn; int /*<<< orphan*/  bus; int /*<<< orphan*/  domain; int /*<<< orphan*/  cmd; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int,int,int,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PCI_DEVFN (int,int) ; 
 int /*<<< orphan*/  XEN_PCI_OP_conf_write ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int do_pci_op (int /*<<< orphan*/ ,struct xen_pci_op*) ; 

__attribute__((used)) static void
xpcib_write_config(device_t dev, int bus, int slot, int func,
				   int reg, u_int32_t data, int bytes)
{
	struct xpcib_softc *sc = (struct xpcib_softc *)device_get_softc(dev);
	struct xen_pci_op op = {
		.cmd    = XEN_PCI_OP_conf_write,
		.domain = sc->domain,
		.bus    = sc->bus,
		.devfn  = PCI_DEVFN(slot, func),
		.offset = reg,
		.size   = bytes,
		.value  = data,
	};
	int err;

	err = do_pci_op(sc->pdev, &op);

	DPRINTF("write config (b=%d, s=%d, f=%d, reg=%d, len=%d, val=%x, err=%d)\n",
			bus, slot, func, reg, bytes, data, err);
}