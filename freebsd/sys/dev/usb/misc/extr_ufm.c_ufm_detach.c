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
struct ufm_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_fifo; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct ufm_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fifo_detach (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ufm_detach(device_t dev)
{
	struct ufm_softc *sc = device_get_softc(dev);

	usb_fifo_detach(&sc->sc_fifo);

	mtx_destroy(&sc->sc_mtx);

	return (0);
}