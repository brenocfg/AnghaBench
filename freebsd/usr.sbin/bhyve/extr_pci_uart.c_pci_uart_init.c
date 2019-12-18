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
struct uart_softc {int dummy; } ;
struct pci_devinst {int pi_slot; int pi_func; struct uart_softc* pi_arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  COM_DEV ; 
 int /*<<< orphan*/  COM_VENDOR ; 
 int /*<<< orphan*/  PCIBAR_IO ; 
 int /*<<< orphan*/  PCIC_SIMPLECOMM ; 
 int /*<<< orphan*/  PCIR_CLASS ; 
 int /*<<< orphan*/  PCIR_DEVICE ; 
 int /*<<< orphan*/  PCIR_VENDOR ; 
 int /*<<< orphan*/  UART_IO_BAR_SIZE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int,int) ; 
 int /*<<< orphan*/  pci_emul_alloc_bar (struct pci_devinst*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_lintr_request (struct pci_devinst*) ; 
 int /*<<< orphan*/  pci_set_cfgdata16 (struct pci_devinst*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_cfgdata8 (struct pci_devinst*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_uart_intr_assert ; 
 int /*<<< orphan*/  pci_uart_intr_deassert ; 
 int /*<<< orphan*/  stderr ; 
 struct uart_softc* uart_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pci_devinst*) ; 
 scalar_t__ uart_set_backend (struct uart_softc*,char*) ; 

__attribute__((used)) static int
pci_uart_init(struct vmctx *ctx, struct pci_devinst *pi, char *opts)
{
	struct uart_softc *sc;

	pci_emul_alloc_bar(pi, 0, PCIBAR_IO, UART_IO_BAR_SIZE);
	pci_lintr_request(pi);

	/* initialize config space */
	pci_set_cfgdata16(pi, PCIR_DEVICE, COM_DEV);
	pci_set_cfgdata16(pi, PCIR_VENDOR, COM_VENDOR);
	pci_set_cfgdata8(pi, PCIR_CLASS, PCIC_SIMPLECOMM);

	sc = uart_init(pci_uart_intr_assert, pci_uart_intr_deassert, pi);
	pi->pi_arg = sc;

	if (uart_set_backend(sc, opts) != 0) {
		fprintf(stderr, "Unable to initialize backend '%s' for "
		    "pci uart at %d:%d\n", opts, pi->pi_slot, pi->pi_func);
		return (-1);
	}

	return (0);
}