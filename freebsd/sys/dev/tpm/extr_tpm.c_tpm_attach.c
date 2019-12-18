#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* dv_xname; } ;
struct tpm_softc {int (* sc_init ) (struct tpm_softc*,scalar_t__,char*) ;int /*<<< orphan*/  sc_powerhook; int /*<<< orphan*/  sc_suspend; TYPE_1__ sc_dev; int /*<<< orphan*/  sc_bh; int /*<<< orphan*/  sc_bt; int /*<<< orphan*/ * sc_ih; int /*<<< orphan*/  sc_end; int /*<<< orphan*/  sc_write; int /*<<< orphan*/  sc_read; int /*<<< orphan*/  sc_start; int /*<<< orphan*/  sc_batm; } ;
struct isa_attach_args {scalar_t__ ia_irq; int /*<<< orphan*/  ia_ic; int /*<<< orphan*/  ia_maddr; int /*<<< orphan*/  ia_memt; int /*<<< orphan*/  ia_iot; int /*<<< orphan*/  ia_iosize; int /*<<< orphan*/  ia_iobase; } ;
typedef  scalar_t__ device_t ;
typedef  int /*<<< orphan*/  bus_size_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  IPL_TTY ; 
 scalar_t__ IRQUNK ; 
 int /*<<< orphan*/  IST_EDGE ; 
 int /*<<< orphan*/  PWR_RESUME ; 
 int /*<<< orphan*/  TPM_SIZE ; 
 scalar_t__ bus_space_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_space_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * isa_intr_establish (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tpm_softc*,char*) ; 
 int /*<<< orphan*/  powerhook_establish (int /*<<< orphan*/ ,struct tpm_softc*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int stub1 (struct tpm_softc*,scalar_t__,char*) ; 
 int /*<<< orphan*/  tpm_intr ; 
 int /*<<< orphan*/  tpm_legacy_end ; 
 int tpm_legacy_init (struct tpm_softc*,scalar_t__,char*) ; 
 scalar_t__ tpm_legacy_probe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpm_legacy_read ; 
 int /*<<< orphan*/  tpm_legacy_start ; 
 int /*<<< orphan*/  tpm_legacy_write ; 
 int /*<<< orphan*/  tpm_powerhook ; 
 int /*<<< orphan*/  tpm_tis12_end ; 
 int tpm_tis12_init (struct tpm_softc*,scalar_t__,char*) ; 
 int /*<<< orphan*/  tpm_tis12_read ; 
 int /*<<< orphan*/  tpm_tis12_start ; 
 int /*<<< orphan*/  tpm_tis12_write ; 

void
tpm_attach(device_t parent, device_t self, void *aux)
{
	struct tpm_softc *sc = (struct tpm_softc *)self;
	struct isa_attach_args *ia = aux;
	bus_addr_t iobase;
	bus_size_t size;
	int rv;

	if (tpm_legacy_probe(ia->ia_iot, ia->ia_iobase)) {
		sc->sc_bt = ia->ia_iot;
		iobase = ia->ia_iobase;
		size = ia->ia_iosize;
		sc->sc_batm = ia->ia_iot;
		sc->sc_init = tpm_legacy_init;
		sc->sc_start = tpm_legacy_start;
		sc->sc_read = tpm_legacy_read;
		sc->sc_write = tpm_legacy_write;
		sc->sc_end = tpm_legacy_end;
	} else {
		sc->sc_bt = ia->ia_memt;
		iobase = ia->ia_maddr;
		size = TPM_SIZE;
		sc->sc_init = tpm_tis12_init;
		sc->sc_start = tpm_tis12_start;
		sc->sc_read = tpm_tis12_read;
		sc->sc_write = tpm_tis12_write;
		sc->sc_end = tpm_tis12_end;
	}

	if (bus_space_map(sc->sc_bt, iobase, size, 0, &sc->sc_bh)) {
		printf(": cannot map registers\n");
		return;
	}

	if ((rv = (sc->sc_init)(sc, ia->ia_irq, sc->sc_dev.dv_xname))) {
		bus_space_unmap(sc->sc_bt, sc->sc_bh, size);
		return;
	}

	/*
	 * Only setup interrupt handler when we have a vector and the
	 * chip is TIS 1.2 compliant.
	 */
	if (sc->sc_init == tpm_tis12_init && ia->ia_irq != IRQUNK &&
	    (sc->sc_ih = isa_intr_establish(ia->ia_ic, ia->ia_irq, IST_EDGE,
	    IPL_TTY, tpm_intr, sc, sc->sc_dev.dv_xname)) == NULL) {
		bus_space_unmap(sc->sc_bt, sc->sc_bh, TPM_SIZE);
		printf("%s: cannot establish interrupt\n",
		    sc->sc_dev.dv_xname);
		return;
	}

	sc->sc_suspend = PWR_RESUME;
	sc->sc_powerhook = powerhook_establish(tpm_powerhook, sc);
}