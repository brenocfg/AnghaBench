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
struct ntb_plx_softc {scalar_t__ int_res; int /*<<< orphan*/  int_rid; int /*<<< orphan*/  int_tag; int /*<<< orphan*/  link; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  NTX_WRITE (struct ntb_plx_softc*,int,int) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct ntb_plx_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ntb_plx_teardown_intr(device_t dev)
{
	struct ntb_plx_softc *sc = device_get_softc(dev);

	if (!sc->link)	/* Link Interface has no Link Error registers. */
		NTX_WRITE(sc, 0xfe4, 0xf);	/* Mask link interrupts. */

	if (sc->int_res) {
		bus_teardown_intr(dev, sc->int_res, sc->int_tag);
		bus_release_resource(dev, SYS_RES_IRQ, sc->int_rid,
		    sc->int_res);
	}
}