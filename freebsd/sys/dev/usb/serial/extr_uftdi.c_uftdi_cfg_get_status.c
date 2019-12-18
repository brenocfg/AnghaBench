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
typedef  int /*<<< orphan*/  uint8_t ;
struct uftdi_softc {int /*<<< orphan*/  sc_lsr; int /*<<< orphan*/  sc_msr; } ;
struct ucom_softc {struct uftdi_softc* sc_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
uftdi_cfg_get_status(struct ucom_softc *ucom, uint8_t *lsr, uint8_t *msr)
{
	struct uftdi_softc *sc = ucom->sc_parent;

	DPRINTFN(3, "msr=0x%02x lsr=0x%02x\n", sc->sc_msr, sc->sc_lsr);

	*msr = sc->sc_msr;
	*lsr = sc->sc_lsr;
}