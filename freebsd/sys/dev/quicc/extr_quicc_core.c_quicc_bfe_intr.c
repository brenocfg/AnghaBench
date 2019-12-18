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
typedef  int uint32_t ;
struct quicc_softc {int /*<<< orphan*/  sc_dev; struct quicc_device* sc_device; int /*<<< orphan*/  sc_rres; } ;
struct quicc_device {int (* qd_ih ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  qd_ih_arg; } ;

/* Variables and functions */
 int FILTER_STRAY ; 
 int /*<<< orphan*/  QUICC_REG_SIPNR_L ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int quicc_read4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
quicc_bfe_intr(void *arg)
{
	struct quicc_device *qd;
	struct quicc_softc *sc = arg;
	uint32_t sipnr;

	sipnr = quicc_read4(sc->sc_rres, QUICC_REG_SIPNR_L);
	if (sipnr & 0x00f00000)
		qd = sc->sc_device;
	else
		qd = NULL;

	if (qd == NULL || qd->qd_ih == NULL) {
		device_printf(sc->sc_dev, "Stray interrupt %08x\n", sipnr);
		return (FILTER_STRAY);
	}

	return ((*qd->qd_ih)(qd->qd_ih_arg));
}